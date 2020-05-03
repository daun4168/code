#include <iostream>
#include <queue>

constexpr int MAX_N = 100;
constexpr int MAX_K = 100;
constexpr int MAX_L = 100;
constexpr int MAX_MOVE = 10500;

enum {
  RIGHT = 0,
  DOWN = 1,
  LEFT = 2,
  UP = 3,
};
constexpr int dir_x[4] = {1, 0, -1, 0};
constexpr int dir_y[4] = {0, 1, 0, -1};
char dirs[MAX_MOVE];

// 'A' : APPLE
// '.' : BLANK
// 'D' : 뱀

struct Dot{
  Dot(int x, int y) :x(x), y(y){}
  int x;
  int y;
};

class Board {
 public:
  int N;
  int dir;
  int x;
  int y;
  std::queue<Dot> snake;
  char map[MAX_N][MAX_N];

  Board() {
    initArray(*map, '.', MAX_N * MAX_N);
    dir = RIGHT;
    snake.push(Dot(x, y));
    map[0][0] = 'D';
  }

  // return is dead;
  bool move() {
    x = x + dir_x[dir];
    y = y + dir_y[dir];

    if(x < 0 || x >= N || y < 0 || y >= N){
      return true;
    }
    
    if(map[y][x] == 'D'){
      return true;
    } 

    if(map[y][x] == '.'){
      Dot d = snake.front();
      snake.pop();
      map[d.y][d.x] = '.';
    }

    map[y][x] = 'D';
    snake.push(Dot(x, y));

    return false; 
  }

  void rotateRight() {
    dir = (dir + 1) % 4;
  }

  void rotateLeft() {
    dir = (dir + 3) % 4;
  }
};

int main() {
  // freopen("sample_input.txt", "r", stdin);
  Board b;
  std::cin >> b.N;
  int K;
  std::cin >> K;
  for (int k = 0; k < K; k++) {
    int x, y;
    std::cin >> y >> x;
    b.map[y - 1][x - 1] = 'A';
  }

  int L;
  std::cin >> L;
  for (int l = 0; l < L; l++) {
    int X;
    char C;
    std::cin >> X >> C;
    dirs[X] = C;
  }

  int time = 1;
  for (; time < MAX_MOVE; time++) {
    bool is_dead = b.move();
    if (is_dead) break;

    if (dirs[time] == 'L') {
      b.rotateLeft();
    } else if (dirs[time] == 'D') {
      b.rotateRight();
    }
  }
  std::cout << time << std::endl;
  return 0;
}