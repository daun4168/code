#include <iostream>
#include <string>

using namespace std;

int main() {
  int line_num;
  cin >> line_num;
  for (int i = 0; i < line_num; i++) {
    string s;
    int delete_num;
    cin >> delete_num>> s;
    cout << i + 1 << " " << 
      s.substr(0, delete_num-1) + s.substr(delete_num)<< endl;
  }
}