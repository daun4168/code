#include <iostream>
#include <algorithm>

using namespace std;

void PI();

inline int getint() {
  int ret = 0, ch;
  for (ch = getchar(); ch < '0' || ch > '9'; ch = getchar());
  for (ret = ch - '0', ch = getchar(); ch >= '0' && ch <= '9'; ch = getchar()) {
    ret = ret * 10 + ch - '0';
  }

  return ret;
}

int main() {
 // std::ios::sync_with_stdio(false);
  int test_case = getint();
  for (int i = 0; i < test_case; i++) {
    PI();
  }
  return 0;

}

int length;
int number[10000];
int cache[10000];

bool isAllSame(int i1, int i2) {
  for (int i = i1 + 1; i < i2; i++) {
    if (number[i1] != number[i]) return false;
  }
  return true;
}

bool isMonotone(int i1, int i2) {
  if (number[i1 + 1] == number[i1] + 1) {
    for (int i = i1 + 2; i < i2; i++) {
      if (number[i] != number[i - 1] + 1) return false;
    }
    return true;
  } else if (number[i1 + 1] == number[i1] - 1) {
    for (int i = i1 + 2; i < i2; i++) {
      if (number[i] != number[i - 1] - 1) return false;
    }
    return true;
  }
  return false;
}

bool isAlternately(int i1, int i2) {
  if (i2 - i1 == 3) {
    if (number[i1] == number[i1 + 2]) return true;
    return false;
  }
  if (i2 - i1 == 4) {
    if (number[i1] == number[i1 + 2] && number[i1 + 1] == number[i1 + 3]) 
      return true;
    return false;
  }
  if (i2 - i1 == 5) {
    if (number[i1] == number[i1 + 2] && number[i1] == number[i1 + 4]
      && number[i1 + 1] == number[i1 + 3] )  return true;
    return false;
  }
}

bool isEqualDiffer(int i1, int i2) {
  int equal_difference = number[i1 + 1] - number[i1];
  for (int i = i1 + 2; i < i2; i++) {
    if (number[i] - number[i - 1] != equal_difference) return false;
  }
  return true;
}

int difficulty(int i1,int i2) {
  if (isAllSame(i1, i2)) return 1;
  if (isMonotone(i1, i2)) return 2;
  if (isAlternately(i1, i2)) return 4;
  if (isEqualDiffer(i1, i2)) return 5;
  return 10;
}


int pi(int pos) {
  if (pos == length) return 0;
  if (pos > length - 3) return 100000;
  int& ref = cache[pos];
  if (ref != -1) return ref;
  ref =  min({ difficulty(pos, pos + 3) + pi(pos+3), difficulty(pos, pos + 4) + pi(pos + 4)
    , difficulty(pos, pos + 5 ) + pi(pos + 5)});
  return ref;
}


void PI() {
  length = 0;
  int ch;
  while(true) {
    ch = getchar();
    if (ch == '\n') break;
    number[length] = ch;
    cache[length] = -1;
    length++;
  }
  cout << pi(0) << endl;
}
