#include <iostream>

constexpr int MAX_N = 20;

int N;

enum { LEFT = 1, RIGHT = 2, UP = 3, DOWN = 4 };

template <typename T>
void initArray(T* arr, T value, unsigned long size) {
  while (size--) *arr++ = value;
}

int calc_max_num(const int board[MAX_N][MAX_N], int move_num) {
  int max_num = 0;
  int new_board[MAX_N][MAX_N];

  if (move_num >= 5) {
    for (int y = 0; y < N; y++) {
      for (int x = 0; x < N; x++) {
        max_num = max_num > board[y][x] ? max_num : board[y][x];
      }
    }
    return max_num;
  }

  for (int dir = LEFT; dir <= DOWN; dir++) {
    initArray(*new_board, 0, MAX_N * MAX_N);
    if (dir == LEFT) {
      for (int y = 0; y < N; y++) {
        int new_x = 0;
        int last_num = 0;
        for (int x = 0; x < N; x++) {
          if(board[y][x] == 0) continue;
          if(board[y][x] == last_num){
            new_board[y][new_x - 1] = board[y][x] * 2;
            last_num = 0;
          } else {
            new_board[y][new_x] = board[y][x];
            last_num = board[y][x];
            new_x++;
          }
        }
      }
    } else if (dir == RIGHT) {
      for (int y = 0; y < N; y++) {
        int new_x = N-1;
        int last_num = 0;
        for (int x = N-1; x >= 0; x--) {
          if(board[y][x] == 0) continue;
          if(board[y][x] == last_num){
            new_board[y][new_x + 1] = board[y][x] * 2;
            last_num = 0;
          } else {
            new_board[y][new_x] = board[y][x];
            last_num = board[y][x];
            new_x--;
          }
        }
      }
    } else if (dir == UP) {
      for (int x = 0; x < N; x++) {
        int new_y = 0;
        int last_num = 0;
        for (int y = 0; y < N; y++) {
          if(board[y][x] == 0) continue;
          if(board[y][x] == last_num){
            new_board[new_y - 1][x] = board[y][x] * 2;
            last_num = 0;
          } else {
            new_board[new_y][x] = board[y][x];
            last_num = board[y][x];
            new_y++;
          }
        }
      }
    }else if (dir == DOWN) {
      for (int x = 0; x < N; x++) {
        int new_y = N-1;
        int last_num = 0;
        for (int y = N-1; y >= 0; y--) {
          if(board[y][x] == 0) continue;
          if(board[y][x] == last_num){
            new_board[new_y + 1][x] = board[y][x] * 2;
            last_num = 0;
          } else {
            new_board[new_y][x] = board[y][x];
            last_num = board[y][x];
            new_y--;
          }
        }
      }
    }


    int calc_num = calc_max_num(new_board, move_num + 1);
    max_num = max_num > calc_num ? max_num : calc_num;
  }
  return max_num;
}

int main() {
  // freopen("sample_input.txt", "r", stdin);
  std::cin >> N;

  int board[MAX_N][MAX_N];
  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      std::cin >> board[y][x];
    }
  }

  int max_num = calc_max_num(board, 0);

  std::cout << max_num << std::endl;
  return 0;
}