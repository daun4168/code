#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

bool isPalindrome(int i) {
  string s = to_string(i);
  int s_pos = 0;
  int e_pos = s.size() - 1;
  while (s_pos < e_pos) {
    if (s[s_pos] != s[e_pos]) return false;
    s_pos++;
    e_pos--;
  }
  return true;
}


int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("palindrome.txt", "r", stdin);
  cin >> T;

  vector<int> palindromes;
  for (int i = 1; i <= 10000; i++) {
    if (isPalindrome(i)) palindromes.push_back(i);
  }


  for (test_case = 0; test_case < T; test_case++)
  {
    int n;
    cin >> n;
    int k = 0;
    int sums[3];

    // k == 1
    auto p_find = find(palindromes.begin(), palindromes.end(), n);
    if (p_find != palindromes.end()) {
      k = 1;
      sums[0] = *p_find;
    }

    // k == 2
    if (k == 0) {
      for (int p1 : palindromes) {
        int n2 = n - p1;
        if (n2 <= 0) break;
        p_find = find(palindromes.begin(), palindromes.end(), n2);

        if (p_find != palindromes.end()) {
          k = 2;
          sums[0] = p1;
          sums[1] = *p_find;
        }
      }
    }

    // K == 3
    
    for (int i = 0; i < palindromes.size() && k == 0; i++) {
      int p1 = palindromes[i];
      int n2 = n - p1;
      if (n2 <= 0) break;

      for (int p2 : palindromes) {
        int n3 = n2 - p2;
        if (n3 <= 0) break;
        p_find = find(palindromes.begin(), palindromes.end(), n3);

        if (p_find != palindromes.end()) {
          k = 3;
          sums[0] = p1;
          sums[1] = p2;
          sums[2] = *p_find;
        }
      }
    }
    cout << "Case #" << test_case + 1 << endl;
    cout << k << ' ';
    for (int i = 0; i < k; i++) {
      cout << sums[i] << ' ';
    }
    cout << endl;
  }
  return 0;
}