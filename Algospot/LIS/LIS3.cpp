#include <iostream>
#include <vector>
#include <set>

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

void lis() {
  set<int> cache;
  int arr_length;
  cin >> arr_length;
  for (int i = 0; i < arr_length; i++) {
    int ele;
    cin >> ele;
    if (cache.find(ele) != cache.end()) continue;
    auto up = cache.upper_bound(ele);
    if (up == cache.end()) {
      cache.insert(ele);
    } else {
      cache.erase(up);
      cache.insert(ele);
    }
  }
  cout << cache.size() << endl;
}