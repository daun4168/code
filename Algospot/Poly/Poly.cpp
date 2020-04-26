#include <iostream>

using namespace std;

#ifndef WIN32
#include <inttypes.h>
typedef int64_t __int64;
#endif // !WIN32

int main() {
  __int64 poly[101][101];
  for (int i = 0; i <= 100; i++) {
    poly[i][0] = 1;
  }
  poly[1][1] = 1;
  for (int n = 2; n <= 100; n++) {
    for (int i = 1; i <= n; i++) {
      poly[n][i] = 0;
      if (i == n) {
        poly[n][i] = 1;
        continue;
      }
      int j = 1;
      while (i+j <= n) {
        poly[n][i] = ((i + j - 1) * poly[n - i][j] + poly[n][i]) % 10000000;
        j++;
      }
    }
  }
  int sum_poly[101];
  for (int n = 1; n <= 100; n++) {
    sum_poly[n] = 0;
    for (int i = 1; i <= n; i++) {
      sum_poly[n] = (sum_poly[n] + poly[n][i]) % 10000000;
    }
  }
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    int n;
    cin >> n;
    cout << sum_poly[n] << '\n';
  }
  return 0;
}

