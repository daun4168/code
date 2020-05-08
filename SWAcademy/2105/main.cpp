#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

template <typename T, typename U>
auto max(T x, U y) -> decltype(x > y ? x : y) {
  return x > y ? x : y;
}

template <typename T, typename U>
auto min(T x, U y) -> decltype(x < y ? x : y) {
  return x < y ? x : y;
}

template <typename T>
constexpr T pow(const T x, unsigned const n) {
  return n == 0 ? 1
                : n % 2 == 0 ? pow(x * x, n / 2) : pow(x * x, (n - 1) / 2) * x;
}

template <typename T>
void memset(T *s, T c, unsigned long n) {
  while (n--) *s++ = c;
}

constexpr int MAX_N = 20;
constexpr int MAX_DESSERT_NUM = 101;

int map[MAX_N][MAX_N];
bool check[MAX_DESSERT_NUM];
int T, N;
int testcase;

int top_x = 0;
int top_y = 0;
int left_x = 0;
int left_y = 0;
int right_x = 0;
int right_y = 0;

int calc_max_dessert();
int max_dessert_left_point();
int max_dessert_right_point();
int max_dessert();

int calc_max_dessert() {
  int max_dessert_num = -1;
  for (int y = 0; y < N; y++) {
    for (int x = 0; x < N; x++) {
      top_x = x;
      top_y = y;
      max_dessert_num = max(max_dessert_num, max_dessert_left_point());
    }
  }
  return max_dessert_num;
}

int max_dessert_left_point() {
  int max_dessert_num = -1;
  for (int y = top_y + 1, x = top_x - 1; y < N && x >= 0; y++, x--) {
    left_x = x;
    left_y = y;
    max_dessert_num = max(max_dessert_num, max_dessert_right_point());
  }
  return max_dessert_num;
}

int max_dessert_right_point() {
  int max_dessert_num = -1;
  for (int y = top_y + 1, x = top_x + 1; y < N && x < N; y++, x++) {
    right_x = x;
    right_y = y;
    max_dessert_num = max(max_dessert_num, max_dessert());
  }
  return max_dessert_num;
}

int max_dessert() {
  int bottom_x = right_x - (top_x - left_x);
  int bottom_y = right_y + (left_y - top_y);

  if (bottom_x < 0 || bottom_x >= N || bottom_y < 0 || bottom_y >= N) {
    return -1;
  }
  int dessert_num = 0;

  memset(check, false, sizeof(check));
  for (int x = top_x, y = top_y; x < right_x && y < right_y; x++, y++) {
    if (check[map[y][x]]) return -1;
    check[map[y][x]] = true;
    dessert_num++;
  }

  for (int x = right_x, y = right_y; x > bottom_x && y < bottom_y; x--, y++) {
    if (check[map[y][x]]) return -1;
    check[map[y][x]] = true;
    dessert_num++;
  }

  for (int x = bottom_x, y = bottom_y; x > left_x && y > left_y; x--, y--) {
    if (check[map[y][x]]) return -1;
    check[map[y][x]] = true;
    dessert_num++;
  }

  for (int x = left_x, y = left_y; x < top_x && y > top_y; x++, y--) {
    if (check[map[y][x]]) return -1;
    check[map[y][x]] = true;
    dessert_num++;
  }

  return dessert_num;
}

int main() {
  freopen("sample_input.txt", "r", stdin);
  setbuf(stdout, NULL);

  scanf("%d", &T);
  for (testcase = 1; testcase <= T; ++testcase) {
    int answer = 0;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        scanf("%d", &map[i][j]);
      }
    }
    answer = calc_max_dessert();

    printf("#%d %d\n", testcase, answer);
  }
  return 0;
}