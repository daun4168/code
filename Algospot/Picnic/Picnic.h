#ifndef PICNIC_H
#define PICNIC_H

#include <iostream>

using namespace std;

class Picnic {
public:
  Picnic();
private:
  bool areFriends_[10][10];
  int student_, pair_;
  int way_;
  int countPairings(bool taken[10]);
};

#endif // PICNIC_H
