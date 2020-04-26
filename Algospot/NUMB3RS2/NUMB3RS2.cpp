#include <iostream>
#include <iomanip>

using namespace std;

int n, d, p;
double cache[50][101]; //town, day
bool is_path[50][50];
int path_num[50];

double search(int town, int day);

int main() {
  std::ios::sync_with_stdio(false);
  cout << fixed << setprecision(8);
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    cin >> n >> d >> p;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> is_path[i][j];
      }
    }
    //cache reset
    for (int i = 0;i < n; i++) {
      for (int j = 0; j <= 100; j++) {
        cache[i][j] = -1.0;
      }
    }
    for (int i = 0; i < n; i++) {
      path_num[i] = 0;
      for (int j = 0; j < n; j++) {
        if (is_path[i][j]) path_num[i]++;
      }
    }
    int prob_town_num;
    cin >> prob_town_num;
    for (int i = 0; i < prob_town_num; i++) {
      int prob_town;
      cin >> prob_town;
      cout << search(prob_town, d) << ' ';    
    }
    cout << '\n';
  }
  return 0;
}

double search(int town, int day) {
  double& r = cache[town][day];
  if (r != -1.0) return r;
  if (day == 0) {
    r = town == p ? 1 : 0;
    return r;
  }
  r = 0;
  for (int i = 0; i < n; i++) {
    if (is_path[town][i])
      r += search(i, day - 1) / path_num[i];
  }
  return r;
}
