#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <list>
#include <cstring>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <random>
#include <cstdlib>

using namespace std;

typedef pair<int, int> Edge;

constexpr int MAX_N = 100;
constexpr int MAX_M = 1000;
#define INT_MAX 987654321;

#define OPT_NUM 10000
#define OPT_NUM2 100

int N, M;
Edge e[MAX_M];

struct iv {
  int dist;
  vector<int> arr;
};

int cal_dist(const vector<int>& v) {
  int sum = 0;
  for (int i = 0; i < M; i++) {
    int pv = v[e[i].first];
    int pu = v[e[i].second];
    sum += abs(pv - pu);
  }
  return sum;
}

iv min_dist(vector<int> v) {
  if (v.size() == N) return iv{ cal_dist(v), v };
  list<int> remain;
  for (int i = 0; i < N; i++) {
    remain.push_back(i);
  }
  for (int i : v) {
    remain.remove(i);
  }
  int min_dist_sum = INT_MAX;
  vector<int> rv;
  for (int i : remain) {
    vector<int> new_v = vector<int>(v);
    new_v.push_back(i);
    auto md = min_dist(vector<int>(new_v));
    if (md.dist < min_dist_sum) {
      min_dist_sum = md.dist;
      rv = md.arr;
    }
  }
  return iv{ min_dist_sum, rv };
}

int myrandom(int i) { return rand() % i; }

void change(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("line.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
      int a, b;
      cin >> a >> b;
      e[i] = { a, b };
    }

    vector<int> arr;
    int min_dist_sum = INT_MAX;
    
    if (N < 9) {
      auto md = min_dist(vector<int>());
      arr = md.arr;
      min_dist_sum = md.dist;
    }
    else {
      for (int j = 0; j < OPT_NUM2; j++) {
        vector<int> newarr(N);
        for (int i = 0; i < N; i++) {
          newarr[i] = i;
        }
        random_shuffle(newarr.begin(), newarr.end(), myrandom);
        int local_dist_sum = cal_dist(newarr);
        int new_dist = cal_dist(newarr);
        for (int i = 0; i < OPT_NUM; i++) {
          int ch1 = myrandom(N);
          int ch2 = myrandom(N);
          change(newarr[ch1], newarr[ch2]);
          int new_dist_sum = cal_dist(newarr);
          if (new_dist_sum < local_dist_sum) {
            local_dist_sum = new_dist_sum;
          }
          else {
            change(newarr[ch1], newarr[ch2]);
          }
        }
        if (local_dist_sum < min_dist_sum) {
          arr = newarr;
          min_dist_sum = local_dist_sum;
        }
      }
      
      /*avg_dist_sum /= 500;
      cout << min_dist_sum << endl;
      cout << avg_dist_sum << endl;*/
    }

    vector<int> xs = vector<int>(N);
    for (int i = 0; i < N; i++) {
      xs[arr[i]] = i;
    }
    
    cout << "Case #" << test_case + 1 << endl;
    cout << min_dist_sum << endl;
    for (auto i : xs) {
      cout << i << ' ';
    }
    cout << endl;
  }
  return 0;
}