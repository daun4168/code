#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int i;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("bus.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    int N, K;
    cin >> N >> K;
    int pro[200000];

    for (int i = 0; i < N; i++) {
      cin >> pro[i];
    }
    sort(pro, pro + N);

    int max_bus = 0;
    int e_pos = 0;
    
    for (int i = 0; i < N; i++) {
      while (pro[e_pos + 1] <= pro[i] + K && e_pos < N - 1)
        e_pos++;

      max_bus = max(max_bus, e_pos - i + 1);
    }


    cout << "Case #" << test_case + 1 << endl;
    cout << max_bus << endl;
  }
  return 0;
}