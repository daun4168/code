#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <cxxabi.h>
#include <forward_list>
#include "../../IODefault.h"


using namespace daun;

int main() {

  Vector<int> v1;

  v1.push_back(2);
  v1.push_back(5);
  v1.push_back(3);
  v1.push_back(4);

  Vector<int> v2(move(v1));

  v1.push_back(1);
  v1.push_back(2);
  v1.push_back(3);
  v1.push_back(4);
  v1.push_back(5);
  v1.push_back(6);

  std::cout << v1 << std::endl;
  std::cout << v2 << std::endl;

  v1.resize(10);
  std::cout << v1 << std::endl;

  v1.resize(5);
  std::cout << v1 << std::endl;

  v1.assign(7, 7);
  std::cout << v1 << std::endl;

  v1.assign(3, 3);
  std::cout << v1 << std::endl;

}


