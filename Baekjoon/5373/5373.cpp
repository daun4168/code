#include <iostream>
#include <string>
#include <unordered_map>

using std::cin, std::cout, std::endl;
using std::string;
using std::unordered_map;

constexpr int NUM_LEN = 3;

enum FACE {
  UP = 0,
  BACK = 1,
  FRONT = 2,
  DOWN = 3,
  LEFT = 4,
  RIGHT = 5,
};

constexpr char FACE_COLOR[] = {'w', 'o', 'r', 'y', 'g', 'b'};
const unordered_map<char, int> DirToFace{
    {'U', UP},   {'B', BACK}, {'F', FRONT},
    {'D', DOWN}, {'L', LEFT}, {'R', RIGHT},
};

char cube[6][NUM_LEN][NUM_LEN];

int up_face(const int face) { return (7 - face) % 6; }
int right_face(const int face) { return (5 - face) % 6; }
int left_face(const int face) { return (face + 4) % 6; }
int down_face(const int face) { return (face + 2) % 6; }

void rotate_face(int face, bool circle) {
  char copy_arr[NUM_LEN][NUM_LEN];
  for (int y = 0; y < NUM_LEN; y++) {
    for (int x = 0; x < NUM_LEN; x++) {
      copy_arr[y][x] = cube[face][y][x];
    }
  }

  for (int y = 0; y < NUM_LEN; y++) {
    for (int x = 0; x < NUM_LEN; x++) {
      if (circle)
        cube[face][x][NUM_LEN - y - 1] = copy_arr[y][x];
      else
        cube[face][NUM_LEN - x - 1][y] = copy_arr[y][x];
    }
  }

  if (circle) {
    char t1, t2, t3;
    t1 = cube[right_face(face)][2][2];
    t2 = cube[right_face(face)][1][2];
    t3 = cube[right_face(face)][0][2];

    cube[right_face(face)][2][2] = cube[up_face(face)][0][2];
    cube[right_face(face)][1][2] = cube[up_face(face)][0][1];
    cube[right_face(face)][0][2] = cube[up_face(face)][0][0];

    cube[up_face(face)][0][2] = cube[left_face(face)][2][0];
    cube[up_face(face)][0][1] = cube[left_face(face)][2][1];
    cube[up_face(face)][0][0] = cube[left_face(face)][2][2];

    cube[left_face(face)][2][0] = cube[down_face(face)][0][0];
    cube[left_face(face)][2][1] = cube[down_face(face)][1][0];
    cube[left_face(face)][2][2] = cube[down_face(face)][2][0];

    cube[down_face(face)][0][0] = t1;
    cube[down_face(face)][1][0] = t2;
    cube[down_face(face)][2][0] = t3;
  } else {
    char t1, t2, t3;
    t1 = cube[right_face(face)][2][2];
    t2 = cube[right_face(face)][1][2];
    t3 = cube[right_face(face)][0][2];

    cube[right_face(face)][2][2] = cube[down_face(face)][0][0];
    cube[right_face(face)][1][2] = cube[down_face(face)][1][0];
    cube[right_face(face)][0][2] = cube[down_face(face)][2][0];

    cube[down_face(face)][0][0] = cube[left_face(face)][2][0];
    cube[down_face(face)][1][0] = cube[left_face(face)][2][1];
    cube[down_face(face)][2][0] = cube[left_face(face)][2][2];

    cube[left_face(face)][2][0] = cube[up_face(face)][0][2];
    cube[left_face(face)][2][1] = cube[up_face(face)][0][1];
    cube[left_face(face)][2][2] = cube[up_face(face)][0][0];

    cube[up_face(face)][0][2] = t1;
    cube[up_face(face)][0][1] = t2;
    cube[up_face(face)][0][0] = t3;
  }
}

void init_cube() {
  for (int face = 0; face < 6; face++) {
    for (int y = 0; y < NUM_LEN; y++) {
      for (int x = 0; x < NUM_LEN; x++) {
        cube[face][y][x] = FACE_COLOR[face];
      }
    }
  }
}

int main() {
  int T;
  cin >> T;

  for (int t = 0; t < T; t++) {
    init_cube();

    int N;
    cin >> N;

    for (int n = 0; n < N; n++) {
      string str;
      cin >> str;

      int face = DirToFace.at(str[0]);
      bool sign = str[1] == '+' ? true : false;

      rotate_face(face, sign);
    }

    // print UP colors
    for (int y = 0; y < NUM_LEN; y++) {
      for (int x = 0; x < NUM_LEN; x++) {
        cout << cube[UP][y][x];
      }
      cout << endl;
    }
  }
}