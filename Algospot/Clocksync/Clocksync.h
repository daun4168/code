#ifndef CLOCKSYNC_H
#define CLOCKSYNC_H

class Clocksync {
public:
  Clocksync();
  void pressClock(int clock[16], int num_swich, int num_press_swich);
private:
  const int switch_[10][6] =
  { {0,1,2,-1}, {3,7,9,11, -1},{4,10,14,15, -1}, {0,4,5,6,7, -1}, {6,7,8,10,12, -1},
  {0,2,14,15, -1},{3,14,15, -1},{4,5,7,14,15, -1},{1,2,3,4,5, -1},{3,4,5,9,13, -1} };
  int clock_[16];
  int min_press_;
};

#endif // !CLOCKSYNC_H