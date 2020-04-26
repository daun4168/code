#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
 
using namespace std;
 
int mt[8][8];
int visit[8][8];
 
int N, K;
int t, T;
 
int dfs(int x, int y) {
  if (x < 0 || x >= N || y < 0 || y >= N) return 0;
  if (visit[x][y] != -1) return visit[x][y];
   
  int max_len = 0;
 
  if (x > 0 &&  mt[x][y] > mt[x - 1][y])
    max_len = max(dfs(x - 1, y) + 1, max_len);
 
  if (x < N - 1 &&  mt[x][y] > mt[x + 1][y])
    max_len = max(dfs(x + 1, y) + 1, max_len);
 
  if (y > 0 && mt[x][y] > mt[x][y - 1])
    max_len = max(dfs(x, y - 1) + 1, max_len);
 
  if (y < N - 1&& mt[x][y] > mt[x][y + 1])
    max_len = max(dfs(x, y + 1) + 1, max_len);
 
  visit[x][y] = max_len;
  return max_len;
}
 
int main()
{
  freopen("sample_input.txt", "r", stdin);
  cin >> T;
 
  for (t = 1; t <= T; t++) {
    cin >> N >> K;
 
    int max_height = 0;
    int max_height_num = 0;
    int max_height_x[5];
    int max_height_y[5];
 
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> mt[i][j];
 
        if (mt[i][j] > max_height) {
          max_height = mt[i][j];
          max_height_x[0] = i;
          max_height_y[0] = j;
          max_height_num = 1;
        }
        else if (mt[i][j] == max_height) {
          max_height_x[max_height_num] = i;
          max_height_y[max_height_num] = j;
          max_height_num++;
        }
      }
    }
 
    int max_len = 0;
 
    for (int i = 0; i < max_height_num; i++) {
      int x = max_height_x[i];
      int y = max_height_y[i];
 
      for (int k = 0; k <= K; k++) {
        for (int k_x = 0; k_x < N; k_x++) {
          for (int k_y = 0; k_y < N; k_y++) {
            mt[k_x][k_y] -= k;
 
            memset(visit, -1, sizeof(visit));
 
            max_len = max(dfs(x, y) + 1, max_len);
 
            mt[k_x][k_y] += k;
          }
        }
      }
    }
    cout << '#' << t << ' ';
    cout << max_len << endl;
  }
  return 0;
}