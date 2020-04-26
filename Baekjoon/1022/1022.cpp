#include <iostream>
#include <iomanip>

using namespace std;

int main() {
  int xy, x, y;
  x = 0;
  y = 0;
  xy = 0;
  int r1, c1, r2, c2;
  cin >> r1 >> c1 >> r2 >> c2;

  int max_val = 0;
  int* arr = new int[(r2 - r1 + 1) * (c2 - c1 + 1)];
  int i = 0;
  int val;

  for (int y = r1; y <= r2; y++) {
    for (int x = c1; x <= c2; x++) {
      int xy = abs(x) > abs(y) ? abs(x) : abs(y);
      
      if (y >= x) {
        val = ((2 * xy + 1) * (2 * xy + 1)) - (2 * xy) + x + y;
      }
      else {
        val = ((2 * xy + 1) * (2 * xy + 1)) - (6 * xy) - x - y;
      }

      arr[i] = val;
      i++;
      if (val > max_val) {
        max_val = val;
      }
    }
  }

  int max_len = 0;
  while (max_val>0) {
    max_val /= 10;
    max_len++;
  }

  i = 0; 
  for (int y = r1; y <= r2; y++) {
    for (int x = c1; x <= c2; x++) {
      cout << setw(max_len) << arr[i] << ' ';
      i++;
    }
    cout << endl;
  }
  return 0;
}