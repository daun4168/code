#define MAX 30000
struct Node {
  int key = 0;
  int* data = nullptr;
  int data_num = 0;
  int arr_size = 0;
  Node* next_node = nullptr;

  ~Node() {
    delete[] data;
    data = nullptr;
  }
};

class Hash {
 public:
  Hash(int size = 50000) {
    this->size = size;
    this->used_num = 0;
    tb = new Node*[size];
    for (int i = 0; i < size; i++) {
      tb[i] = nullptr;
    }
  }
  ~Hash() {
    for (int i = 0; i < size; i++) {
      Node* next_node = tb[i];
      while (next_node != nullptr) {
        Node* this_node = next_node;
        next_node = this_node->next_node;
        delete this_node;
      }
    }
    delete[] tb;
  }

  unsigned long hash(int i) { return (i * 2654435761ll) % size; }

  Node* find(int key) {
    unsigned long h = hash(key);

    Node* next_node = tb[h];
    while (next_node != nullptr) {
      if (next_node->key == key) {
        return next_node;
      }
      next_node = next_node->next_node;
    }
    return nullptr;
  }

  void remove(int key) {
    if(find(key) == nullptr) return;
    unsigned long h = hash(key);
    if (tb[h] == nullptr) return;

    if(tb[h]->key == key){
      Node* last_node = tb[h];
      tb[h] = last_node->next_node;
      delete last_node;
      return;
    }

    Node* last_node = tb[h];
    Node* next_node = tb[h];

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

  int add(int key, int data) {
    unsigned long h = hash(key);

    if (tb[h] != nullptr) {
      Node* last_node = tb[h];
      Node* next_node = tb[h];
      bool is_append = false;

      while (next_node != nullptr) {
        if (next_node->key == key) {
          is_append = true;

          if (next_node->data_num >= next_node->arr_size) {
            int* new_data = new int[next_node->arr_size * 2];
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
        new_node->data = new int[1];
        new_node->data[0] = data;
        new_node->data_num = 1;
        new_node->arr_size = 1;
        last_node->next_node = new_node;
      }
    } else {
      Node* new_node = new Node;
      new_node->key = key;
      new_node->data = new int[1];
      new_node->data[0] = data;
      new_node->data_num = 1;
      new_node->arr_size = 1;
      tb[h] = new_node;
    }
  }
  Node** tb;
  int size;
  int used_num;
};

int pow(int a, int b) {
  int mul = 1;
  for (int i = 0; i < b; i++) {
    mul *= a;
  }
  return mul;
}
int sum_of_4square(const int block[4][4]) {
  int min = block[0][0];
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (block[y][x] < min) min = block[y][x];
    }
  }

  int sum = 0;
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      sum += pow(81, y) * pow(3, x) * (block[y][x] - min);
    }
  }
  return sum;
}

void add_block(Hash& hash, const int block[4][4]) {
  int min = block[0][0];
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (block[y][x] < min) min = block[y][x];
    }
  }
  int sum = sum_of_4square(block);
  hash.add(sum, min);
}

void quickSort(int input[], int first, int last) {
  int pivot;
  int i;
  int j;
  int temp;

  if (first < last) {
    pivot = first;
    i = first;
    j = last;

    while (i < j) {
      while (input[i] <= input[pivot] && i < last) {
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

    quickSort(input, first, j - 1);
    quickSort(input, j + 1, last);
  }
}

void rotate_blocks(const int block[4][4], int rblocks[4][4][4]) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      rblocks[0][y][x] = block[y][x];
    }
  }

  for (int rt = 1; rt < 4; rt++) {
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        rblocks[rt][x][3 - y] = rblocks[rt - 1][y][x];
      }
    }
  }
}

void fold_block(const int block[4][4], int fblock[4][4]) {
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      fblock[y][x] = block[y][3 - x];
    }
  }
}

int calc_max_diff(const int block[4][4]) {
  int min = block[0][0];
  int max = block[0][0];
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (block[y][x] < min) min = block[y][x];
      if (block[y][x] > max) max = block[y][x];
    }
  }
  return max - min;
}

