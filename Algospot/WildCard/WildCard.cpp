#include <iostream>
#include <string>
#include <exception>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

void wildCard();
unordered_map<string,bool> memory;

class wildCardException : public std::exception {
public:
  wildCardException(bool isFound) : exception(), isFound(isFound) { }
  const char* what() const noexcept { return "wildCardException"; }
  bool isFound;
}found(true), not_found(false);

int main() {
  int test_case;
  cin >> test_case;
  for (int i = 0; i < test_case; i++) {
    wildCard();
  }
  return 0;
}

bool match(const string& wild, const string& file) {
  int pos = 0;
  auto iter = memory.find(wild + "&" + file);
  if (!(iter == memory.end()) && iter->second == false)
    return false;
  
  while (pos < wild.size() && pos < file.size()) {
    if (wild[pos] != file[pos]) {
      if (wild[pos] == '?') {
      } else if (wild[pos] == '*') {
        for (int i = pos;i<=file.length();i++) {
          match(wild.substr(pos+1), file.substr(i));
        }
      } else {
        memory.insert({ wild + "&" + file, false });
        return false;
      }
    }
    pos++;
  }
  if (pos == wild.size() && pos == file.size())
    throw found;
  if (pos == file.size()) {
    while (pos < wild.size()) {
      if (wild[pos] != '*') {
        memory.insert({ wild + "&" + file, false });
        return false;
      }
      pos++;
    }
    throw found;
  }
  memory.insert({ wild + "&" + file, false });
  return false;
}

void wildCard() {
  memory.clear();
  string wild, file;
  int file_num;
  cin >> wild >> file_num;
  map<string, bool> files;
  for (int k = 0; k < file_num; k++) {
    cin >> file;
    try {
      if (!match(wild, file))
        throw not_found;    
    }
    catch (wildCardException &e) {
      if (e.isFound == true) {
        files.insert({ file, true });
      } else {
        files.insert({ file, false });
      }
    }  
  }
  for (const auto& i : files) {
    if (i.second == true) {
      cout << i.first << endl;
    }
  }
}
