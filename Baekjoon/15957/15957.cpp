#include <iostream>
#include <map>
#include <queue>
#include <vector>

using std::cin, std::cout, std::endl;
using std::priority_queue, std::vector, std::map;

constexpr int MAX_N = 100000;
constexpr int MAX_K = 100000;
constexpr int MAX_J = 100000000;
constexpr int MAX_T = 1000000000;
constexpr int MAX_S = 1000000000;

struct Song {
  Song() = delete;
  Song(int time, int song_num, int weight)
      : time(time), song_num(song_num), weight(weight) {}
  int time;
  int song_num;
  int weight;
};

class SongGreater {
 public:
  bool operator()(const Song& t, const Song& u) { return t.time > u.time; }
};

int N, K, J;

int pars[MAX_N + 1];
vector<int> childs[MAX_N + 1];
int child_nums[MAX_N + 1];
map<int, int> child_singers[MAX_N + 1];

int singers[MAX_N + 1];
int singer_nums[MAX_N + 1];
int singer_weight_sum[MAX_N + 1];
int over_time[MAX_N + 1];
bool everything_over[MAX_N + 1];

int calc_child_nums(int idx) {
  int sum_nums = 0;
  for (const auto& ele : childs[idx]) {
    sum_nums += calc_child_nums(ele);
  }
  child_nums[idx] = sum_nums;
  return sum_nums + 1;
}

map<int, int>& calc_child_singers(int idx) {
  

  for (const auto& ele : childs[idx]) {
    auto& child_singer = calc_child_singers(ele);
    for (const auto& p : child_singer) {
      child_singers[idx][p.first] += p.second;
    }
  }

  child_singers[idx][singers[idx]]++;

  return child_singers[idx];
}

void add_weight(int idx, int weight, int time) {
  // if (over_time[singers[idx]] == -1) {
  //   singer_weight_sum[singers[idx]] += weight;
  //   if (singer_weight_sum[singers[idx]] > J * singer_nums[singers[idx]]) {
  //     over_time[singers[idx]] = time;
  //   }
  // }

  // for (const auto& ele : childs[idx]) {
  //   add_weight(ele, weight, time);
  // }

  // 2
  for (const auto& p : child_singers[idx]) {

    if (over_time[p.first] == -1) {
      singer_weight_sum[p.first] += weight * p.second;
      if (singer_weight_sum[p.first] > J * singer_nums[p.first]) {
        over_time[p.first] = time;
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  cin >> N >> K >> J;

  for (int i = 2; i <= N; i++) {
    cin >> pars[i];
    childs[pars[i]].push_back(i);
  }

  for (int i = 1; i <= N; i++) {
    cin >> singers[i];
    singer_nums[singers[i]]++;
  }

  priority_queue<Song, vector<Song>, SongGreater> pq;

  for (int k = 0; k < K; k++) {
    int T, P, S;
    cin >> T >> P >> S;
    pq.push(Song(T, P, S));
  }

  calc_child_nums(1);
  calc_child_singers(1);

  // for (int idx = 1; idx <= 3; idx++) {
  //   cout << "IDX!" << idx << endl;
  //   for (const auto& p : child_singers[idx]) {
  //     cout << p.first << " " << p.second << endl;
  //   }
  // }

  for (int i = 1; i <= N; i++) {
    over_time[i] = -1;
  }

  while (!pq.empty()) {
    int song_num = pq.top().song_num;
    int time = pq.top().time;
    int weight = pq.top().weight;

    int each_weight = weight / (child_nums[song_num] + 1);
    add_weight(song_num, each_weight, time);
    pq.pop();
  }

  for (int i = 1; i <= N; i++) {
    cout << over_time[singers[i]] << endl;
  }

  return 0;
}