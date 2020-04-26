#include <iostream>
#include <vector>

class Fence {
public:
  Fence();
private:
  void maxArea(vector<int>);
  void saveMax(int);
  vector<int> fence_;
  int board_num_;
  int max_area_;
};
