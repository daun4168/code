#define N 4

typedef struct {
  int strike;

  int ball;

} Result;

// API

extern Result query(int guess[]);

Result check(int guess[], int digits[]) {
	Result result;

  int digits_c[10] = {0};
  for (int idx = 0; idx < N; ++idx) 
		digits_c[digits[idx]]++;
	
	result.strike = 0;
	result.ball = 0;

	for (int idx = 0; idx < N; ++idx)
		if (guess[idx] == digits[idx])
			result.strike++;
		else if (digits_c[guess[idx]] > 0)
			result.ball++;

	return result;
}

void doUserImplementation(int guess[]) {
  int** possible;
  possible = new int*[5040];
  int possible_num = 0;

  for (int i1 = 0; i1 < 10; i1++) {
    for (int i2 = 0; i2 < 10; i2++) {
      if(i2 == i1) continue;
      for (int i3 = 0; i3 < 10; i3++) {
        if(i3 == i1 || i3 == i2) continue;
        for (int i4 = 0; i4 < 10; i4++) {
          if(i4 == i1 || i4 == i2 || i4 == i3) continue;
          int* new_num = new int[4];
          new_num[0] = i1;
          new_num[1] = i2;
          new_num[2] = i3;
          new_num[3] = i4;
          possible[possible_num] = new_num;
          possible_num++;
        }
      }
    }
  }

  while(true){
    int* guessed = possible[0];
    Result result = query(guessed);
    
    if(result.strike == 4){
      guess[0] = guessed[0];
      guess[1] = guessed[1];
      guess[2] = guessed[2];
      guess[3] = guessed[3];
      for(int i=0;i<possible_num;i++){
        delete[] possible[i];
      }
      delete[] possible;

      return;
    }
    
    possible[0] = possible[possible_num-1];
    possible_num--;

    for(int check_num = 0;check_num < possible_num;){
      Result check_result = check(guessed, possible[check_num]);
      if(check_result.ball == result.ball && check_result.strike == result.strike){
        check_num++;
      } else {
        delete[] possible[check_num];
        possible_num--;
        if(possible_num > check_num){
          possible[check_num] = possible[possible_num];
        }
      }
    }
    delete[] guessed;
  }
}