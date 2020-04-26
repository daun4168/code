#include <iostream>
#include <stack>
#include <climits>
#include <string>

using namespace std;

int main() {
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    stack<int> brackets;
    string line;
    cin >> line;
    bool isOk = true;
    for (int i = 0; i < line.size(); i++) {
      switch (line[i]) {
      case '(': {
        brackets.push(1);
        break;
      }
      case '{': {
        brackets.push(2);
        break;
      }
      case '[': {
        brackets.push(3);
        break;
      }
      case ')': {
        if (!brackets.empty() && brackets.top() == 1) {
          brackets.pop();
        } else {
          isOk = false;
        }
        break;
      }
      case '}': {
        if (!brackets.empty() && brackets.top() == 2) {
          brackets.pop();
        } else {
          isOk = false;
        }
        break;
      }
      case ']': {
        if (!brackets.empty() && brackets.top() == 3) {
          brackets.pop();
        } else {
          isOk = false;
        }
        break;
      }
      default: {
        break;
      }
      }
      if (!isOk) break;
    }
    if (!brackets.empty()) isOk = false;
    if (isOk) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}