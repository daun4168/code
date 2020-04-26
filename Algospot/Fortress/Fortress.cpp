#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Circle {
  Circle(int x, int y, int r) : x(x), y(y), r(r) { }
  int x;
  int y;
  int r;
};

//c1�� c2�� �����ϳ�?
bool isContain(Circle& c1, Circle& c2) {
  return sqrt((pow((c2.x - c1.x), 2) + pow((c2.y - c1.y), 2))) + c2.r < c1.r;
}

class Tree {
public:
  struct Node {
    Node(Circle c, Node* par) : c(c), par(par) { }
    Circle c;
    vector<Node*> child;
    Node* par;
  };
  Tree() {
    size_ = 0;
    root_ = nullptr;
  }
  bool insert(Circle c, Node* par = nullptr) {
    if (size_ == 0) {
      Node* new_node = new Node(c, par);
      root_ = new_node;
      size_++;
      return true;
    } else {
      if (par == nullptr) par = root_;
      bool is_inserted = false;
      for (int i = 0; i < par->child.size(); i++) {
        if (isContain(par->child[i]->c, c)) {
          is_inserted = insert(c, par->child[i]);
          break;
        }
      }
      if (!is_inserted) {
        Node* new_node = new Node(c, par);
        par->child.push_back(new_node);
        for (int i = 0; i < par->child.size(); i++) {
          if (isContain(c, par->child[i]->c)) {
            Node* temp = par->child[i];
            par->child.erase(par->child.begin() + i);
            new_node->child.push_back(temp);
            temp->par = new_node;
          }
        }
        size_++;
        return true;
      }
    }
  }
  int size() {
    return size_;
  }
  int height(Node* node) {
    int h = 0;
    for (int i = 0; i < node->child.size(); i++) {
      h = max(h, 1 + height(node->child[i]));
    }
    return h;
  }
  int maxPass(Node* node) {
    //vector<int> h;
    //for (int i = 0; i < node->child.size(); i++)
    //  h.push_back(maxPass(node->child[i]));
    //if (h.empty()) return 0;
    //sort(h.begin(), h.end());
    //if (h.size() >= 2)
    //  longest_ = max(longest_, 2 + h[h.size() - 2] + h[h.size() - 1]);
    //return h.back() + 1;

    if (node->child.size() == 0) {
      return 0;
    } else if (node->child.size() == 1) {
      return max(height(node), maxPass(node->child[0]));
    } else {
      int max_height1 = 0, max_height2 = 0;
      for (int i = 0; i < node->child.size(); i++) {
        max_height2 = max(max_height2,1 + height(node->child[i]));
        if (max_height2 > max_height1)
          swap(max_height2, max_height1);        
      }
      int max_pass = max_height1 + max_height2;
      for (int i = 0; i < node->child.size(); i++) {
        max_pass = max(max_pass, maxPass(node->child[i]));
      }
      return max_pass;
    }
  }
  Node* root() {
    return root_;
  } 
private:
  int size_;
  Node* root_;
  int longest_;
};

int main() {
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    int N;
    cin >> N;
    Tree fortress;
    int x, y, r;
    cin >> x >> y >> r;
    fortress.insert({ x, y, r });
    auto root = fortress.root();
    for (int i = 1; i < N; i++) {
      cin >> x >> y >> r;
      fortress.insert({ x, y, r });
    }
    cout << fortress.maxPass(root) << endl;
  }
  return 0;
}