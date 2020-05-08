#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_W 12
#define MAX_H 15

int N, W, H;

int min(const int a, const int b) { return a < b ? a : b; }

int count_block(const int map[MAX_H][MAX_W]) {
  int block_num = 0;
  for (int h = 0; h < H; h++) {
    for (int w = 0; w < W; w++) {
      if (map[h][w] != 0) block_num++;
    }
  }
  return block_num;
}

void copy_map(const int ori_map[MAX_H][MAX_W], int new_map[MAX_H][MAX_W]) {
  for (int h = 0; h < H; h++) {
    for (int w = 0; w < W; w++) {
      new_map[h][w] = ori_map[h][w];
    }
  }
}

void do_break(int map[MAX_H][MAX_W], int h, int w) {
  if (h < 0 || h >= H || w < 0 || w >= W) return;
  if (map[h][w] == 0) return;

  int num = map[h][w];
  map[h][w] = 0;
  for (int i = h - (num - 1); i <= h + (num - 1); i++) {
    do_break(map, i, w);
  }
  for (int i = w - (num - 1); i <= w + (num - 1); i++) {
    do_break(map, h, i);
  }
}

void start_break(int map[MAX_H][MAX_W], int marble_w) {
  for (int i = 0; i < H; i++) {
    if (map[i][marble_w] != 0) {
      do_break(map, i, marble_w);
      break;
    }
  }
}

void after_break(int map[MAX_H][MAX_W]) {
  for (int w = 0; w < W; w++) {
    int non0_num = 0;
    for (int i = H - 1; i >= 0; i--) {
      if (map[i][w] != 0) {
        int temp = map[i][w];
        map[i][w] = 0;
        map[H - non0_num - 1][w] = temp;
        non0_num++;
      }
    }
  }
}

int calc_block_num(const int map[MAX_H][MAX_W], int marble_num) {
  if (marble_num == 0) {
    return count_block(map);
  }

  int min_block_num = MAX_W * MAX_H;
  for (int i = 0; i < W; i++) {
    int new_map[MAX_H][MAX_W];
    copy_map(map, new_map);
    start_break(new_map, i);
    after_break(new_map);
    min_block_num = min(min_block_num, calc_block_num(new_map, marble_num - 1));
  }
  return min_block_num;
}

int main() {
  int T;

  freopen("sample_input.txt", "r", stdin);
  setbuf(stdout, NULL);

  scanf("%d", &T);
  for (int testcase = 1; testcase <= T; ++testcase) {
    scanf("%d %d %d", &N, &W, &H);

    int input_map[MAX_H][MAX_W];
    for (int h = 0; h < H; h++) {
      for (int w = 0; w < W; w++) {
        scanf("%d", &input_map[h][w]);
      }
    }
    int block_num = calc_block_num(input_map, N);
    printf("#%d %d\n", testcase, block_num);
  }
  return 0;
}