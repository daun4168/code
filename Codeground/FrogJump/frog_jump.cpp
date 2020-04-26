#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

int Answer;
int a[1000000];

int main(int argc, char** argv)
{
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int T, test_case;
  // freopen("frog_jump_input.txt", "r", stdin);
  cin >> T;
  for (test_case = 0; test_case < T; test_case++)
  {
    int N, K;

    cin >> N;   
    for (int i = 0; i < N; i++) {
      cin >> a[i];
    }
    cin >> K;

    int before_jump = 0;
    int before_stone = 0;
    int jump_num = 0;
    bool can_jump = true;

    for (int i = 0; i < N; i++) {

      if (a[i] - before_stone > K) {
        can_jump = false;
        break;
      }

      if (a[i] - before_jump > K) {
        jump_num++;
        before_jump = before_stone;
      }
      before_stone = a[i];

    }

    if (can_jump)
      Answer = jump_num + 1;
    else
      Answer = -1;

    cout << "Case #" << test_case + 1 << endl;
    cout << Answer << endl;
  }

  return 0;
}

