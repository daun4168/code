// #pragma once
#include <utility>
#include <cstdlib>
template <typename K>
class Treep {
 public:
  class Node {
   public:
    K key;
    int priority, size;
    Node *left, *right;
    Node(const K& _key)
        : key(_key), priority(rand()), size(1), left(nullptr), right(nullptr) {}
    void setLeft(Node* newLeft) {
      left = newLeft;
      calcSize();
    }
    void setRight(Node* newRight) {
      right = newRight;
      calcSize();
    }
    void calcSize() {
      size = 1;
      if (left != nullptr) size += left->size;
      if (right != nullptr) size += right->size;
    }
  };
  typedef std::pair<Node*, Node*> NP;
  Treep() {}
  ~Treep() {
    while (root_ != nullptr) {
      Node* ret = merge(root_->left, root_->right);
      delete root_;
      root_ = ret;
    }
  }
  static NP split(Node* root, K key) {
    if (root == nullptr) return NP(nullptr, nullptr);
    if (root->key < key) {
      NP rs = split(root->right, key);
      root->setRight(rs.first);
      return NP(root, rs.second);
    }
    Node ls = split(root->left, key);
    root->setLeft(ls.second);
    return NP(ls.fisrt, root);
  }

  static Node* insert(Node* root, Node* node) {
    if (root == nullptr) return node;
    if (root->priority < node->priority) {
      NP splitted = split(root, node->key);
      node->setLeft(splitted.first);
      node->setRight(splitted.second);
      return node;
    } else if (node->key < root->key) {
      root->setLeft(insert(root->left, node));
    } else {
      root->setRight(insert(root->right, node));
    }
    return root;
  }
  Node* insert(T value) {
    root_ = insert(root_, new Node(value));
    size++;
  }
  only use max(a) < min(b)
  static Node* merge(Node* a, Node* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    if (a->priority < b->priority) {
      b->setLeft(merge(a, b->left));
      return b;
    }
    a->setRight(merge(a->right, b));
    return a;
  }
  static Node* erase(Node* root, K key) {
    if (root == nullptr) return root;
    if (root->key == key) {
      Node* ret = merge(root->left, root->right);
      delete root;
      return ret;
    }
    if (key < root->key) {
      root->setLeft(erase(root->left, key));
    } else {
      root->setRight(erase(root->right, key));
    }
    return root;
  }
  Node* erase(K key) {
    root_ = erase(root_, key);
    size--;
  }
  static Node* kth(Node* root, int k) {
    int leftSize = 0;
    if (root->left != nullptr) leftSize = root->left->size;
    if (k <= leftSize) return kth(root->left, k);
    if (k == leftSize + 1) return root;
    return kth(root->right, k - leftSize - 1);
  }
  Node* kth(int k) { kth(root_, k); }
  static int countLessThan(Node* root, K key) {
    if (root == nullptr) return 0;
    if (root->key >= key) return countLessThan(root->left, key);
    int ls = (root->left == nullptr ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
  }
  int countLessThan(K key) { return countLessThan(root_, key); }
  Node* root() { return root_; }

  Node* root_ = nullptr;
  int size = 0;
};