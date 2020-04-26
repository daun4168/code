#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

void lis();

int main() {
  int test_case;
  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    lis();
  }
  return 0;
}

int arr_length;
int* arr;
map<int, int>cache;

int increasingNum(int pos, int prev) {
  if (pos == arr_length - 1) {
    if (prev < arr[pos]) return 1;
    else return 0;
  }
  auto find_iter = cache.find(pos * 1000000 + prev);
  if (find_iter != cache.end()) return find_iter->second;
  int temp;
  if (prev < arr[pos]) {
    temp = max(1 + increasingNum(pos + 1, arr[pos]), increasingNum(pos + 1, prev));
    cache.insert({ pos * 1000000 + prev, temp });
    return temp;
  }
  temp = increasingNum(pos + 1, prev);
  cache.insert({ pos * 1000000 + prev, temp });
  return temp;
}

void lis() {
  cache.clear();
  cin >> arr_length;
  arr = new int[arr_length];
  for (int i = 0; i < arr_length; i++) {
    int temp;
    cin >> temp;
    arr[i] = temp;
  }  
  cout << increasingNum(0, 0) << endl;
  delete[] arr;
}
