#include "Clocksync.h"
#include <iostream>

using namespace std;

Clocksync::Clocksync() {
  int temp;
  for (int i = 0; i < 16; i++) {
    cin >> temp;
    clock_[i] = temp % 12;
  }
  min_press_ = 100;
  pressClock(clock_, 0, 0);
  if (min_press_ == 100) {
    cout << -1 << endl;
  } else {
    cout << min_press_ << endl;
  }
}

void Clocksync::pressClock(int clock[16], int num_swich, int num_press_swich) {
  bool is_all0 = true;
  for (int i = 0; i < 16; i++) {
    if (clock[i] != 0)
      is_all0 = false;
  }
  if (is_all0) {
    if (num_press_swich < min_press_) {
      min_press_ = num_press_swich;
      return;
    }
  }
  if (num_swich == 10)
    return;
  for (int i = 0; i < 4; i++) {
    pressClock(clock, num_swich + 1, num_press_swich + i);
    for (int k = 0; switch_[num_swich][k] != -1; k++) {
      clock[switch_[num_swich][k]] = (clock[switch_[num_swich][k]] + 3) % 12;
    }
  }
}
