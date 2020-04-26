//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <unordered_map>
//
//using namespace std;
//
//void lis();
//
//int main() {
  //int test_case;
  //cin >> test_case;
  //for (int i = 0; i < test_case; i++) {
  //  lis();
  //}
  //return 0;
//}

//vector<int> cache;
//
//int findlis(vector<int>& v) {
//  if (v.size() == 0) return 0;
//  if (cache[v.size() - 1] != -1) return cache[v.size() - 1];
//  int max_lis;
//  for (int i = 0; i < v.size(); i++) {
//    int first = v[i];
//    vector<int> temp;
//    for_each(v.begin() + i, v.end(), [&](int it) {if (it > first)temp.push_back(it); });
//    max_lis = max(max_lis, findlis(temp));
//  }
//  cache[v.size() - 1] = max_lis + 1;
//  return max_lis + 1;
//}
//
//void lis() {
//  int arr_length;
//  cache.clear();
//  cin >> arr_length;
//  vector<int> arr;
//  cache.assign(arr_length, -1);
//  for (int i = 0; i < arr_length; i++) {
//    int temp;
//    cin >> temp;
//    arr.push_back(temp);
//  }
//  cout << findlis(arr) << endl;
//}