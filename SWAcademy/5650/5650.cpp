#include <cstdio>

constexpr int MAX_N = 100;

enum DIRECTION { LEFT, RIGHT, UP, DOWN };

struct Pos {
  Pos() {}
  Pos(int x, int y) : x(x), y(y) {}
  int x = 0;
  int y = 0;
  bool operator == (const Pos &Ref) const{
    return this->x == Ref.x && this->y == Ref.y;
  }
};

int N;
int map[MAX_N][MAX_N];
Pos s_pos;
Pos pos;
int dir;
int score;
bool is_first_pos;

void go() {
  if(is_first_pos){
    is_first_pos = false;
  } else if(pos == s_pos){
    return;
  } else if(pos.x < 0){
    pos.x = 0;
    dir = RIGHT;
    score++;
  } else if(pos.y < 0) {
    pos.y = 0;
    dir = DOWN;
    score++;
  } else if(pos.x >= N){
    pos.x = N - 1;
    dir = LEFT;
    score++;
  } else if(pos.y >= N){
    pos.y = N - 1;
    dir = UP;
    score++;
  }

  

  go();
}

int main() {
  freopen("sample_input.txt", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    scanf("%d", &N);

    for (int y = 0; y < N; y++) {
      for (int x = 0; x < N; x++) {
        scanf("%d", &map[y][x]);
      }
    }

    int max_score = 0;

    s_pos = Pos(0, 0);
    dir = DOWN;
    score = 0;
    is_first_pos = true;

    go();

    max_score = score;

    printf("# %d\n", max_score);
  }
  return 0;
}