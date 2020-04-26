#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printPostorder(vector<int> preorder, vector<int> inorder) {
  auto it = find(inorder.begin(), inorder.end(), preorder[0]);
  if (it - inorder.begin() > 1)
    printPostorder(
      vector<int>(preorder.begin() + 1, preorder.begin() + (it - inorder.begin()) + 1),
      vector<int>(inorder.begin(), it));
  else if (it - inorder.begin() == 1)
    cout << *(it - 1) << " ";
  if (inorder.end() - it > 2)
    printPostorder(
      vector<int>(preorder.begin() + (it - inorder.begin()) + 1, preorder.end()),
      vector<int>(it + 1, inorder.end()));
  else if (inorder.end() - it == 2)
    cout << *(it + 1) << " ";
  cout << *it << " ";

}

// int main() {
//   int test_case;
//   cin >> test_case;
//   for (int t = 0; t < test_case; t++) {
//     size_t N;
//     cin >> N;
//     vector<int> preorder(N);
//     vector<int> inorder(N);
//     for (size_t i = 0; i < N; i++) {
//       cin >> preorder[i];
//     }
//     for (size_t i = 0; i < N; i++) {
//       cin >> inorder[i];
//     }
//     printPostorder(preorder, inorder);
//     cout << endl;
//   }
//   return 0;
// }