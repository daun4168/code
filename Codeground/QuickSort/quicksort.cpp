#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>

#define INT_MAX 987654321

using namespace std;

constexpr int MAX_N = 200000;
int arr[MAX_N];
bool is_pivot[MAX_N];



int main() {
  int i;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("quicksort.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> arr[i];
    }
    memset(is_pivot, true, sizeof(is_pivot));
    
    // less check
    int max_ele = arr[0];
    for (int i = 1; i < N; i++) {
      if (arr[i] < max_ele) {
        is_pivot[i] = false;
      }
      max_ele = max(max_ele, arr[i]);
    }

    int min_ele = arr[N - 1];
    for (int i = N - 2; i >= 0 ; i--) {
      if (arr[i] > min_ele) {
        is_pivot[i] = false;
      }
      min_ele = min(min_ele, arr[i]);
    }
    

    int pivot_num = count(is_pivot, is_pivot + N, true);

    cout << "Case #" << test_case + 1 << endl;
    cout << pivot_num << endl;
    
  }
  return 0;
}