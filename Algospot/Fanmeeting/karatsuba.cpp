#include "karatsuba.h"
#include <cmath>
#include <algorithm>
using namespace std;

std::vector<int> connect(const std::vector<int>& a, const std::vector<int> &b, int k) {
  vector<int> c(max({ b.size() + k, a.size() }), 0);
  for (int i = 0; i < a.size(); i++) {
    c[i] += a[i];
  }
  for (int i = 0; i < b.size(); i++) {
    c[i + k] += b[i];
  }
  return c;
}

std::vector<int> sub(const std::vector<int>& a, const std::vector<int> &b) {
  vector<int> c(a);
  for (int i = 0; i < b.size(); i++) {
    c[i] -= b[i];
  }
  return c;
}

std::vector<int> mul(const std::vector<int>& a, const std::vector<int> &b) {
  vector<int>c(a.size() + b.size() + 1, 0);
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      c[i + j] += a[i] * b[j];
    }
  }
  //  normalize(c);
  return c;
}

void normalize(std::vector<int>& num) {
  num.push_back(0);
  for (int i = 0; i < num.size() - 1; i++) {
    if (num[i] < 0) {
      int borrow = abs((num[i] + 9)) / 10;
    } else {
      num[i + 1] += num[i] / 10;
      num[i] %= 10;
    }
  }
  while (num.back() == 0) {
    num.pop_back();
  }
}

std::vector<int> karatsuba(const std::vector<int>& a, const std::vector<int>& b) {
  int a_size = a.size();
  int b_size = b.size();
  if (a_size < b_size) return karatsuba(b, a);
  if (a_size == 0 || b_size == 0) return vector<int>();
  if (a_size < 50) return mul(a, b);
  int mid = a_size / 2;
  vector<int> a0(a.begin(), a.begin() + mid);
  vector<int> a1(a.begin() + mid, a.end());
  vector<int> b0(b.begin(), b.begin() + min({ b_size, mid }));
  vector<int> b1(b.begin() + min({ b_size, mid }), b.end());
  vector<int>z2 = karatsuba(a1, b1);
  vector<int>z0 = karatsuba(a0, b0);
  vector<int>z1 = karatsuba(connect(a0, a1, 0), connect(b0, b1, 0));
  z1 = sub(z1, z0);
  z1 = sub(z1, z2);
  vector<int>result(z0);
  result = connect(result, z1, mid);
  result = connect(result, z2, mid * 2);
  return result;
}
