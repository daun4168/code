#include <cstdio>

int main(){
  int T;
  scanf("%d", &T);
  for(int t = 1;t <= T;t++){
    int N;
    scanf("%d", &N);
    long long int * prices = new long long int[N];

    for(int n = 0;n < N;n++){
      scanf("%lld", prices + n);
    }

    long long int max_price = prices[N - 1];
    long long int revenue = 0;

    for(int i = N - 2;i >= 0;i--){
      if(prices[i] < max_price){
        revenue += max_price - prices[i];
      } else {
        max_price = prices[i];
      }
    }
    printf("#%d %lld\n", t, revenue);

    delete[] prices;
  }
  

  return 0;
}