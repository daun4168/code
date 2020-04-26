#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;


double snail(int n, int m);
double combination(int n, int k);
double combination_cache[1000][1000];

int main() {
  int test_case;
  cin >> test_case;
  for (int i = 0; i < 1000; i++) {
    for (int j = 0; j < 1000; j++) {
      combination_cache[i][j] = -1.0;
    }
  }
  for (int t = 0; t < test_case; t++) {
    int n, m;
    cin >> n >> m;
    cout << fixed << setprecision(10) << snail(n, m) << '\n';
  }
  return 0;
}

double snail(int n, int m) {
  if (n <= m) return 1;
  if (n > 2 * m) return 0;
  double sum = 0;
  for (int i = 0; i < n - m; i++) {
    sum += combination(m, i) * pow(3.0 / 4.0, i) * pow(1.0 / 4.0, m - i);
  }
  return 1 - sum;
}

double combination(int n, int k) {
  double& ref = combination_cache[n][k];
  if (ref != -1.0) return ref;
  if (n == k || k == 0) {
    ref = 1;
  } else {
    ref = combination(n - 1, k - 1) + combination(n - 1, k);
  } 
  return ref;
}
