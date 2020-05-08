template <typename T>
void initArray(T* arr, T value, unsigned n) {
  while (n--) *arr++ = value;
}

template <typename T>
void quickSort(T input[], int first, int last) {
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

// return new data_num
template <typename T>
int removeDuplicate(T input[], int data_num) {
  if (data_num <= 1) return data_num;
  T before = input[0];
  int new_data_num = 1;
  for (int i = 1; i < data_num; i++) {
    if (input[i] == before) continue;
    input[new_data_num++] = input[i];
    before = input[i];
  }
  return new_data_num;
}

template <typename T>
class MultiMap {
 public:
  struct Node {
    int key = 0;
    T* data = nullptr;
    int data_num = 0;
    int arr_size = 0;
    Node* next_node = nullptr;

    ~Node() {
      delete[] data;
      data = nullptr;
    }
  };

  explicit MultiMap(int n = 500) {
    this->_size = n;
    _tb = new Node*[n];
    for (int i = 0; i < n; i++) {
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

  unsigned hash(const int i) { return (i * 2654435761ll) % _size; }

  Node* find(const int key) {
    unsigned h = hash(key);

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
    unsigned h = hash(key);
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

  void add(int key, const T& data) {
    unsigned h = hash(key);

    if (_tb[h] != nullptr) {
      Node* last_node = _tb[h];
      Node* next_node = _tb[h];
      bool is_append = false;

      while (next_node != nullptr) {
        if (next_node->key == key) {
          is_append = true;

          if (next_node->data_num >= next_node->arr_size) {
            T* new_data = new T[next_node->arr_size * 2];
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
        new_node->data = new T[1];
        new_node->data[0] = data;
        new_node->data_num = 1;
        new_node->arr_size = 1;
        last_node->next_node = new_node;
      }
    } else {
      Node* new_node = new Node;
      new_node->key = key;
      new_node->data = new T[1];
      new_node->data[0] = data;
      new_node->data_num = 1;
      new_node->arr_size = 1;
      _tb[h] = new_node;
    }
  }

 private:
  Node** _tb;
  int _size;
};


// template <typename T>
// class Deque {
//  public:
//   Deque() {}
//   ~Deque() {}
//   Deque& operator=(const Deque& x) {}  // copy
//   Deque& operator=(Deque&& x) {}       // move

//   unsigned size() {}
//   void resize(unsigned n) {}
//   void resize(unsigned n, const T& val) {}
//   bool empty() {}

//   T& front() {}
//   T& back() {}
//   void push_back(const T& val) {}
//   void push_back(T&& val) {}
//   void push_front(const T& val) {}
//   void push_front(T&& val) {}
//   void pop_back() {}
//   void pop_front() {}
//   void clear() {}

//   bool operator==(const Deque& x) {}  // is same
//   bool operator!=(const Deque& x) {}  // is same

//  private:
//   T* _arr = nullptr;
//   unsigned _size = 0;
//   unsigned _capacity = 0;
//   unsigned _front_idx = 0;
//   unsigned _back_idx = 0;
// };
