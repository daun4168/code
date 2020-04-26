#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

using namespace std;

#define long long long

typedef pair<long, long> Point;

vector<Point> p;

long calY(long x) {
  auto lo = lower_bound(p.begin(), p.end(), x);
  auto up = upper_bound(p.begin(), p.end(), x);

  if (up == p.end()) return lo->second;

  if (lo->second < up->second) {
    return lo->second + (x - lo->first);
  }
  else {
    return lo->second - (x - lo->first);
  }
}

int main() {
  int i;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("stage.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    p.clear();
    long N;
    int M, L;
    cin >> N >> M >> L;

    bool isSolution = false;

    int nu, de;

    if (L == 1) {
      for (int i = 0; i < M + 1; i++) {
        long x, y;
        cin >> x >> y;
        if (x - y <= 0 && x + y >= N) {
          isSolution - true;
        }
        p.push_back(Point{ x * 2, y * 2 });
      }

      if (isSolution) {
        


      }
    }

    

    

    cout << "Case #" << test_case + 1 << endl;
    if (isSolution) {
      cout << nu << ' ' << de << endl;
    }
    else {
      cout << -1 << endl;
    }
  }
  return 0;
}