#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <climits>

using namespace std;

int n;
array<int, 100> arr;
array<array<int, 10>, 100> quantize_cache;
array<array<int, 100>, 100> minSumSquare_cache;

int quantize(int pos, int s);
int minSumSquare(int pos1, int pos2);
int minSumSquare2(int pos1, int pos2);
int sumSquare(int pos1, int pos2, int q);
void cacheReset();

int sum[100];
int sq_sum[100];

int main() {
  std::ios::sync_with_stdio(false);
  int test_case;
  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    int s;
    cacheReset();
    cin >> n >> s;
    for (int j = 0; j < n; j++) {
      cin >> arr[j];
    }
    sort(arr.begin(), arr.begin() + n);
    sum[0] = arr[0];
    sq_sum[0] = arr[0] * arr[0];
    for (int i = 1; i < n; i++) {
      sum[i] = sum[i - 1] + arr[i];
      sq_sum[i] = sq_sum[i - 1] + arr[i] * arr[i];
    }
    int min_quantize = INT_MAX;
    for (int j = 1; j <= s; j++) {
      min_quantize = min(min_quantize, quantize(0, j));
    }
    cout << min_quantize << endl;
  }
  return 0;
}

void cacheReset() {
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 10; j++) {
      quantize_cache[i][j] = -1;
    }
    for (int j = 0; j < 100; j++) {
      minSumSquare_cache[i][j] = -1;
    }
  }
}

int quantize(int pos, int s) {
  int& ref = quantize_cache[pos][s];
  if (ref != -1) return ref;
  if (s == 1) {
    ref = minSumSquare2(pos, n);
    return ref;
  }
  ref = INT_MAX;
  for (int i = pos + 1; i < n - s + 2; i++) {
    ref = min(quantize(i, s - 1)
      + minSumSquare2(pos, i), ref);
  }
  return ref;
}

//느린 방법 - min to max 까지 다해봄
int minSumSquare(int pos1, int pos2) {
  int& ref = minSumSquare_cache[pos1][pos2];
  int min_ele = arr[pos1];
  int max_ele = arr[pos2 - 1];
  ref = INT_MAX;
  for (int i = min_ele; i <= max_ele; i++) {
    ref = min(ref, sumSquare(pos1, pos2, i));
  }
  return ref;
}

//빠른 방법  - 공식 사용
int minSumSquare2(int pos1, int pos2) {
  int& ref = minSumSquare_cache[pos1][pos2];
  int min_ele = arr[pos1];
  int max_ele = arr[pos2 - 1];
  if (min_ele == max_ele)  return 0;
  int sum_ = sum[pos2 - 1] - (pos1 == 0 ? 0 : sum[pos1 - 1]);
  int sq_sum_ = sq_sum[pos2 - 1] - (pos1 == 0 ? 0 : sq_sum[pos1 - 1]);
  int  q = static_cast<int>(0.5 + (double) sum_ / (pos2 - pos1));
//느린 방법 - 전부 계산
//  ref = sumSquare(pos1, pos2, q);

  //빠른 방법 - 공식 사용
  ref = sq_sum_ - 2 * q*sum_ + q * q * (pos2 - pos1);
  return ref;
}

int sumSquare(int pos1, int pos2, int q) {
  int sum = 0;
  for (int i = pos1; i < pos2; i++) {
    sum += (arr[i] - q) * (arr[i] - q);
  }
  return sum;
}