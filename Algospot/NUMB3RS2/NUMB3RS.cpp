//#include <iostream>
//#include <iomanip>
//
//using namespace std;
//
//int main() {
//  std::ios::sync_with_stdio(false);
//  int test_case;
//  cin >> test_case;
//  for (int t = 0; t < test_case; t++) {
//    int town_num, day, prison;
//    bool is_path[50][50];
//    cin >> town_num >> day >> prison;
//    for (int i = 0; i < town_num; i++) {
//      for (int j = 0; j < town_num; j++) {
//        cin >> is_path[i][j];
//      }
//    }    
//    //[town][day]
//    double prob[50][101];
//    int path_num[50];
//    for (int i = 0; i < town_num; i++) {
//      path_num[i] = 0;
//      for (int j = 0; j < town_num; j++) {
//        if (is_path[i][j]) path_num[i]++;
//      }
//    }
//    //ÃÊ±âÈ­
//    for (int i = 0; i < town_num; i++) {
//      prob[i][0] = 0;
//    }
//    prob[prison][0] = 1;
//    for (int d = 1; d <= day; d++) {
//      for (int i = 0; i < town_num; i++) {
//        prob[i][d] = 0;
//        for (int j = 0; j < town_num; j++) {
//          if(is_path[i][j])
//          prob[i][d] += prob[j][d - 1] * (1 / double(path_num[j]));
//        }
//      }
//    }
//    int prob_town_num;
//    cin >> prob_town_num;
//    cout << fixed << setprecision(8);
//    for (int i = 0; i < prob_town_num; i++) {
//      int prob_town;
//      cin >> prob_town;
//      cout << prob[prob_town][day] << " ";
//    }
//    cout << '\n';
//  }
//  return 0;
//}