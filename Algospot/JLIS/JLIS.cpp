#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void JLIS();

int main() {
  int test_case;
  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    JLIS();
  }
  return 0;
}

int n, m;
long long A[101], B[101];
int cache[101][101];

int findJlis(int pos1, int pos2) {
  int& cache_ele = cache[pos1][pos2];
  if (cache_ele != -1) return cache_ele;
    if (A[pos1] == B[pos2]) cache_ele = 1;
    else cache_ele = 2;
  long long max_ele = max(A[pos1], B[pos2]);
  for (int i = pos1  + 1; i < n + 1; i++) {
    if (A[i] > max_ele)
      cache_ele = max(findJlis(i, pos2) + 1, cache_ele);
  }
  for (int i = pos2  + 1; i < m + 1; i++) {
    if (B[i] > max_ele)
      cache_ele = max(findJlis(pos1, i) + 1, cache_ele);
  }
  return cache_ele;
}


void JLIS() {
  cin >> n >> m;
  A[0] = -1000000000000;
  B[0] = -1000000000000;
  for (int i = 0; i < n; i++) {
    cin >> A[i + 1];
  }
  for (int i = 0; i < m; i++) {
    cin >> B[i + 1];
  }
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      cache[i][j] = -1;
    }
  }
  int max_length = 0;
  for (int i = 0; i < n + 1; i++) {
    for (int j = 0; j < m + 1; j++) {
      max_length = max(max_length, findJlis(i, j));
    }
  }
  cout << max_length - 2 << endl;
}
