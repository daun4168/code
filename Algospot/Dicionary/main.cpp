#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <deque>
#include <forward_list>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

int arr[26][26];
bool visited[26];
string visit_str;
vector<int> order;

void dfs(int p) {
  visited[p] = true;
  for (int i = 0; i < 26; i++) {
    if (arr[p][i] == 1 && !visited[i]) {
      dfs(i);
    }
  }
  order.push_back(p);
  visit_str.push_back(p + 'a');
}

int main() {
  freopen("sample_input.txt", "r", stdin);
  std::ios::sync_with_stdio(false);
  int C;
  cin >> C;
  for (int c = 0; c < C; c++) {
    int N;
    cin >> N;

    memset(arr, 0, sizeof(arr));
    memset(visited, false, sizeof(visited));
    visit_str.clear();
    order.clear();

    string s;
    cin >> s;
    for (int n = 1; n < N; n++) {
      string s1;
      cin >> s1;
      int str_len = min(s.length(), s1.length());
      for (int i = 0; i < str_len; i++) {
        if (s[i] != s1[i]) {
          arr[s[i] - 'a'][s1[i] - 'a'] = 1;
          break;
        }
      }
      s = s1;
    }

    for (int i = 0; i < 26; i++) {
      if (!visited[i]) {
        bool is_root = true;
        for (int j = 0; j < 26; j++) {
          if (arr[j][i] == 1) is_root = false;
        }
        if (is_root) {
          dfs(i);
        }
      }
    }

    reverse(order.begin(), order.end());
    int n = order.size();
    bool is_ok = true;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (arr[order[j]][order[i]] == 1) {
          is_ok = false;
        }
      }
    }

    if (is_ok && order.size() == 26) {
      reverse(visit_str.begin(), visit_str.end());
      cout << visit_str << '\n';
    } else {
      cout << "INVALID HYPOTHESIS\n";
    }
  }
  return 0;
}