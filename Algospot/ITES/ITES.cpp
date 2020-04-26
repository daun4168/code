//참고 : Queue를 안쓰는게 더 빠르다

#include <iostream>

using namespace std;

int up(unsigned int& a) {
  int signal = static_cast<int>((a % 10000) + 1);
  a = (a * 214013 + 2531011);
  return signal;
}

int main() {
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    int K, N;
    cin >> K >> N;
    int head = -1, tail = -1;
    unsigned int head_a = 1983;
    unsigned int tail_a = 1983;
    int section_sum = 0;
    int section_num = 0;
    while (head < N) {
      if (section_sum == K) {
        section_num++;
        head++;
        section_sum += up(head_a);
      } else if (section_sum < K) {
        head++;
        section_sum += up(head_a);
      } else {
        tail++;
        section_sum -= up(tail_a);
      }
    }
    cout << section_num << '\n';
  }
  return 0;
}
