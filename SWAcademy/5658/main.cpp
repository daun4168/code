#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_STR (28 + 1 + 7)

int N, K;
int R;
char str[MAX_STR];
int arr[28];

int pow(int a, int b) {
  int mul = 1;
  for (int i = 0; i < b; i++) {
    mul *= a;
  }
  return mul;
}

int str_to_int(int s_pos, int e_pos) {
  int num = 0;
  for(int i = 0;i<e_pos - s_pos;i++){
    char ch = str[e_pos - i - 1];
    int this_num;
    if(ch <= '9' && ch >= '0'){
      this_num = static_cast<int>(ch - '0');
    } else if(ch <='F' && ch >= 'A'){
      this_num = static_cast<int>(ch - 'A') + 10;
    }
    num += pow(16, i) * this_num;
  }

  return num; 
}

template <typename DataType>
void quickSort(DataType input[], int first, int last) {
  int pivot;
  int i;
  int j;
  int temp;

  if (first < last - 1) {
    pivot = first;
    i = first;
    j = last - 1;

    while (i < j) {
      while (input[i] <= input[pivot] && i < last - 1) {
        i++;
      }
      while (input[j] > input[pivot]) {
        j--;
      }
      if (i < j) {
        temp = input[i];
        input[i] = input[j];
        input[j] = temp;
      }
    }

    temp = input[pivot];
    input[pivot] = input[j];
    input[j] = temp;

    quickSort(input, first, j);
    quickSort(input, j + 1, last);
  }
}

template <typename DataType>
int removeDuplicate(DataType input[], int data_num) {
  if (data_num <= 1) return data_num;
  DataType before = input[0];
  int new_data_num = 1;
  for (int i = 1; i < data_num; i++) {
    if (input[i] == before) continue;
    input[new_data_num++] = input[i];
    before = input[i];
  }
  return new_data_num;
}

int calc_answer() {
  int answer = 0;

  for (int r = 0; r < R; r++) {
    for (int i = 0; i < 4; i++) {
      arr[i + 4 * r] = str_to_int(R * i + r, R * (i + 1) + r);
    }
  }

  quickSort(arr, 0, 4 * R);
  int data_num = removeDuplicate(arr, 4 * R);

  return arr[data_num - K];
}

int main() {
  int T;

  freopen("sample_input.txt", "r", stdin);
  setbuf(stdout, NULL);

  scanf("%d", &T);
  for (int testcase = 1; testcase <= T; ++testcase) {
    scanf("%d %d", &N, &K);
    scanf("%s", str);
    R = N / 4;
    for (int i = N; i < N + R; i++) {
      str[i] = str[i % N];
    }

    int answer = calc_answer();
    printf("#%d %d\n", testcase, answer);
  }
  return 0;
}