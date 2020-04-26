#include "Boardcover.h"
#include <iostream>

using namespace std;

Boardcover::Boardcover() {
  int num_white = 0;
  char input;
  cin >> h_ >> w_;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      is_white_[i][j] = false;
    }
  }
  for (int i = 0; i < h_; i++) {
    for (int j = 0; j < w_; j++) {
      cin >> input;
      if (input == '.') {
        is_white_[i][j] = true;
        num_white++;
      } else if (input == '#') {
        is_white_[i][j] = false;
      }
    }
  }
  if (num_white > 50 || h_ > 20 || w_ > 20) {
    cout << 0 << endl;
    return;
  }
  if ((num_white % 3) != 0) {
    cout << 0 << endl;
  } else {
    cout << numOfCases(is_white_) << endl;
  }
}

int Boardcover::numOfCases(bool is_white[20][20]) {
  bool is_first = true;
  int first_h, first_w;
  int case_num = 0;
  for (int i = 0; i < h_; i++) {
    for (int j = 0; j < w_; j++) {
      if (is_white[i][j]&&is_first) {
        is_first = false;
        first_h = i;
        first_w = j;
      }
    }
  }
  if (is_first)
    return 1;
  const int cover_type[4][3][2] = {
    { { 0,0 },{ 0 ,1 },{ 1, 0 } },    
    { { 0,0 },{ 0, 1 },{ 1, 1 } },    
    { { 0,0 },{ 1, 0 },{ 1, 1 } },    
    { { 0,0 },{ 1, 0 },{ 1, -1 } }    
  };
  for (int i = 0; i < 4; i++) {
    if (is_white[first_h + cover_type[i][1][0]][first_w + cover_type[i][1][1]]
      && is_white[first_h + cover_type[i][2][0]][first_w + cover_type[i][2][1]]) {
      is_white[first_h + cover_type[i][0][0]][first_w + cover_type[i][0][1]] = false;
      is_white[first_h + cover_type[i][1][0]][first_w + cover_type[i][1][1]] = false;
      is_white[first_h + cover_type[i][2][0]][first_w + cover_type[i][2][1]] = false;
      case_num += numOfCases(is_white);
      is_white[first_h + cover_type[i][0][0]][first_w + cover_type[i][0][1]] = true;
      is_white[first_h + cover_type[i][1][0]][first_w + cover_type[i][1][1]] = true;
      is_white[first_h + cover_type[i][2][0]][first_w + cover_type[i][2][1]] = true;
    }
  }
  return case_num;
}
