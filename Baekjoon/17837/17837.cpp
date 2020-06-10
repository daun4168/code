#include <iostream>

using std::cin, std::cout, std::endl;

constexpr int MAX_N = 12;  // 4~
constexpr int MAX_K = 10;  // 4~

int N, K;
int map[MAX_N + 2][MAX_N + 2];

int xs[MAX_K];
int ys[MAX_K];
int dirs[MAX_K];

int dirx[] = {0, 1, -1, 0, 0};
int diry[] = {0, 0, 0, -1, 1};

enum Color{
  WHITE = 0,
  RED = 1,
  BLUE = 2
};

enum Dir{
  RIGHT = 1,
  LEFT = 2,
  UP = 3,
  DOWN = 4
};

int main() {
  cin >> N >> K;

  for (int y = 0; y <= N + 1; y++) {
    for (int x = 0; x <= N + 1; x++) {
      map[y][x] = BLUE;
    }
  }


  for (int y = 1; y <= N; y++) {
    for (int x = 1; x <= N; x++) {
      cin >> map[y][x];
    }
  }

  for (int k = 0; k < K; k++) {
    cin >> ys[k] >> xs[k] >> dirs[k];
  }

  int turn_num = 0;

  while(turn_num < 1000){
    turn_num++;

    for(int k = 0;k<K;k++){
      int new_x = xs[k] + dirx[dirs[k]];
      int new_y = ys[k] + diry[dirs[k]];
      
      int color = map[new_y][new_x];

      if(color == BLUE){
        if(dirs[k] == LEFT) dirs[k] = RIGHT;
        else if(dirs[k] == RIGHT)dirs[k] = LEFT;
        else if(dirs[k] == UP)dirs[k] = DOWN;
        else if(dirs[k] == DOWN)dirs[k] = UP;


      } else if(color == RED){

      } else if(color == WHITE){
        
      }




    }



  }

PRINT:
  if(turn_num <= 1000){
    cout << turn_num << endl;
  } else {
    cout << -1 << endl;
  }

  return 0;
}