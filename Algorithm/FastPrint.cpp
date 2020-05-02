#include <iostream>

#ifdef __GNUC__
#define putchar putchar_unlocked
#define getchar getchar_unlocked
#elif _MSC_VER
#endif

char _c, _b[11];
int _x, _k;
#define scan(x) do{while((x=getchar())<'0'); \
for(x-='0'; '0'<=(_c=getchar()); x = x*10 + _c -'0'); }while(0)
#define scani(x) do{while((x=getchar())<'-'); \
if(x == '-'){x=getchar();for(x-='0'; '0'<=(_c=getchar()); x = x*10 + _c -'0');x=-x;}\
else { for (x -= '0'; '0' <= (_c = getchar()); x = x * 10 + _c - '0'); }}while (0)
#define print(x) do{ _x = x;\
for (_k = 0; _x > 0; _k++, _x /= 10) _b[_k] = _x % 10 + '0'; \
for (_k--; _k >= 0; _k--) putchar(_b[_k]); } while (0)
#define printi(x) do{_x = x;\
if(_x > 0) {for (_k = 0; _x > 0; _k++, _x /= 10) _b[_k] = _x % 10 + '0'; \
for (_k--; _k >= 0; _k--) putchar(_b[_k]);} else if (_x == 0) putchar('0'); \
else { putchar('-'); _x = -_x;\
for (_k = 0; _x > 0; _k++, _x /= 10) _b[_k] = _x % 10 + '0'; \
for (_k--; _k >= 0; _k--) putchar(_b[_k]);}} while (0)
#define eol putchar('\n')
#define space putchar(' ')

// using namespace std;

// int main() {
//   std::ios::sync_with_stdio(false);
//   int C;
//   scan(C);
//   for (int c = 0; c < C; c++) {
    

//   }
//   return 0;
// }

