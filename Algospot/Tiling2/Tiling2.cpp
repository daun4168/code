#include <iostream>

using namespace std;

int main() {
  std::ios::sync_with_stdio(false);
  int tile[101];
  tile[1] = 1;
  tile[2] = 2;
  for (int i = 3; i <= 100; i++) {
    tile[i] = (tile[i-2] + tile[i-1]) % 1000000007;
  }
  int test_case;
  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    int n;
    cin >> n;
    cout << tile[n] << '\n';
  }
  return 0;
}

