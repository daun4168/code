// Copyright 2020 Daun Jeong
// Author: Daun Jeong
#pragma once

#include <iostream>

#include "Default.h"

namespace daun {

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  if (!v.empty()) {
    for (const auto& ele : v) {
      os << ele << ' ';
    }
  }
  return os;
}
}  // namespace daun
