// #include <iostream>
// #include <map>
// #include <queue>
// #include <vector>

// using std::cin, std::cout, std::endl;
// using std::priority_queue, std::vector, std::map;

// constexpr int MAX_N = 100000;
// constexpr int MAX_K = 100000;
// constexpr int MAX_J = 100000000;
// constexpr int MAX_T = 1000000000;
// constexpr int MAX_S = 1000000000;

// int N, K, J;

// struct Range{
//   int lo;
//   int hi;
// };

// vector<int> childs[MAX_N + 1];
// int singers[MAX_N + 1];
// int singer_nums[MAX_N + 1];

// int tta[MAX_N + 1]; // TreeTraversalArray
// Range ranges[MAX_N + 1];

// void calc_tta(int idx){
//   static int traversal_num = 0;
//   int lo = traversal_num;

//   for(const auto& child : childs[idx]){
//     calc_tta(child);
//   }


//   int hi = traversal_num;

//   ranges[idx] = Range{lo, hi};
//   traversal_num++;
//   tta[idx] = traversal_num;
// }

// int main() {
//   std::ios::sync_with_stdio(false);
//   cin >> N >> K >> J;

//   for (int i = 2; i <= N; i++) {
//     int par;
//     cin >> par;
//     childs[par].push_back(i);
//   }

//   for (int i = 1; i <= N; i++) {
//     cin >> singers[i];
//     singer_nums[singers[i]]++;
//   }

//     for (int k = 0; k < K; k++) {
//     int T, P, S;
//     cin >> T >> P >> S;
//   }

//   calc_tta(1);


//   return 0;

// }
