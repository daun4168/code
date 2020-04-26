#include <iostream>
#include <exception>

using namespace std;

void jumpgame();
bool isWay(int width, int height);

int** grid;
bool** is_way;
int n;

class myException : public exception {
public:
  myException() : exception() { }
  const char* what() const noexcept {
    return "YES";
  }
}end_exception;

int main() {
  std::ios::sync_with_stdio(false);

  int test_case;
  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    jumpgame();
  }
  return 0;
}

void jumpgame() {
  cin >> n;
  grid = new int*[n];
  is_way = new bool*[n];
  for (int i = 0; i < n; i++) {
    grid[i] = new int[n];
    is_way[i] = new bool[n];
    for (int j = 0; j < n; j++) {
      cin >> grid[i][j];
      is_way[i][j] = true;
    }
  }
  try {
    isWay(0, 0);
    cout << "NO\n";
  }
  catch (myException &e) {
    cout << e.what() << endl;
  }
  for (int i = 0; i < n; i++) {
    delete[] grid[i];
    delete[] is_way[i];
  }
  delete[]grid;
  delete[] is_way;
}

bool isWay(int width, int height) {
  if (width >= n || height >= n)return false;
  if (!is_way[width][height]) return false;
  if (grid[width][height] == 0) {
    cout << "YES\n";
    throw end_exception;
  }
  isWay(width + grid[width][height], height);
  isWay(width, height + grid[width][height]);
  is_way[width][height] = false;
  return false;
}
