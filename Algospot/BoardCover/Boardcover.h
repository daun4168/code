#ifndef BOARDCOVER_H
#define BOARDVOVER_H

class Boardcover {
public:
  Boardcover();
  int numOfCases(bool[20][20]);
private:
  bool is_white_[20][20]; //H W
  int h_, w_;
};

#endif // !BOARDCOVER_H

