#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using std::cin, std::cout, std::endl;
using std::swap;
using std::vector;

constexpr int MAX_N = 100000;
constexpr int MAX_LOG_N = 20;
constexpr int MAX_M = 100000;

int N, M;
vector<int> edges[MAX_N + 1];

int depths[MAX_N + 1];
int pars[MAX_N + 1][20];
bool visited[MAX_N + 1];

constexpr int intlog2(int num) {
  int lv = 0;
  while (num >>= 1) ++lv;
  return lv;
}

void calc_depth(int here, int depth) {
  visited[here] = true;
  depths[here] = depth;

  for (int v : edges[here]) {
    if (visited[v]) continue;
    pars[v][0] = here;
    calc_depth(v, depth + 1);
  }
}

int lca(int a, int b) {
  if (a == b) return a;
  if (depths[b] > depths[a]) swap(a, b);  // always depths[b] >= depths[a]
  if (depths[a] > depths[b])
    return lca(pars[a][intlog2(depths[a] - depths[b])], b);


  // now depths[a] == depths[b]
  for (int i = MAX_LOG_N - 1; i >= 0; i--)
    if (pars[a][i] != pars[b][i]) return lca(pars[a][i], pars[b][i]);

  return pars[a][0];
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  cin >> N;
  // scanf("%d", &N);
  for (int i = 0; i < N - 1; i++) {
    int a, b;
    cin >> a >> b;
    // scanf("%d%d", &a, &b);
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  calc_depth(1, 0);

  for (int j = 1; j < MAX_LOG_N; j++) {
    for (int i = 1; i <= N; i++) {
      pars[i][j] = pars[pars[i][j - 1]][j - 1];
    }
  }

  cin >> M;
  // scanf("%d", &M);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    // scanf("%d%d", &a, &b);
    cout << lca(a, b) << '\n';
  }

  return 0;
}