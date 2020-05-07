#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <cxxabi.h>


template <typename T>
void destroy(T* p) {
  p->~T();
}

template <typename T>
void destroy(T* first, T* last) {
  for (; first != last; ++first) destroy(first);
}

template <typename T>
void destroy(T first, T last) {
  for (; first != last; ++first) destroy(&(*first));
}

int main() {
  // std::vector<int> v;
  // typedef int* pint;
  // auto i = pint();
  // int b = 5;
  // if(i == nullptr){
  //   std::cout << "NULL!!" << std::endl;
  // }


  int* i = nullptr;
  int* i2 = nullptr;
  auto i3 = i - i2;
  std::cout << i3 << std::endl;
}



