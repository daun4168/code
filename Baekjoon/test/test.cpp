#include <algorithm>
#include <iostream>
#include <vector>
#include "../../Default.h"
#include "../../IODefault.h"

using namespace daun;

Vector<int> mkvector(){
  Vector<int> a;
  a.resize(10);
  return a;
}

int main() {

  Vector<Vector<int>> v;
  // v.push_back(Vector<int>(10, 5));
  v[0];
  // v.push_back(Vector<int>(10, 7));
  v.push_back(mkvector());
  int a = 10;
  std::cout << a;

}


