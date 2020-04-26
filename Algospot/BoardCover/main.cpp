#include <iostream>
#include "Boardcover.h"

int main() {
  freopen("sample_input.txt", "r", stdin);
  int testcase;
  std::cin >> testcase;
  for (int i = 0; i < testcase; i++) {
    Boardcover* b = new Boardcover();
    delete b;
  }
}