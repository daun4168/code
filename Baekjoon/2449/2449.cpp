#include <iostream>

using std::cin, std::cout;

constexpr int MAX_N = 200;
constexpr int MAX_K = 20;


int N, K;
int bulb[MAX_N];

int main(){
  cin >> N >> K;
  for(int i = 0;i<N;i++){
    cin >> bulb[i];
  }

  return 0;
}