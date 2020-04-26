#include <stdio.h>
#include <string.h>
#include <map>
#include <iostream>
#include <algorithm>

#ifdef __GNUC__
#define putchar putchar_unlocked
#define getchar getchar_unlocked
#elif _MSC_VER
#endif

char _c;
#define scan(x) do{while((x=getchar())<'0'); \
for(x-='0'; '0'<=(_c=getchar()); \
x = x*10 + _c -'0'); }while(0)

char _b[11];
int _k;
#define print(x) do{ _k = 9;\
while (x) { _b[_k--] = x%10 + '0'; x/=10; }\
while (_b[_k] != '\n') putchar(_b[++_k]); } while(0)

using namespace std;

map<int, int> coords;


bool isDominated(int x, int y);
void removeDominated(int x, int y);
int registered(int x, int y);

int main() {
  freopen("sample_input.txt", "r", stdin);
  _b[10] = '\n';
  int C;
  
  std::cin >> C;
  for (int c = 0; c < C; c++) {
    coords.clear();
    int N, p, q;
    int size = 0;
    std::cin >> N;
    for (int n = 0; n < N; n++) {
      std::cin >> p >> q;
      size += registered(p, q);
    }
    print(size);
  }
  return 0;
}

bool isDominated(int x, int y)
{
  auto it = coords.lower_bound(x);
  if (it == coords.end()) return false;
  return y < it->second;
}

void removeDominated(int x, int y) {
  map<int, int>::iterator it;
  it = coords.lower_bound(x);
  if (it == coords.begin()) return;
  --it;
  while (true) { 
    if (it->second > y) break;
    if (it == coords.begin()) {
      coords.erase(it);
      break;
    }
    map<int, int>::iterator jt = it;
    --jt;
    coords.erase(it);
    it = jt;
  }
}

int registered(int x, int y) {
  if (isDominated(x, y)) return coords.size();
  removeDominated(x, y);
  coords[x] = y;
  return coords.size();
}
