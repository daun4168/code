#include <iostream>
#include <utility>
#include <map>

using namespace std;

#ifdef __GNUC__
#define putchar putchar_unlocked
#define getchar getchar_unlocked
#elif _MSC_VER
#endif

char _c, _k, _b[11];
int _x;
#define scan(x) do{while((x=getchar())<'0'); \
for(x-='0'; '0'<=(_c=getchar()); x = x*10 + _c -'0'); }while(0)
#define scani(x) do{while((x=getchar())<'-'); \
if(x == '-'){x=getchar();for(x-='0'; '0'<=(_c=getchar()); x = x*10 + _c -'0');x=-x;}\
else { for (x -= '0'; '0' <= (_c = getchar()); x = x * 10 + _c - '0'); }}while (0)
#define print(x) do{ _x = x;\
for (_k = 0; _x > 0; _k++, _x /= 10) _b[_k] = _x % 10 + '0'; \
for (_k--; _k >= 0; _k--) putchar(_b[_k]); } while (0)
#define printi(x) do{_x = x;\
if(_x > 0) {for (_k = 0; _x > 0; _k++, _x /= 10) _b[_k] = _x % 10 + '0'; \
for (_k--; _k >= 0; _k--) putchar(_b[_k]);} else if (_x == 0) putchar('0'); \
else { putchar('-'); _x = -_x;\
for (_k = 0; _x > 0; _k++, _x /= 10) _b[_k] = _x % 10 + '0'; \
for (_k--; _k >= 0; _k--) putchar(_b[_k]);}} while (0)
#define eol putchar('\n')
#define space putchar(' ')

template<class K>
class Treep {
public:
  class Node
  {
  public:
    K key;
    int priority, size;
    Node *left, *right;
    Node(const K& _key) : key(_key), priority(rand()),
      size(1), left(nullptr), right(nullptr) {}
    void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
    void setRight(Node* newRight) { right = newRight; calcSize(); }
    void calcSize() {
      size = 1;
      if (left != nullptr) size += left->size;
      if (right != nullptr) size += right->size;
    }
  };
  typedef pair <Node*, Node*> NP;
  Treep() {  }
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
    NP ls = split(root->left, key);
    root->setLeft(ls.second);
    return NP(ls.first, root);
  }
  static Node* insert(Node* root, Node* node) {
    if (root == nullptr) return node;
    if (root->priority < node->priority) {
      NP splitted = split(root, node->key);
      node->setLeft(splitted.first);
      node->setRight(splitted.second);
      return node;
    }
    else if (node->key < root->key) {
      root->setLeft(insert(root->left, node));
    }
    else {
      root->setRight(insert(root->right, node));
    }
    return root;
  }
  void insert(K value) {
    root_ = insert(root_, new Node(value));
    size++;
  }
  // only use max(a) < min(b)
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
    }
    else {
      root->setRight(erase(root->right, key));
    }
    return root;
  }
  void erase(K key) {
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
  Node* kth(int k) {
    return kth(root_, k);
  }
  static int countLessThan(Node* root, K key) {
    if (root == nullptr) return 0;
    if (root->key >= key)
      return countLessThan(root->left, key);
    int ls = (root->left == nullptr ? root->left->size : 0);
    return ls + 1 + countLessThan(root->right, key);
  }
  int countLessThan(K key) {
    return countLessThan(root_, key);
  }
  Node* root() {
    return root_;
  }

  Node* root_ = nullptr;
  int size = 0;

};
int main() {
  std::ios::sync_with_stdio(false);
  int C, N, a;
  int shifted[50000];
  int A[50000];
  scan(C);
  for (int c = 0; c < C; c++) {
    scan(N);
    Treep<int>* tr = new Treep<int>();
    for (int n = 1; n <= N; n++) {
      tr->insert(n);
      scan(shifted[n - 1]);
    }
    for (int i = N-1; i >= 0; i--) {
      int larger = shifted[i];
      Treep<int>::Node* k = tr->kth(i + 1 - larger);
      A[i] = k->key;
      tr->erase(k->key);
    }
    for (int i = 0; i < N; i++) {
      print(A[i]);
      space;
    }
    eol;
    delete tr;
  }
  return 0;
}
