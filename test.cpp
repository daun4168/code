#include <cstdio>

int fun(int *i) {
  *i += 7;

  return 5;
}

int main() {
  int x = 10;

  // x = x - fun(&x);
  x = -(fun(&x) - x);
  printf("%d\n", x);
}