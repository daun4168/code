#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>
#include "karatsuba.h"

using namespace std;

//M : true, F : false;

int main() {
  freopen("sample_input.txt", "r", stdin);
  int test_case_num;
  cin >> test_case_num;
  for (int test_case = 0; test_case < test_case_num; test_case++) {
    vector<int> member, fan;
    char temp;
    cin.ignore(INT_MAX, '\n');
    while (cin.peek() != '\n') {
      cin.get(temp);
      if (temp == 'F') {
        member.push_back(0);
      } else {
        member.push_back(1);
      }
    }
    cin.ignore(INT_MAX, '\n');
    while (cin.peek() != '\n') {
      cin.get(temp);
      if (temp == 'F') {
        fan.push_back(0);
      } else {
        fan.push_back(1);
      }
    }
    int HugNum = 0;
    reverse(member.begin(), member.end());
    vector<int> result = karatsuba(member, fan);

    for (int i = member.size() - 1; i < fan.size(); i++) {
      if (!result[i]) HugNum++;
    }
    cout << HugNum << endl;
  }
  return 0;
}

