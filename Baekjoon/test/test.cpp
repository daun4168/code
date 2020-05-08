#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <cxxabi.h>
#include <forward_list>
#include "../../IODefault.h"


using namespace daun;

Vector<int> make_vector(){
  return Vector<int>(3, 10);
}

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


  Vector<Vector<int>> v4;
  v4.push_back(move(make_vector()));

  std::vector<int> vv;
  std::forward_list<int> flist;
  vv.erase( std::remove(vv.begin(), vv.end(), 1234), vv.end() );
  std::remove(flist.begin(), flist.end(), 1234);
}


