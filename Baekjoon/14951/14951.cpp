#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <cstring>

using namespace std;

int n, a, b;
vector<int>* T;
vector<bool>* newtree;

bool isAllTrue(vector<bool>* tree) {
  for (int k = 1; k <= n; k++) {
    if (!((*tree)[k])) return false;
  }
  return true;
}


void deleteEle(vector<bool>* tree, int depth, int v) {
  if (depth == 1) {
    for (auto ele : *T) {
      (*tree)[(*T)[ele]] = true;
    }
  }
  else {
    
    (*tree)[v] = true;
    for (auto ele : *T) {
      deleteEle(tree, depth - 1, ele);
    }
    
  }
}


int findmin(vector<bool>* tree, int max_depth) {
  if (isAllTrue(tree)) return 0;
  if (max_depth == 0) return n;
  int temp;
  int min = n;
  for (int d = 1; d <= max_depth; d++) {
    for (int v = 1; v <= n; v++) {
      if (!(*tree)[v]) {
        vector<bool>* temptree = new vector<bool>(*tree);
        deleteEle(temptree, d, v);
        temp = findmin(temptree, max_depth - d);
        min = min < temp + d ? min : temp + d;
        delete temptree;
      }      
    }
    if (min <= d) {
      break;
    }
  }
  return min;
}





int main()
{
  std::ios::sync_with_stdio(false);

  cin >> n;
  T = new vector<int>[n + 1];
  for (int k = 0; k < n - 1; k++) {
    cin >> a >> b;
    T[a].push_back(b);
    T[b].push_back(a);
  }
  
  newtree = new vector<bool>;
  newtree->reserve(n + 1);
  newtree->resize(n + 1);
  for (int i = 1; i <= n; i++) {
    (*newtree)[i] = false;
  }

  int minp = n;
  
  for (int i = 1; i <= n; i++) {
    vector<bool>* argtree = new vector<bool>(*newtree);
    minp = findmin(argtree, i);
    if (minp <= i) break;
    delete argtree;
  }
  cout << minp << '\n';

}