void opp_blocks(const int block[4][4], int oppblocks[4][4][4]) {
  int min = block[0][0];
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (block[y][x] < min) min = block[y][x];
    }
  }
  int diff = calc_max_diff(block);

  int new_block[4][4];
  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      new_block[y][x] = diff - (block[y][x] - min);
    }
  }
  int fblock[4][4];
  fold_block(new_block, fblock);
  rotate_blocks(fblock, oppblocks);
}

int is_same_block(const int oblock[4][4], const int cblock[4][4],
                  bool return_max = true) {
  // return -1 if not same
  // return max of cblock if return_max
  // return min of cblock if not return_max

  int diff = oblock[0][0] - cblock[0][0];

  for (int y = 0; y < 4; y++) {
    for (int x = 0; x < 4; x++) {
      if (oblock[y][x] - cblock[y][x] != diff) return -1;
    }
  }

  if (return_max) {
    int max = cblock[0][0];
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        if (cblock[y][x] > max) max = cblock[y][x];
      }
    }
    return max;
  } else {
    int min = cblock[0][0];
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        if (cblock[y][x] < min) min = cblock[y][x];
      }
    }
    return min;
  }
}

bool can_fold(const int oblock[4][4], const int cblock[4][4]) {
  int fblock[4][4];
  fold_block(cblock, fblock);
  int rblocks[4][4][4];
  rotate_blocks(fblock, rblocks);

  for (int i = 0; i < 4; i++) {
    bool is_all_same = true;
    int first_sum = oblock[0][0] + rblocks[i][0][0];
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        if (oblock[y][x] + rblocks[i][y][x] != first_sum) is_all_same = false;
      }
    }
    if (is_all_same) return true;
  }
  return false;
}

int makeBlock(int module[][4][4]) {
  int max_product_sum = 0;
  Hash hash(40000);
  Node* nodeptr;

  for (int block_num = 0; block_num < MAX; block_num++) {
    add_block(hash, module[block_num]);
  }

  for (int block_num = 0; block_num < MAX; block_num++) {
    nodeptr = hash.find(sum_of_4square(module[block_num]));
    if (nodeptr == nullptr) continue;

    int down_base_num = 0;
    static int down_base_list[MAX];

    int up_base_num = 0;
    static int up_base_list[MAX];

    int max_diff = calc_max_diff(module[block_num]);
    bool can_fold_self = can_fold(module[block_num], module[block_num]);

    int rblocks[4][4][4];
    rotate_blocks(module[block_num], rblocks);

    for (int i = 0; i < 4; i++) {
      nodeptr = hash.find(sum_of_4square(rblocks[i]));
      if (nodeptr == nullptr) continue;
      for (int j = 0; j < nodeptr->data_num; j++) {
        down_base_list[down_base_num++] = nodeptr->data[j];
      }
      hash.remove(sum_of_4square(rblocks[i]));
    }

    if (can_fold_self) {
      if (down_base_num > 1) {
        quickSort(down_base_list, 0, down_base_num);
        for (int i = 0; i * 2 + 1 < down_base_num; i++) {
          max_product_sum += down_base_list[down_base_num - (i * 2) - 1] +
                             down_base_list[down_base_num - (i * 2 + 1) - 1] +
                             max_diff;
        }
      }
    } else {
      int oppblocks[4][4][4];
      opp_blocks(module[block_num], oppblocks);

      for (int i = 0; i < 4; i++) {
        nodeptr = hash.find(sum_of_4square(oppblocks[i]));
        if (nodeptr == nullptr) continue;
        for (int j = 0; j < nodeptr->data_num; j++) {
          up_base_list[up_base_num] = nodeptr->data[j];
          up_base_num += 1;
        }
        hash.remove(sum_of_4square(oppblocks[i]));
      }

      quickSort(down_base_list, 0, down_base_num - 1);
      quickSort(up_base_list, 0, up_base_num - 1);

      int can_make_block_num =
          down_base_num < up_base_num ? down_base_num : up_base_num;

      for (int i = 0; i < can_make_block_num; i++) {
        max_product_sum += down_base_list[down_base_num - i - 1] +
                           up_base_list[up_base_num - i - 1] + max_diff;
      }
    }
  }

  return max_product_sum;
}

