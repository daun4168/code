#include <iostream>
#include <cstring>

using namespace std;

int Answer;
char mirror[1000][1000];
bool visit[1000][1000];

enum dir {LEFT, RIGHT, TOP, BOTTOM};

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  int T, test_case;
  // freopen("mirror_room_input.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> mirror[i];
    }

    memset(visit, false, sizeof(visit));

    bool isloop = false;
    dir state = LEFT;
    int x = 0;
    int y = 0;

    
    while (true) {
      if (x < 0 || x >= N || y < 0 || y >= N) {
        break;
      }
      visit[y][x] = true;

      if (state == LEFT) {
        if (mirror[y][x] == '0') {
          x = x + 1;
        }
        else if (mirror[y][x] == '1') {
          y = y - 1;
          state = BOTTOM;
        }
        else if (mirror[y][x] == '2') {
          y = y + 1;
          state = TOP;
        }
      }
      else if (state == RIGHT) {
        if (mirror[y][x] == '0') {
          x = x - 1;
        }
        else if (mirror[y][x] == '1') {
          y = y + 1;
          state = TOP;
        }
        else if (mirror[y][x] == '2') {
          y = y - 1;
          state = BOTTOM;
        }
      }
      else if (state == TOP) {
        if (mirror[y][x] == '0') {
          y = y + 1;
        }
        else if (mirror[y][x] == '1') {
          x = x - 1;
          state = RIGHT;
        }
        else if (mirror[y][x] == '2') {
          x = x + 1;
          state = LEFT;
        }
      }
      else if (state == BOTTOM) {
        if (mirror[y][x] == '0') {
          y = y - 1;
        }
        else if (mirror[y][x] == '1') {
          x = x + 1;
          state = LEFT;
        }
        else if (mirror[y][x] == '2') {
          x = x - 1;
          state = RIGHT;
        }
      }
    }
    if (isloop) {
      Answer = -1;
    }
    else {
      Answer = 0;
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (visit[i][j] && mirror[i][j] != '0')
            Answer++;
        }
      }
    } 
    cout << "Case #" << test_case + 1 << endl;
    cout << Answer << endl;
  }
  return 0;
}
