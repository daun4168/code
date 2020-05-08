#include <cstdio>

#define WORD_SIZE 101

int pow(int base, int exp) {
  int num = 1;
  for (int i = 0; i < exp; i++) {
    num *= base;
  }
  return num;
}

bool is_all_alphabet(char** words, int N, int comb) {
  bool is_alphabet[26] = {false};

  for (int n = 0; n < N; n++) {
    if(comb % 2 == 1){

      for(int i = 0;i<WORD_SIZE;i++){
        char ch = words[n][i];
        if(ch == '\0') break;
        is_alphabet[ch-'a'] = true;
      }
      
    }
    comb >>= 1;
  }

  bool all_alphabet = true;
  for (int i = 0; i < 26; i++) {
    if (!is_alphabet[i]) {
      all_alphabet = false;
      break;
    }
  }
  return all_alphabet;
}

int main() {
  freopen("sample_input.txt", "r", stdin);
  setbuf(stdout, NULL);

  int T;
  scanf("%d", &T);

  for (int t = 1; t <= T; t++) {
    int N;
    scanf("%d", &N);

    char** words = new char*[N];
    for (int n = 0; n < N; n++) {
      words[n] = new char[WORD_SIZE];
      scanf("%s", words[n]);
    }

    int comb_max = pow(2, N) - 1;
    int set_num = 0;

    for (int comb = 1; comb <= comb_max; comb++) {
      if (is_all_alphabet(words, N, comb)) set_num++;
    }
    printf("#%d %d\n", t, set_num);

    for (int n = 0; n < N; n++) {
      delete[] words[n];
    }
    delete[] words;
  }
}