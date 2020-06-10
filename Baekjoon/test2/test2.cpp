#include <regex>
#include <string>
#include <vector>
#include <iostream>

auto split(const std::string &s, const std::regex &r){
  auto rit = std::sregex_token_iterator(s.begin(), s.end(), r);
  auto rend = std::sregex_token_iterator();

  //std::cout << static_cast<const std::string>(*rit)[0] << std::endl;
  //std::cout << static_cast<const void*>(&(static_cast<const std::string>(*rit)[0])) << std::endl;

  return std::pair(rit, rend);
}


int main() {
  std::u8string aaaa = u8"abcde";

  std::cout << aaaa << std::endl;
  std::u8string us = u8"abcde";



  return 0;
}