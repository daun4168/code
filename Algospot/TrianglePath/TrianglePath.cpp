#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>

using namespace std;

void trianglePath();

int main() {
  int test_case;
  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    trianglePath();
  }
  return 0;
}

unordered_map<int, int> cache;

int findPath(vector<vector<int>>& triangle, int height, int width) {
  auto iter = cache.find(height * 1000 + width);
  if (iter != cache.end()) return iter->second;
  if (height < triangle.size() - 1) {
    int max_path = triangle[height][width] + max(findPath(triangle, height + 1, width)
      , findPath(triangle, height + 1, width + 1));
     cache.insert({ height * 1000 + width, max_path });
     return max_path;
  } else {
    cache.insert({ height * 1000 + width, triangle[height][width]});
    return triangle[height][width];
  }   
}

void trianglePath() {
  int triangle_size;
  cache.clear();
  cin >> triangle_size;
  vector<vector<int>> triangle; 
  for (int i = 0; i < triangle_size; i++) {
    vector<int> v;
    for (int j = 0; j <= i; j++) {
      int num;
      cin >> num;
      v.push_back(num);
    }
    triangle.push_back(v);
  }
  cout << findPath(triangle, 0, 0) << endl;
}
