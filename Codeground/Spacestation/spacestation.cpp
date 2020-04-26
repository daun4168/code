//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include <algorithm>
//#include <list>
//#include <cstring>
//#include <vector>
//#include <unordered_set>
//
//using namespace std;
//typedef pair<int, int> Edge;
//
//struct Tri {
//  Tri(int s, int t, int v) {
//    if (s < t && s < v) {
//      if (t < v) {
//        this->s = s;
//        this->t = t;
//        this->v = v;
//      }
//      else {
//        this->s = s;
//        this->t = v;
//        this->v = t;
//      }
//    }
//    else if (t < s && t < v) {
//      if (s < v) {
//        this->s = t;
//        this->t = s;
//        this->v = v;
//      }
//      else {
//        this->s = t;
//        this->t = v;
//        this->v = s;
//      }
//    }
//    else {
//      if (s < t) {
//        this->s = v;
//        this->t = s;
//        this->v = t;
//      }
//      else {
//        this->s = v;
//        this->t = t;
//        this->v = s;
//      }
//    }
//  }
//  int s;
//  int t;
//  int v;
//};
//
//int N, M;
//int n, m;
//constexpr long long N_MAX =  2000001;
//
//struct edge_hash {
//  inline long long operator()(const std::pair<int, int> & v) const {
//    return v.first * N_MAX + v.second;
//  }
//};
//
//int main() {
//  std::ios_base::sync_with_stdio(false);
//  std::cin.tie(0);
//  int T, test_case;
//  freopen("spacestation.txt", "r", stdin);
//  cin >> T;
//  for (test_case = 0; test_case < T; test_case++)
//  {
//    cin >> N >> M;
//
//    vector<vector<int>> g(N + 1);
//
//    for (int i = 0; i < M; i++) {
//      int a, b;
//      cin >> a >> b;
//      g[a].push_back(b);
//      g[b].push_back(a);
//    }
//
//    list<Tri> tris;
//    vector<vector<int>> A(N + 1);
//
//    for (int s = 1; s <= N; s++) {
//      for (int t : g[s]) {
//        if (s < t) {
//          for (int v : A[s]) {
//            for (int v2 : A[t]) {
//              if (v == v2) {
//                tris.push_back(Tri{ s, t, v });
//              }
//            }
//          }
//          A[t].push_back(s);
//        }
//      }
//    }
//
//    int flow = 0;
//
//
//    
//
//    unordered_set<int> epos;
//
//    for (auto t : tris) {
//      if (epos.find(t.s) == epos.end()) {
//        epos.insert(t.s);
//        flow++;
//      }
//
//      if (epos.find(t.v) == epos.end()) {
//        epos.insert(t.v);
//        flow++;
//      }
//
//      if (epos.find(t.t) == epos.end()) {
//        epos.insert(t.t);
//        flow++;
//      }
//    }
//
//    if(flow > 2) flow -= 2;
//    
//    //unordered_set<Edge, edge_hash> e1;
//    //unordered_set<Edge, edge_hash> e2;
//
//    //vector<int> input_count;
//    //vector<int> output_count;
//
//    //input_count.assign(N + 1, 0);
//    //output_count.assign(N + 1, 0);
//
//    //for (auto t : tris) {
//    //  if (e1.find(Edge{ t.s, t.t }) == e1.end()) {
//    //    input_count[t.t]++;
//    //    e1.insert(Edge{ t.s, t.t });
//    //  }
//
//    //  if (e2.find(Edge{ t.t, t.v }) == e2.end()) {
//    //    output_count[t.t]++;
//    //    e2.insert(Edge{ t.t, t.v });
//    //  }
//    //}
//
//    //for (int i = 1; i <= N; i++) {
//    //  flow += min(input_count[i], output_count[i]);
//    //}
//
//    cout << "Case #" << test_case + 1 << endl;
//    cout << N - flow << endl;
//  }
//  return 0;
//}