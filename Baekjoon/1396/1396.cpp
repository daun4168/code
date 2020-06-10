#include <functional>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using std::cin, std::cout;
using std::greater;
using std::vector;
using std::priority_queue;
using std::swap;


constexpr int MAX_N = 100000;
constexpr int MAX_M = 100000;
constexpr int MAX_Q = 100000;
constexpr int MAX_C = 1000000;
constexpr int MAX_V = MAX_N + MAX_M + 2;
constexpr int MAX_LOG_V = 25;

struct Edge {
  Edge() = delete;
  Edge(int a, int b, int c) : a(a), b(b), c(c) {}
  
  int a;
  int b;
  int c;
  
};

auto operator<(const Edge& e1, const Edge& e2){ return e1.c < e2.c; }
auto operator>(const Edge& e1, const Edge& e2){ return e1.c > e2.c; }



int n, m;
int pars[MAX_V][MAX_LOG_V];
int depths[MAX_V];
int cs[MAX_V];
int sizes[MAX_V];
vector<int> childs[MAX_V];
bool visited[MAX_N + 1];


constexpr int intlog2(int num) {
  int lv = 0;
  while (num >>= 1) ++lv;
  return lv;
}

int find_root(int idx){
  if(pars[idx][0] == 0) return idx;
  return find_root(pars[idx][0]);
}

void calc_depth(int here, int depth) {
  visited[here] = true;
  depths[here] = depth;

  for (int v : childs[here]) {
    if (visited[v]) continue;
    pars[v][0] = here;
    calc_depth(v, depth + 1);
  }
}

int lca(int a, int b) {
  if (a == b) return a;
  if (depths[b] > depths[a]) swap(a, b); 
  if (depths[a] > depths[b])
    return lca(pars[a][intlog2(depths[a] - depths[b])], b);

  for (int i = MAX_LOG_V - 1; i >= 0; i--)
    if (pars[a][i] != pars[b][i]) return lca(pars[a][i], pars[b][i]);

  return pars[a][0];
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  cin >> n >> m;

  vector<Edge> edges;


  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    edges.push_back(Edge{a, b, c});
  }

  std::sort(edges.begin(), edges.end());


  for(int i = 0;i<=n;i++){
    sizes[i] = 1;
  }

  int next_idx = n + 1;
  for(const auto& edge : edges){
    int root_a = find_root(edge.a);
    int root_b = find_root(edge.b);
    pars[root_a][0] = next_idx;
    pars[root_b][0] = next_idx;
    childs[next_idx].push_back(root_a);
    childs[next_idx].push_back(root_b);
    cs[next_idx] = edge.c;
    sizes[next_idx] = sizes[root_a] + sizes[root_b];
    next_idx++;
  }

  calc_depth(n+m, 0);

  for (int j = 1; j < MAX_LOG_V; j++) {
    for (int i = 1; i <= n+m; i++) {
      pars[i][j] = pars[pars[i][j - 1]][j - 1];
    }
  }

  int q;
  cin >> q;

  for(int i = 0;i<q;i++){
    int x, y;
    cin >> x >> y;
    if(find_root(x) != find_root(y)) {
      cout << "-1\n";
      continue;
    }
    int v = lca(x, y);
    cout << cs[v] <<' ' << sizes[v] << '\n';
  }

  return 0;
}