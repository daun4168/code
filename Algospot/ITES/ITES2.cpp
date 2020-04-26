#include <iostream>

using namespace std;

class randomQueue {
public:
  randomQueue() {
    arr = new int[50000];
    head =  -1;
    tail = -1;
    last_a = 1983;
  }
  int& push() {
    ++head;
    head %= 50000;
    arr[head] = static_cast<int>((last_a % 10000) + 1);
    last_a = (last_a * 214013 + 2531011);
    return arr[head];
  }
  int& pop() {
    ++tail;
    tail %= 50000;
    return arr[tail];
  }
  unsigned int last_a;
  int head;
  int tail;
  int* arr;
};

int main() {
  int test_case;
  cin >> test_case;
  for (int t = 0; t < test_case; t++) {
    randomQueue r;
    int K, N;
    cin >> K >> N;
    int head = -1;
    int section_sum = 0;
    int section_num = 0;
    while (head < N) {
      if (section_sum == K) {
        section_num++;
        head++;
        section_sum += r.push();
      } else if (section_sum < K) {
        head++;
        section_sum += r.push();
      } else {
        section_sum -= r.pop();
      }
    }
    cout << section_num << '\n';
  }
  return 0;
}
