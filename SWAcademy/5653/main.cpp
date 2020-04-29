#include <iostream>
#include <cstring>

using namespace std;

int N, M, K;
int H, W;
int** v;

int main() {
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    cin >> N >> M >> K;
    H = N + 2 * K;
    W = M + 2 * K;
    v = new int*[H];
    for(int h = 0;h<H;h++){
      v[h] = new int[W];
      memset(v[h], 0, sizeof(int) * W);
    }
    for (int n = 0; n < N; n++) {
      for (int m = 0; m < M; m++) {
        cin >> v[n][m];
      }
    }

    for(int h = 0;h<H;h++){
      delete[] v[h];
    }
    delete[] v;
  }
}