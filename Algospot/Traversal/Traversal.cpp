#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
class BTree {
public:
  enum LR { left = 1, right };
  struct Node {
    Node(T value) {
      this->value = value;
      left = nullptr;
      right = nullptr;
      par = nullptr;
    }
    T value;
    Node* left;
    Node* right;
    Node* par;
  };
  BTree() {
    size_ = 0;
  }
  BTree(T value) {
    Node* new_node = new Node(value);
    root_ = new_node;
    size_ = 1;
  }
  Node* insert(T value, Node* par, LR lr) {
    Node* new_node = new Node(value);
    new_node->par = par;
    if (lr == left) par->left = new_node;
    else par->right = new_node;
    size_++;
    return new_node;
  }
  T pop(Node* node) {
    T tmp = node->value;
    if (node != root_) {
      if (node->par->left == node)
        node->par->left = nullptr;
      else
        node->par->right = nullptr;
    } else {
      root_ = nullptr;
    }
    if (node->left != nullptr)
      node->left->par = nullptr;
    if (node->right != nullptr)
      node->right->par = nullptr;
    delete node;
    size_--;
  }
  int size() {
    return size_;
  }
  Node* root() {
    return root_;
  }
  void inorder(Node* node) {
    if (node == nullptr) return;
    if (node->left != nullptr)
      inorder(node->left);
    cout << node->value << " ";
    if (node->right != nullptr)
      inorder(node->right);
  }
  void preorder(Node* node) {
    if (node == nullptr) return;
    cout << node->value << " ";
    if (node->left != nullptr)
      preorder(node->left);
    if (node->right != nullptr)
      preorder(node->right);
  }
  void postorder(Node* node) {
    if (node == nullptr) return;
    if (node->left != nullptr)
      postorder(node->left);
    if (node->right != nullptr)
      postorder(node->right);
    cout << node->value << " ";
  }
private:
  int size_;
  Node* root_;
};

pair<BTree<int>::Node*, BTree<int>::LR> findPlace
(BTree<int>::Node* node, vector<int>& inorder, int value) {
  auto value_iter = find(inorder.begin(), inorder.end(), value);
  auto par_iter = find(inorder.begin(), inorder.end(), node->value);
  if (value_iter < par_iter) {
    if (node->left == nullptr)
      return { node, BTree<int>::left };
    else
      return findPlace(node->left, inorder, value);
  } else {
    if (node->right == nullptr)
      return { node, BTree<int>::right };
    else
      return findPlace(node->right, inorder, value);
  }
}

int main() {
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    size_t N;
    cin >> N;
    vector<int> preorder(N);
    vector<int> inorder(N);
    for (size_t i = 0; i < N; i++) {
      cin >> preorder[i];
    }
    for (size_t i = 0; i < N; i++) {
      cin >> inorder[i];
    }
    BTree<int> Tree(preorder[0]);
    auto root = Tree.root();

    for (size_t i = 1; i < N; i++) {
      auto temp = findPlace(root, inorder, preorder[i]);
      Tree.insert(preorder[i], temp.first, temp.second);
    }
    Tree.postorder(root);
    std::cout << endl;
  }
  return 0;
}