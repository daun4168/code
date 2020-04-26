#include "Fence.h"
#include <iostream>
#include <algorithm>

using namespace std;

Fence::Fence() {
  cin >> board_num_;
  fence_.resize(board_num_);
  for (int i = 0; i < board_num_; i++) {
    cin >> fence_[i];
  }
  max_area_ = 0;
}

void Fence::maxArea(vector<int> fence) {
  int area;
  if (fence.size() == 0)
    return;
  if (fence.size() == 1) {
    area = fence[0];
    saveMax(area);
    return;
  }
  vector<int>::iterator min = min_element(fence.begin(), fence.end());
  
  

}

void Fence::saveMax(int data) {
  if (data > max_area_)
    max_area_ = data;
}
