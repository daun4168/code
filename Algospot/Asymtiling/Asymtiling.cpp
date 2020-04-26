#include <iostream>

using namespace std;

int main() {
  int tile[101];
  tile[0] = 1;
  tile[1] = 1;
  tile[2] = 2;
  for (int i = 3; i <= 100; i++) {
    tile[i] = (tile[i - 2] + tile[i - 1]) % 1000000007;
  }
  int symtile[101];
  symtile[0] = 1;
  symtile[1] = 1;
  symtile[2] = 2;
  for (int i = 3; i <= 100; i++) {
    if (i % 2 == 1) {
      symtile[i] = tile[i / 2];
    } else {
      symtile[i] = (tile[i / 2 - 1] * 2) % 1000000007;
      if (i != 2) {
        symtile[i] += tile[(i-4)/2];
      }    
      symtile[i] %= 1000000007;
    }
  }
  int asymtile[101];
  for (int i = 1; i <= 100; i++) {
    if (symtile[i] > tile[i]) {
      asymtile[i] = tile[i] - symtile[i] + 1000000007;
    } else {
      asymtile[i] = (tile[i] - symtile[i]) % 1000000007;
    }
  }
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    int n;
    cin >> n;
    cout << asymtile[n] << '\n';
  }
  return 0;
}