#pragma once

template<typename T>
class clist {
private:
  struct node {
    T value;
    node* next;
    node* last;
  };
public:
  class iterator {
  public:
    iterator(node* ptr) :ptr(ptr) { }
    iterator& operator++() {
      ptr = ptr->next;
      return (*this);
    }
    iterator& operator--() {
      ptr = ptr->last;
      return (*this);
    }
    iterator operator++(int) {
      iterator temp = (*this);
      ++*this;
      return temp;
    }
    iterator operator--(int) {
      iterator temp = (*this);
      --*this;
      return temp;
    }
    bool operator==(iterator& iter) {
      return this->ptr == iter.ptr;
    }
    bool operator!=(iterator& iter) {
      return !(this->ptr == iter.ptr);
    }
    T& operator*() {
      return ptr->value;
    }
  private:
    friend iterator clist<T>::erase(iterator&);
    node* ptr;
  };
  clist() {
    size_ = 0;
  }
  clist(const clist<T>& old) {
    if (this != &old) {
      size_ = 0;
      auto& iter = old.begin();
      for (int i = 0; i < old.size(); i++) {
        push_back(*iter);
        ++iter;
      }
    }
  }
  clist<T>& operator=(const clist<T>& old) {
    if (this != &old) {
      clear();
      size_ = 0;
      auto& iter = old.begin();
      for (int i = 0; i < old.size(); i++) {
        push_back(*iter);
        ++iter;
      }
    }
    return (*this);
  }
  ~clist() {
    clear();
  }
  void clear() {
    node* pnode = begin_;
    while (size_ > 0) {
      node* pnext = pnode->next;
      delete pnode;
      pnode = pnext;
      size_--;
    }
  }
  iterator push_back(T value) {
    if (size_ == 0) {
      begin_ = new node;
      begin_->value = value;
      begin_->next = begin_;
      begin_->last = begin_;
      fin_ = begin_;
    } else {
      node* new_node = new node;
      new_node->value = value;
      fin_->next = new_node;
      new_node->last = fin_;
      begin_->last = new_node;
      new_node->next = begin_;
      fin_ = new_node;
    }
    size_++;
    return iterator(fin_);
  }
  iterator pop_front() {
    erase(iterator(begin_));
  }
  iterator erase(iterator& iter) {
    if (size_ == 1) {
      delete iter.ptr;
      size_ = 0;
      return end();
    }
    node* last_node = iter.ptr->last;
    node* next_node = iter.ptr->next;
    last_node->next = next_node;
    next_node->last = last_node;
    if (iter.ptr == begin_) {
      begin_ = next_node;
    }
    if (iter.ptr == fin_) {
      fin_ = last_node;
    }
    delete iter.ptr;
    size_--;
    return iterator(next_node);
  }
  bool empty() {
    return size_ == 0;
  }
  int size() { return size_; }
  T& front() {
    return begin_->value;
  }
  iterator begin() { return iterator(begin_); }
  iterator end() { return iterator(begin_); }
private:
  int size_;
  node* begin_;
  node* fin_;
};
