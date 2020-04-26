#include "Quadtree.h"

using namespace std;

Quadtree::Quadtree() {
  cin >> input_;
//  cout << reverse(input_) << endl;
  head_ = 0;
  cout << reverse(input_) << endl;
}

string Quadtree::reverse(string s) {
  if (s.size() == 1)
    return s;
  int depth = 1;
  int string_num = 0;
  int start_num = 1;
  int this_num = 1;
  int this_length = 0;
  string reversed_string[4];
  while (string_num < 4) {
    if (s[this_num] == 'x') {
      depth += 3;
      this_num++;
      this_length++;
    } else {
      depth--;
      this_num++;
      this_length++;
      if (depth == 0) {
        reversed_string[string_num] = reverse(s.substr(start_num, this_length));
        start_num = this_num;
        string_num++;
        depth = 1;
        this_length = 0;
      }
    }
  }
  return "x" + reversed_string[2] + reversed_string[3] + reversed_string[0] + reversed_string[1];
}



