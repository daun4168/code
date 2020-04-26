#include <iostream>

using namespace std;

int n;
int triangle[100][100];

//<path num, path length>
typedef pair<int, int> path;

path cache[100][100];
path maxPathNum(int height, int width);

int main() {
  std::ios::sync_with_stdio(false);
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        cin >> triangle[i][j];
        cache[i][j] = { -1, -1 };
      }
    }
    cout << maxPathNum(0, 0).first << endl;
  }
  return 0;
}

path maxPathNum(int height, int width) {
  if (height == n - 1) return { 1, triangle[height][width] };

  int& path_num = cache[height][width].first; 
  int& path_length = cache[height][width].second;
  if (path_num != -1) return cache[height][width];

  path left = maxPathNum(height + 1, width);
  path right = maxPathNum(height + 1, width + 1);
  if (left.second == right.second) {
    path_length = left.second;
    path_num = left.first + right.first;
  } else if (left.second > right.second) {
    path_length = left.second;
    path_num = left.first;
  } else {
    path_length = right.second;
    path_num = right.first;
  }
  path_length += triangle[height][width];
  return cache[height][width];
}
