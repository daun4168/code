#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include "../../IODefault.h"


using namespace daun;


int main() {
  Vector<int> v1;
  v1.push_back(2);
  v1.push_back(5);
  v1.push_back(3);
  v1.push_back(4);

  // std::sort(v1.begin(), v1.end());

  Vector<int> v2(move(v1));

  std::remove(v2.begin(), v2.end(), 3), v2.end();

  // std::cout << v2 << std::endl;


 //  v.push_back(v1);
  // int a = 10;
  // std::cout << a << std::endl;

  std::vector<int> v;
  v.size();

  std::deque<int> d;
  d.size();
}


