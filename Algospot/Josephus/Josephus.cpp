#include <iostream>
#include "clist.h"
#include <list>

using namespace std;


int main() {
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    int n, k;
    cin >> n >> k;
    clist<int> person;
    for (int i = 0; i < n; i++) {
      person.push_back(i + 1);
    }
    auto iter = person.begin();
    while (person.size() > 2) {
      iter = person.erase(iter);
      for (int i = 0; i < k - 1; i++) {
        ++iter;
      }
    }
    iter = person.begin();
    cout << *iter << " ";
    ++iter;
    cout << *iter << '\n';
  }
  return 0;
}

