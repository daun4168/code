#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

typedef pair<int, int> ipair;

int xs[10000];
int ys[10000];
int hs[10000];
ipair yhs[10000];

#define INT_MAX 987654321

int main() {
  int i;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("memo.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
      int x, y, h;
      cin >> x >> y >> h;
      yhs[i] = { y, h };
    }
    sort(yhs, yhs + N);
    for (int i = 0; i < N; i++) {
      ys[i] = yhs[i].first;
      hs[i] = yhs[i].second;
    }
    int min_broken_line_num = INT_MAX;

    for (int i = 0; i < N; i++) {
      int up = ys[i];
      int down = ys[i] - hs[i];
      int broken_line_num = 0;

      // expand up
      for (int j = i + 1; j < N; j++) {
        if (hs[j] <= ys[j] - up) {
          up = ys[j];
          continue;
        } 
        if (ys[j] < up) {
          broken_line_num++;
        }
        up = up + hs[j];
      }

      // expand down
      for (int j = i - 1; j >= 0; j--) {
        if (hs[j] <= down - ys[j]) {
          down = ys[j];
          continue;
        }
        if (ys[j] > down) {
          broken_line_num++;
        }
        down = down - hs[j];
      }
      min_broken_line_num = min(min_broken_line_num, broken_line_num);
    }


    for (int i = 0; i < N; i++) {
      int up = ys[i] + hs[i];
      int down = ys[i];
      int broken_line_num = 0;

      // expand up
      for (int j = i + 1; j < N; j++) {
        if (hs[j] <= ys[j] - up) {
          up = ys[j];
          continue;
        }
        if (ys[j] < up) {
          broken_line_num++;
        }
        up = up + hs[j];
      }

      // expand down
      for (int j = i - 1; j >= 0; j--) {
        if (hs[j] <= down - ys[j]) {
          down = ys[j];
          continue;
        }
        if (ys[j] > down) {
          broken_line_num++;
        }
        down = down - hs[j];
      }
      min_broken_line_num = min(min_broken_line_num, broken_line_num);
    }

    cout << "Case #" << test_case + 1 << endl;
    cout << min_broken_line_num << endl;

  }
  return 0;
}