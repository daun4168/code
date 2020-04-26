#include <iostream>
#include "Clocksync.h"


int main() {
  int testcase;
  std::cin >> testcase;
  for (int i = 0; i < testcase; i++) {
    Clocksync* b = new Clocksync();
    delete b;
  }
}