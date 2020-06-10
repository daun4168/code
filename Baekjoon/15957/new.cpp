#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int N, Q;     // 가수/곡의 갯수, 쿼리(propagation)의 갯수
long long J;  // 목표 평균 점수

int singer[101010];         // i 번 곡을 부른 가수
vector<int> album[101010];  // i 번 가수가 부른 곡의 리스트
vector<int> graph[101010];  // 트리를 나타내는 구조
bool visited[101010];  // DFS 를 수행하기 위해 점검하는 방문여부
int ordering[101010];  // 해당 노래의 DFS 방문 순서(DFS 배열)
pair<int, int> affects[101010];  // 해당 정점을 루트 정점으로 삼았을때 영향을
                                 // 미칠 수 있는 DFS 배열에서의 범위

int root[101010];  // i번째 쿼리를 수행했을때 영향을 주기 시작하는 루트 노드
long long score[101010];  // 루트 노드에서 전파할 점수
long long total[101010];  // 포인트 쿼리(lazy propagation)를 수행하기 위해
                          // 사용하는 누적합
int lo[101010], hi[101010];  // 쿼리에 대한 이분탐색을 수행하기 위해, i 번째
                             // 가수마다 몇번째 쿼리부터 목표점수를 넘길 수
                             // 있는지 기록하기 위한 목적의 하한/상한
vector<int> predicted_to[101010];  // q 번째 쿼리까지 돌리고 나서야 목표점수를
                                   // 넘길 수 있는지에 대한 정보를 담기 위한 각
                                   // 인덱스마다 가수에 대한 번호를 저장

// 포인트 쿼리를 수행
long long get(int idx) {
  long long sum = 0;
  while (idx > 0) {
    sum += total[idx];
    idx -= idx & -idx;
  }

  return sum;
}

// 포인트 쿼리를 수행하기 위해 lazy propagation 수행
void update(int idx, long long val) {
  while (idx <= N) {
    total[idx] += val;
    idx += idx & -idx;
  }
}

void range_update(int q) {
  int node = root[q];  // 영향을 미치기 시작하는 노드
  long long length = affects[node].second - affects[node].first +
                     1;  // 루트에서부터 영향을 미칠 수 있는 노드의 갯수
  long long calculated_score = score[q] / length;

  update(affects[node].first, calculated_score);
  update(affects[node].second + 1, -calculated_score);
}

typedef pair<int, int> pii;

int idx = 1;

// 트리 펼치기
void dfs(int u) {
  int l, r;
  l = idx;
  visited[u] = true;
  ordering[u] = idx;

  for (auto v : graph[u])
    if (!visited[v]) ++idx, dfs(v);

  r = idx;

  affects[u] = {l, r};
}

int main() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);

  cin >> N >> Q >> J;
  // 트리의 부모 관계 정보 입력
  for (int i = 2; i <= N; ++i) {
    int parent;
    cin >> parent;
    graph[parent].push_back(i);
  }

  // 가수에 대한 정보 입력
  for (int i = 1; i <= N; ++i) {
    cin >> singer[i];
    album[singer[i]].push_back(i);
  }

  // 트리 펼치기
  dfs(1);

  vector<pii> T;

  // 1-based index 를 위해 집어넣는 아무의미없는 pair
  T.push_back({0, 0});
  for (int i = 1; i <= Q; ++i) {
    int t;
    cin >> t >> root[i] >> score[i];

    // 시간 순으로 정렬하고, 부모노드, 추가할 점수에 대한 정보를 접근할 수 있게
    // 입력받은 순서를 덤으로 삽입
    T.push_back({t, i});
  }

  sort(T.begin(), T.end());

  // 가수가 곡을 부른 적이 없다면 이분탐색에서 제외
  for (int i = 1; i <= N; ++i)
    lo[i] = (album[i].empty() ? Q + 1 : 1), hi[i] = Q + 1;

  bool changed = true;

  while (changed) {
    fill(total, total + 101010, 0);

    for (int i = 1; i <= N; ++i)
      if (lo[i] != hi[i]) predicted_to[(lo[i] + hi[i]) >> 1].push_back(i);

    changed = false;
    for (int q = 1; q <= Q; ++q) {
      int idx = T[q].second;
      range_update(idx);

      while (predicted_to[q].size() > 0) {
        changed = true;

        int singer_id = predicted_to[q].back();
        predicted_to[q].pop_back();

        long long sum = 0;

        long long goal_score = J * album[singer_id].size();

        for (auto song : album[singer_id]) {
          sum += get(
              ordering[song]);  // 트리 펼치기를 수행했을때 각 노래가 DFS
                                // 배열에서 몇번째 위치에서 저장되는지 정보를
                                // 가져온 후, 그 위치에서 포인트쿼리를 수행
          if (sum >= goal_score) break;
        }

        if (sum > goal_score)
          hi[singer_id] = q;
        else
          lo[singer_id] = q + 1;
      }
    }
  }

  // 각 곡을 부른 가수가 몇번째 곡까지 부르고 나서야 평균목표점수를 넘을 수 있게
  // 되는지 출력
  for (int i = 1; i <= N; ++i) {
    if (lo[singer[i]] <= Q)
      cout << T[lo[singer[i]]].first;
    else
      cout << -1;
    cout << '\n';
  }

  return 0;
}