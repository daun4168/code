#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <list>

using namespace std;

int dist[1001];
int seen[1001];
list<int> prv[1001];
bool isToll[1001];
int N, M;

#define INT_MAX 10000000

struct vc {
  int c;
  int v;
};

bool operator<(vc a, vc b) {
  return a.c > b.c;
}

class Graph {
public:
  list<vc>* g;

  Graph() {
    g = new list<vc>[1001];
  }

  ~Graph() {
    delete[] g;
  }

  void dijkstra(int src) {
    priority_queue<vc> q;

    q.push(vc{ 0, src });
    for (int i = 1; i <= N; i++) {
      dist[i] = INT_MAX;
      seen[i] = false;
    }
    dist[src] = 0;

    while (!q.empty()) {
      int v1 = q.top().v;
      int cost = q.top().c;
      q.pop();

      if (seen[v1]) continue;
      seen[v1] = true;

      for (vc e : g[v1]) {
        int c = e.c;
        int v2 = e.v;

        if (seen[v2]) continue;
        if (cost + c < dist[v2]) {
          dist[v2] = cost + c;
          prv[v2].clear();
          prv[v2].push_back(v1);
          q.push(vc{ cost + c, v2 });
        }
        else if (cost + c == dist[v2]) {
          prv[v2].push_back(v1);
        }
      }
    }

    for (int i = 1; i <= N; i++) {
      for (int dst : prv[i]) {
        if (dst != src) isToll[dst] = true;
      }
    }
  }

  void addEdge(int src, int dst, int di) {
    g[src].push_back(vc{ di, dst });
    g[dst].push_back(vc{ di, src });
  }
};


int Answer;

int main(int argc, char** argv)
{
  // freopen("frog_jump_input.txt", "r", stdin);
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    cin >> N >> M;
    Graph gr;
    for (int i = 0; i < M; i++) {
      int a, b, dist;
      cin >> a >> b >> dist;
      gr.addEdge(a, b, dist);
    }

    memset(isToll, false, sizeof(isToll));

    for (int i = 1; i <= N; i++) {
      gr.dijkstra(i);
    }
    int count = 0;
    for (int i = 1; i <= N; i++) {
      if (!isToll[i]) count++;
    }
    cout << "Case #" << test_case + 1 << endl;
    cout << count << ' ';
    for (int i = 1; i <= N; i++) {
      if (!isToll[i]) cout << i << ' ';
    }
    cout << endl;
  }
  return 0;
}
