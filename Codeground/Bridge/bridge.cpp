#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const double inf = 1e20;

struct Point {
  double x;
  double y;
};

int N, M;
Point a[2000000], b[2000000];

double dist2(const Point& p1, const Point& p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

double dist(const Point& p1, const Point& p2) {
  return sqrt(dist2(p1, p2));
}

double cal_min_dist(const Point& p1, const Point& p2, const Point& p3) {
  double a1 = dist(p2, p3);
  double b1 = dist(p1, p3);
  double c1 = dist(p1, p2);
  double a2 = dist2(p2, p3);
  double b2 = dist2(p1, p3);
  double c2 = dist2(p1, p2);
  double cosB = (c2 + a2 - b2) / (2 * c1 * a1);
  double cosC = (a2 + b2 - c2) / (2 * a1 * b1);

  if (cosB <= 0) return c1;
  if (cosC <= 0) return b1;

  double sinB = sqrt(1 - cosB * cosB);
  return c1 * sinB;
}

int main(int argc, char** argv)
{
  int i;
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  freopen("bridge.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
      cin >> a[i].x >> a[i].y;
    }
    for (int i = 0; i < M; i++) {
      cin >> b[i].x >> b[i].y;
    }

    int close_line = 0;
    double close_line_dist = inf;

    for (i = 0; i < M; i++) {
      double new_dist = cal_min_dist(a[0], b[i], b[(M + i - 1) % M]);
      if (new_dist < close_line_dist) {
        close_line_dist = new_dist;
        close_line = i;
      }
    }

    double min_dist = close_line_dist;

    i = 1;
    while (i < N) {
      double new_dist = cal_min_dist(a[i], b[close_line], b[(M + close_line - 1) % M]);
      double left_dist = cal_min_dist(a[i], b[(M + close_line - 1) % M], b[(M + close_line - 2) % M]);
      double right_dist = cal_min_dist(a[i], b[close_line], b[(close_line + 1) % M]);

      if (new_dist <= left_dist && new_dist <= right_dist) {
        min_dist = min(new_dist, min_dist);
        i++;
        continue;
      }
      if (left_dist < new_dist) {
        close_line = (close_line - 1 + M) % M;
      }
      else if (right_dist < new_dist) {
        close_line = (close_line + 1) % M;
      }
    }

    close_line = 0;
    close_line_dist = inf;

    for (i = 0; i < N; i++) {
      double new_dist = cal_min_dist(b[0], a[i], a[(N + i - 1) % N]);
      if (new_dist < close_line_dist) {
        close_line_dist = new_dist;
        close_line = i;
      }
    }

    min_dist = min(min_dist, close_line_dist);

    i = 1;
    while (i < M) {
      double new_dist = cal_min_dist(b[i], a[close_line], a[(N + close_line - 1) % N]);
      double left_dist = cal_min_dist(b[i], a[(N + close_line - 1) % N], a[(N + close_line - 2) % N]);
      double right_dist = cal_min_dist(b[i], a[close_line], a[(close_line + 1) % N]);

      if (new_dist <= left_dist && new_dist <= right_dist) {
        min_dist = min(new_dist, min_dist);
        i++;
        continue;
      }
      if (left_dist < new_dist) {
        close_line = (close_line - 1 + N) % N;
      }
      else if (right_dist < new_dist) {
        close_line = (close_line + 1) % N;
      }
    }
    cout << "Case #" << test_case + 1 << endl;
    cout << fixed;
    cout.precision(10);
    cout << min_dist << endl;
  }
  return 0;
}
