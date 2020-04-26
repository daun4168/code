#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

int N, M, K;

vector<int> edata;
vector<int> pattern;
vector<int> pindex;
vector<bool> isearthq;


template <typename T>
vector<int> sort_indexes(const vector<T> &v) {

  // initialize original index locations
  vector<int> idx(v.size());
  iota(idx.begin(), idx.end(), 0);

  // sort indexes based on comparing values in v
  sort(idx.begin(), idx.end(),
    [&v](int i1, int i2) {return v[i1] < v[i2]; });

  return idx;
}

bool check_pattern(int st) {
  int last_value = 0;
  for (int i = 0; i < M; i++) {
    if (edata[pindex[i] + st] < last_value)
      return false;
    last_value = edata[pindex[i] + st];
  }
  return true;
}



void check_pattern2(int st, int k) {
  vector<int> dp;
  vector<int> earthqday;
  dp.resize(k + 1);
  earthqday.resize(k + 1);
  for (int i = 0; i <= k; i++) {
    dp[i] = 0;
    earthqday[i] = 0;
  }

  for (int i = 1; i < M; i++) {
    for (int j = 0; j <= k; j++) {
      if (dp[j] == -1) continue;
      if (edata[pindex[i] + st] > dp[j]) {
        dp[j] = edata[pindex[i] + st];
        earthqday[j] = max(pindex[i] + st, earthqday[j]);
      }
      else if (j < k) {
        dp[j] = -1;
        dp[j + 1] = edata[pindex[i] + st];
      }
    }
  }
  for (int i = 0; i <= k; i++) {
    if (dp[i] != -1) {
      isearthq[earthqday[i]] = true;
    }
  }
}

int main() {
  int i;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("earthq.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    cin >> N >> M >> K;
    edata.resize(N);
    for (int i = 0; i < N; i++) {
      cin >> edata[i];
    }
    pattern.resize(M);
    for (int i = 0; i < M; i++) {
      cin >> pattern[i];
    }
    pindex = sort_indexes(pattern);
    int num_earthq = 0;
    if (K == 0) {
      // dst = st + N - M
      for (int st = 0; st <= N - M; st++) {
        if (check_pattern(st)) {
          num_earthq++;
        }
      }
    }
    else {
      isearthq.resize(N);
      for (int i = 0; i < N; i++) {
        isearthq[i] = false;
      }
      for (int st = 0; st <= N - M; st++) {
        check_pattern2(st, K);
      }
      num_earthq = count(isearthq.begin(), isearthq.end(), true);
    }


    cout << "Case #" << test_case + 1 << endl;
    cout << num_earthq << endl;
  }
  return 0;
}