#include <iostream>
#include <vector>
#include <string>

using std::string;


class Quadtree {
public:
  Quadtree();
  string reverse(string s);
private:
  string input_;
  int head_;
};