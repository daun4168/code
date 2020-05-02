template<typename T>
constexpr const T& max (const T& a, const T& b) {
  return (a > b) ? a : b;
}

template<typename T>
constexpr const T& min (const T& a, const T& b) {
  return !(a < b) ? b : a;
}

template <typename T>
constexpr const T pow(const T x, unsigned const n) {
  return n == 0 ? 1
                : n % 2 == 0 ? pow(x * x, n / 2) : pow(x * x, (n - 1) / 2) * x;
}

template <typename T>
void memset(T *s, const T& c, unsigned long n) {
  while (n--) *s++ = c;
}

void memcpy(void *dest, const void *src, unsigned long count) {
  char *tmp = static_cast<char*>(dest);
  const char *s = static_cast<const char*>(src);
  while (count--) *tmp++ = *s++;
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

template <typename DataType>
class MultiMap {
 public:
  struct Node {
    int key = 0;
    DataType* data = nullptr;
    int data_num = 0;
    int arr_size = 0;
    Node* next_node = nullptr;

    ~Node() {
      delete[] data;
      data = nullptr;
    }
  };

  MultiMap(int size = 500) {
    this->_size = size;
    _tb = new Node*[size];
    for (int i = 0; i < size; i++) {
      _tb[i] = nullptr;
    }
  }
  ~MultiMap() {
    for (int i = 0; i < _size; i++) {
      Node* next_node = _tb[i];
      while (next_node != nullptr) {
        Node* this_node = next_node;
        next_node = this_node->next_node;
        delete this_node;
      }
    }
    delete[] _tb;
  }

  unsigned long hash(const int i) { return (i * 2654435761ll) % _size; }

  Node* find(const int key) {
    unsigned long h = hash(key);

    Node* next_node = _tb[h];
    while (next_node != nullptr) {
      if (next_node->key == key) {
        return next_node;
      }
      next_node = next_node->next_node;
    }
    return nullptr;
  }

  void remove(const int key) {
    if (find(key) == nullptr) return;
    unsigned long h = hash(key);
    if (_tb[h] == nullptr) return;

    if (_tb[h]->key == key) {
      Node* last_node = _tb[h];
      _tb[h] = last_node->next_node;
      delete last_node;
      return;
    }

    Node* last_node = _tb[h];
    Node* next_node = _tb[h];

    while (next_node != nullptr) {
      if (next_node->key == key) {
        last_node->next_node = next_node->next_node;
        delete next_node;
        break;
      }
      last_node = next_node;
      next_node = last_node->next_node;
    }
    return;
  }

  void add(int key, const DataType& data) {
    unsigned long h = hash(key);

    if (_tb[h] != nullptr) {
      Node* last_node = _tb[h];
      Node* next_node = _tb[h];
      bool is_append = false;

      while (next_node != nullptr) {
        if (next_node->key == key) {
          is_append = true;

          if (next_node->data_num >= next_node->arr_size) {
            DataType* new_data = new DataType[next_node->arr_size * 2];
            for (int i = 0; i < next_node->data_num; i++) {
              new_data[i] = next_node->data[i];
            }
            delete[] next_node->data;
            next_node->data = new_data;
            next_node->arr_size *= 2;
          }
          next_node->data[next_node->data_num] = data;
          next_node->data_num += 1;
          break;
        }
        last_node = next_node;
        next_node = last_node->next_node;
      }

      if (!is_append) {
        Node* new_node = new Node;
        new_node->key = key;
        new_node->data = new DataType[1];
        new_node->data[0] = data;
        new_node->data_num = 1;
        new_node->arr_size = 1;
        last_node->next_node = new_node;
      }
    } else {
      Node* new_node = new Node;
      new_node->key = key;
      new_node->data = new DataType[1];
      new_node->data[0] = data;
      new_node->data_num = 1;
      new_node->arr_size = 1;
      _tb[h] = new_node;
    }
  }
  Node** _tb;
  int _size;
};

// NOT IMPLEMENTED
template <typename DataType>
class Vector {
 public:
  Vector() {}
  ~Vector() { delete[] _arr; }
  int size() { return _size; }

 private:
  int _size = 0;
  DataType* _arr = nullptr;
  int _arr_size = 0;
};

#include <iostream>
using namespace std;
int main() {
  MultiMap<double> map(100);
  map.add(1, 10.2);
  map.add(2, 10.5);
  map.add(1, 20.2);
  map.remove(2);
  map.add(2, 40.1);

  auto f1 = map.find(1);
  auto f2 = map.find(2);

  for (int i = 0; i < f1->data_num; i++) {
    cout << f1->data[i] << endl;
  }

  for (int i = 0; i < f2->data_num; i++) {
    cout << f2->data[i] << endl;
  }
  int a[10] = {15, 3, 5, 700, 3, 6, 7, 8, 9, 10};
  quickSort(a, 0, 10);
  for (auto i : a) {
    cout << i << endl;
  }
  cout << "--------------------------\n";
  int data_num = removeDuplicate(a, 10);
  for (int i = 0; i < data_num; i++) {
    cout << a[i] << endl;
  }
}