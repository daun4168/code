#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  freopen("input.txt", "r", stdin);  
  int T;
  T = 10;
    
  for (int t = 1; t <= T; t++) {
    int N;
    cin >> N;
    int building[1000];
    for (int i = 0; i < N; i++) {
      cin >> building[i];
    }

    int good_view = 0;

    for (int i = 0; i < N; i++) {
      if (building[i] == 0) continue;
      int max_building = 0;

      max_building = max(building[i - 2], max_building);
      max_building = max(building[i - 1], max_building);
      max_building = max(building[i + 1], max_building);
      max_building = max(building[i + 2], max_building);

      if (building[i] - max_building > 0)
        good_view += building[i] - max_building;
    }

    cout << '#' << t << ' ';
    cout << good_view << endl;
  }

  return 0;
}