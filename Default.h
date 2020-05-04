// Copyright 2020 Daun Jeong
// Author: Daun Jeong
#pragma once
#include <iostream>

namespace daun {
template <typename T>
struct remove_reference {
  typedef T type;
};

template <typename T>
struct remove_reference<T&> {
  typedef T type;
};

template <typename T>
struct remove_reference<T&&> {
  typedef T type;
};

template <typename T>
constexpr typename remove_reference<T>::type&& move(T&& t) noexcept {
  return static_cast<typename remove_reference<T>::type&&>(t);
}

template <typename InputIt, typename OutputIt>
OutputIt copy(InputIt first, InputIt last, OutputIt d_first) {
  while (first != last) *d_first++ = *first++;
  return d_first;
}

template <typename T>
inline void swap(T& x, T& y) {
  T temp = move(x);
  x = move(y);
  y = move(temp);
}

template <typename T>
void destroy(T* p) {
  p->~T();
}

template <typename T>
void destroy(T* first, T* last) {
  for (; first != last; ++first) destroy(first);
}

template <typename T>
constexpr const T& min(const T& a, const T& b) {
  return !(a < b) ? b : a;
}

template <typename T, typename... Args>
constexpr const T& min(const T& a, const T& b, const Args&... args) {
  return min(min(a, b), args...);
}

template <typename T>
constexpr const T& max(const T& a, const T& b) {
  return (a > b) ? a : b;
}

template <typename T, typename... Args>
constexpr const T& max(const T& a, const T& b, const Args&... args) {
  return max(max(a, b), args...);
}

template <typename T>
constexpr const T pow(const T& x, unsigned const& n) {
  return n == 0 ? 1
                : n % 2 == 0 ? pow(x * x, n / 2) : pow(x * x, (n - 1) / 2) * x;
}

void* memset(void* s, char c, unsigned n) {
  char* p = static_cast<char*>(s);
  while (n--) *p++ = c;
  return s;
}

void* memcpy(void* dest, const void* src, unsigned n) {
  char* tmp = static_cast<char*>(dest);
  const char* s = static_cast<const char*>(src);
  while (n--) *tmp++ = *s++;
  return dest;
}

template <typename T>
class Vector {
 public:
  Vector() = default;                       // default
  explicit Vector(unsigned n) : Vector() {  // fill 1
    resize(n);
  }
  explicit Vector(unsigned n, const T& val) : Vector() {  // fill 2
    resize(n, val);
  }
  Vector(const Vector& x)  // copy
      : _size(x.size()),
        _capacity(x.capacity()),
        _ptr(x.capacity() ? new T[x.capacity()] : nullptr) {
    copy(x.begin(), x.end(), this->begin());
  }
  Vector(Vector&& x) : Vector() {  // move
    using daun::swap;
    swap(*this, x);
  }
  ~Vector() {
    delete[] _ptr;
    _ptr = nullptr;
  }
  Vector& operator=(Vector x) {  // copy & move
    using daun::swap;
    swap(*this, x);
    return *this;
  }

  T* begin() { return _ptr; }
  T* const begin() const { return _ptr; }
  T* end() { return _ptr + _size; }
  T* const end() const { return _ptr + _size; }
  T* const cbegin() const { return _ptr; }
  T* const cend() const { return _ptr + _size; }

  unsigned size() const { return _size; }
  void resize(unsigned n) {
    if (n > size()) {
      _default_append(n - size());
    } else if (n < size()) {
      _erase_at_end(this->_ptr + n);
    }
  }
  void resize(unsigned n, const T& val) {
    if (n > size()) {
      _val_append(n - size(), val);
    } else if (n < size()) {
      _erase_at_end(this->_ptr + n);
    }
  }
  bool empty() const { return begin() == end(); }
  unsigned capacity() const { return _capacity; }
  void reserve(unsigned n) {
    if (capacity() < n) _reallocate(n);
  }

  T& front() { return *begin(); }
  T& back() { return *(end() - 1); }
  void push_back(T val) {
    using daun::swap;
    if (_size >= _capacity) {
      if (_capacity == 0) {
        _reallocate(1);
        _capacity = 1;
      } else {
        _reallocate(_capacity * 2);
        _capacity *= 2;
      }
    }
    swap(_ptr[_size], val);
    _size++;
  }
  void pop_back() {
    if (!empty()) {
      _size--;
      destroy(_ptr + _size);
    }
  }
  void clear() {
    delete[] _ptr;
    _ptr = nullptr;
    _size = 0;
    _capacity = 0;
  }

  T& operator[](unsigned n) { return *(_ptr + n); }
  const T& operator[](unsigned n) const { return *(_ptr + n); }

  void swap(Vector& x) {
    using daun::swap;
    swap(this->_size, x._size);
    swap(this->_capacity, x._capacity);
    swap(this->_ptr, x._ptr);
  }

 private:
  void _reallocate(unsigned n) {
    T* new_arr = new T[n];
    copy(begin(), end(), new_arr);
    delete[] _ptr;
    _ptr = new_arr;
  }
  void _check_capacity(unsigned n) {
    if (n > _capacity) {
      _reallocate(n);
    }
    _capacity = n;
  }
  void _default_append(unsigned n) {
    _check_capacity(_size + n);
    T* p = end();
    for (unsigned i = 0; i < n; i++) *p++ = T();
    _size = _size + n;
  }
  void _val_append(unsigned n, const T& val) {
    _check_capacity(_size + n);
    T* p = _ptr + _size;
    for (unsigned i = 0; i < n; i++){
      *p++ = val;
    }
    _size = _size + n;
  }
  void _erase_at_end(T* pos) {
    unsigned n = end() - pos;
    destroy(pos, end());
    _size -= n;
  }

  T* _ptr{nullptr};
  unsigned _size{0};
  unsigned _capacity{0};
};

template <typename T>
inline void swap(Vector<T>& x, Vector<T>& y) {
  x.swap(y);
}

template <typename T>
inline bool operator==(const Vector<T>& x, const Vector<T>& y) {
  if (x.size() != y.size()) return false;
  for (int idx = 0; idx < x.size(); idx++) {
    if (x[idx] != y[idx]) return false;
  }
  return true;
}

template <typename T>
inline bool operator!=(const Vector<T>& x, const Vector<T>& y) {
  return !(x == y);
}
}  // namespace daun
