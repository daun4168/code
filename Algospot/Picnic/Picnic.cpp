#include <iostream>
#include "Picnic.h"

using namespace std;

Picnic::Picnic() {
  cin >> student_ >> pair_;
  way_ = 0;
  bool arr[10];
  for (int i = 0; i < student_; i++) {
    for (int j = 0; j < student_; j++) {
      areFriends_[i][j] = false;
    }
    arr[i] = false;
  }
  for (int i = 0; i < pair_; i++) {
    int st1, st2;
    cin >> st1 >> st2;
    areFriends_[st1][st2] = true;
    areFriends_[st2][st1] = true;
  }
  cout << countPairings(arr) << endl;
}

int Picnic::countPairings(bool isPaired[10]) {
  //짝 지을 학생이 남았는지 확인
  bool finish = true;
  for (int i = 0; i < student_; i++) {
    if (!isPaired[i]) finish = false;
  }
  if (finish) return 1;
  //남았을 경우
  int num_way = 0;
  int first_not_paired = -1;
  for (int i = 0; i < student_; i++) {
    if (!isPaired[i] && (first_not_paired == -1))
      first_not_paired = i;
  }
    for (int j = first_not_paired +1; j < student_; j++) {
      if (!isPaired[first_not_paired] && !isPaired[j] && areFriends_[first_not_paired][j]) {
        isPaired[first_not_paired] = true;
        isPaired[j] = true;
        num_way = num_way + countPairings(isPaired);
        isPaired[first_not_paired] = false;
        isPaired[j] = false;
      }
    } 
  return num_way;
}