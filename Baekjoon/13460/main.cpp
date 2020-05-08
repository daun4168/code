#include <iostream>

template<typename T>
constexpr const T& max (const T& a, const T& b) {
  return (a > b) ? a : b;
}

template<typename T>
constexpr const T& min (const T& a, const T& b) {
  return !(a < b) ? b : a;
}

template <typename T>
constexpr const T pow(const T x, unsigned const n) {
  return n == 0 ? 1
                : n % 2 == 0 ? pow(x * x, n / 2) : pow(x * x, (n - 1) / 2) * x;
}

template <typename T>
void memset(T *s, const T& c, unsigned long n) {
  while (n--) *s++ = c;
}

void memcpy(void *dest, const void *src, unsigned long count) {
  char *tmp = static_cast<char*>(dest);
  const char *s = static_cast<const char*>(src);
  while (count--) *tmp++ = *s++;
}

constexpr int MAX_N = 10;
constexpr int MAX_M = 11;
constexpr int NOT_POSSIBLE = 1000;

constexpr int dx[4] = {1, -1, 0, 0};
constexpr int dy[4] = {0, 0, 1, -1};

int N, M;
char map[MAX_N][MAX_M];

int calc_min_move(int red_x, int red_y, int blue_x, int blue_y, int move_num) {
  if (move_num > 10) return NOT_POSSIBLE;
  int min_num = NOT_POSSIBLE;

  for (int i = 0; i < 4; i++) {
    bool is_red_in = false;
    bool is_blue_in = false;
    int new_red_x = red_x;
    int new_red_y = red_y;
    int new_blue_x = blue_x;
    int new_blue_y = blue_y;

    while (true) {
      bool is_move = false;
      if (map[new_blue_y + dy[i]][new_blue_x + dx[i]] == 'O') {
        is_blue_in = true;
        break;
      }

      if (map[new_blue_y + dy[i]][new_blue_x + dx[i]] == '.' &&
          !(new_blue_x + dx[i] == new_red_x &&
            new_blue_y + dy[i] == new_red_y)) {
        new_blue_x += dx[i];
        new_blue_y += dy[i];
        is_move = true;
      }

      if (!is_red_in && map[new_red_y + dy[i]][new_red_x + dx[i]] == 'O') {
        is_red_in = true;
        new_red_x = 0;
        new_red_y = 0;
        is_move = true;
      }

      if (!is_red_in && map[new_red_y + dy[i]][new_red_x + dx[i]] == '.' &&
          !(new_red_x + dx[i] == new_blue_x &&
            new_red_y + dy[i] == new_blue_y)) {
        new_red_x += dx[i];
        new_red_y += dy[i];
        is_move = true;
      }
      if (!is_move) break;
    }

    if (is_blue_in) continue;
    if (is_red_in) {
      // min_num = min_num < move_num ? min_num : move_num;
      min_num = min(min_num, move_num);
      continue;
    }

    if (new_blue_x == blue_x && new_blue_y == blue_y && new_red_x == red_x &&
        new_red_y == red_y) {
      continue;
    }
    int n = calc_min_move(new_red_x, new_red_y, new_blue_x, new_blue_y, move_num + 1);
    // min_num = min_num < n ? min_num : n;
    min_num = min(min_num, n);
  }
  return min_num;
}

int main() {
  // freopen("sample_input.txt", "r", stdin);
  int T = 1;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> M;

    for (int y = 0; y < N; y++) {
      for(int x = 0;x<M;x++){
        std::cin >> map[y][x];
      }
    }

    int red_x;
    int red_y;
    int blue_x;
    int blue_y;

    for (int y = 0; y < N; y++) {
      for (int x = 0; x < M; x++) {
        if (map[y][x] == 'R') {
          red_x = x;
          red_y = y;
          map[y][x] = '.';
        } else if (map[y][x] == 'B') {
          blue_x = x;
          blue_y = y;
          map[y][x] = '.';
        }
      }
    }

    int min_move = calc_min_move(red_x, red_y, blue_x, blue_y, 1);
    if (min_move == NOT_POSSIBLE) min_move = -1;

    std::cout << min_move <<  std::endl;

    // int answer;
    // std::cin >> answer;
    // if(answer == min_move){
    //   std::cout <<"CORRECT"<< ' ' << min_move << ' ' << std::endl;
    // } else{
    //   std::cout <<"FAIL"<< ' ' << min_move<< ' '  << std::endl;
    // }
    
  }
}