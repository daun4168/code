#pragma once

#include <vector>

std::vector<int> connect(const std::vector<int>&a, const std::vector<int>&b, int k);
std::vector<int> sub(const std::vector<int>&a, const std::vector<int>&b);
std::vector<int> mul(const std::vector<int>&a, const std::vector<int>&b);
void normalize(std::vector<int>& num);
std::vector<int> karatsuba(const std::vector<int>&a, const std::vector<int>& b);