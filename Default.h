// Copyright 2020 Daun Jeong
// Author: Daun Jeong
#pragma once
#include <iostream>

namespace daun {

typedef long unsigned int size_t;
typedef long int ptrdiff_t;

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

// remove_const
template <typename T>
struct remove_const {
  typedef T type;
};

template <typename T>
struct remove_const<T const> {
  typedef T type;
};

// remove_volatile
template <typename T>
struct remove_volatile {
  typedef T type;
};

template <typename T>
struct remove_volatile<T volatile> {
  typedef T type;
};

// remove_cv
template <typename T>
struct remove_cv {
  typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

// add_const
template <typename T>
struct add_const {
  typedef T const type;
};

// add_volatile
template <typename T>
struct add_volatile {
  typedef T volatile type;
};

// add_cv
template <typename T>
struct add_cv {
  typedef typename add_const<typename add_volatile<T>::type>::type type;
};

// Alias template for remove_const
template <typename T>
using remove_const_t = typename remove_const<T>::type;

// Alias template for remove_volatile
template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

// Alias template for remove_cv
template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

// Alias template for add_const
template <typename T>
using add_const_t = typename add_const<T>::type;

// Alias template for add_volatile
template <typename T>
using add_volatile_t = typename add_volatile<T>::type;

// Alias template for add_cv
template <typename T>
using add_cv_t = typename add_cv<T>::type;

// Alias template for remove_reference
template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

// Alias template for remove_reference and cv
template <typename T>
using remove_c_ref_t =
    typename remove_const<typename remove_reference<T>::type>::type;

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
void destroy(T first, T last) {
  for (; first != last; ++first) destroy(&(*first));
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

// Marking input iterators.
struct input_iterator_tag {};

// Marking output iterators.
struct output_iterator_tag {};

// Forward iterators support a superset of input iterator operations.
struct forward_iterator_tag : public input_iterator_tag {};

// Bidirectional iterators support a superset of forward iterator
// operations.
struct bidirectional_iterator_tag : public forward_iterator_tag {};

// Random-access iterators support a superset of bidirectional
// iterator operations.
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/* normal_iterator */
template <typename IterType, typename ValueType, typename Container>
class normal_iterator {
 public:
  typedef IterType iterator_type;
  typedef ValueType value_type;
  typedef ptrdiff_t difference_type;
  typedef ValueType& reference;
  typedef ValueType* pointer;
  typedef random_access_iterator_tag iterator_tag;

 protected:
  IterType _current;

 public:
  constexpr normal_iterator() noexcept : _current(IterType()) {}
  explicit normal_iterator(const IterType& it) noexcept : _current(it) {}

  // Allow iterator to const_iterator conversion
  template <typename IterT>
  normal_iterator(const normal_iterator<IterT, remove_const_t<value_type>,
                                        Container>& it) noexcept
      : _current(it.base()) {}

  // Forward iterator requirements
  reference operator*() const noexcept { return *_current; }
  pointer operator->() const noexcept { return _current; }
  normal_iterator& operator++() noexcept {
    ++_current;
    return *this;
  }
  normal_iterator operator++(int) noexcept {
    return normal_iterator(_current++);
  }

  // Bidirectional iterator requirements
  normal_iterator& operator--() noexcept {
    --_current;
    return *this;
  }
  normal_iterator operator--(int) noexcept {
    return normal_iterator(_current--);
  }

  // Random access iterator requirements
  reference operator[](difference_type n) const noexcept { return _current[n]; }
  normal_iterator& operator+=(difference_type n) noexcept {
    _current += n;
    return *this;
  }
  normal_iterator operator+(difference_type n) const noexcept {
    return normal_iterator(_current + n);
  }
  normal_iterator& operator-=(difference_type n) noexcept {
    _current -= n;
    return *this;
  }
  normal_iterator operator-(difference_type n) const noexcept {
    return normal_iterator(_current - n);
  }

  const IterType& base() const noexcept { return _current; }
};

// Forward iterator requirements
template <typename IterTypeL, typename IterTypeR, typename ValueTypeL,
          typename ValueTypeR, typename Container>
inline bool operator==(
    const normal_iterator<IterTypeL, ValueTypeL, Container>& lhs,
    const normal_iterator<IterTypeR, ValueTypeR, Container>& rhs) noexcept {
  return lhs.base() == rhs.base();
}

template <typename IterTypeL, typename IterTypeR, typename ValueTypeL,
          typename ValueTypeR, typename Container>
inline bool operator!=(
    const normal_iterator<IterTypeL, ValueTypeL, Container>& lhs,
    const normal_iterator<IterTypeR, ValueTypeR, Container>& rhs) noexcept {
  return lhs.base() != rhs.base();
}

// Random access iterator requirements
template <typename IterTypeL, typename IterTypeR, typename ValueTypeL,
          typename ValueTypeR, typename Container>
inline bool operator<(
    const normal_iterator<IterTypeL, ValueTypeL, Container>& lhs,
    const normal_iterator<IterTypeR, ValueTypeR, Container>& rhs) noexcept {
  return lhs.base() < rhs.base();
}

template <typename IterTypeL, typename IterTypeR, typename ValueTypeL,
          typename ValueTypeR, typename Container>
inline bool operator>(
    const normal_iterator<IterTypeL, ValueTypeL, Container>& lhs,
    const normal_iterator<IterTypeR, ValueTypeR, Container>& rhs) noexcept {
  return lhs.base() > rhs.base();
}

template <typename IterTypeL, typename IterTypeR, typename ValueTypeL,
          typename ValueTypeR, typename Container>
inline bool operator<=(
    const normal_iterator<IterTypeL, ValueTypeL, Container>& lhs,
    const normal_iterator<IterTypeR, ValueTypeR, Container>& rhs) noexcept {
  return lhs.base() <= rhs.base();
}

template <typename IterTypeL, typename IterTypeR, typename ValueTypeL,
          typename ValueTypeR, typename Container>
inline bool operator>=(
    const normal_iterator<IterTypeL, ValueTypeL, Container>& lhs,
    const normal_iterator<IterTypeR, ValueTypeR, Container>& rhs) noexcept {
  return lhs.base() >= rhs.base();
}

template <typename IterTypeL, typename IterTypeR, typename ValueTypeL,
          typename ValueTypeR, typename Container>
inline auto operator-(
    const normal_iterator<IterTypeL, ValueTypeL, Container>& lhs,
    const normal_iterator<IterTypeR, ValueTypeR, Container>& rhs) noexcept
    -> decltype(lhs.base() - rhs.base()) {
  return lhs.base() - rhs.base();
}

template <typename IterType, typename ValueType, typename Container>
inline normal_iterator<IterType, ValueType, Container> operator+(
    typename normal_iterator<IterType, ValueType, Container>::difference_type n,
    const normal_iterator<IterType, ValueType, Container>& it) noexcept {
  return normal_iterator<IterType, ValueType, Container>(it.base() + n);
}
/*  END OF normal_iterator  */

template <typename T>
class Vector {
 public:
  typedef T value_type;
  typedef const T const_value_type;
  typedef T* pointer;
  typedef const T* const_pointer;
  typedef T& reference;
  typedef const T& const_reference;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef normal_iterator<pointer, value_type, Vector> iterator;
  typedef normal_iterator<const_pointer, const_value_type, Vector>
      const_iterator;
  // typedef  const_reverse_iterator;
  // typedef  reverse_iterator;

 private:
  pointer _start{nullptr};
  pointer _finish{nullptr};
  pointer _end_of_storage{nullptr};

 public:
  // Default Constructor
  Vector() = default;

  // Fill Constructor
  explicit Vector(size_type n) : Vector() { resize(n); }

  // Fill Constructor 2
  explicit Vector(size_type n, const value_type& val) : Vector() {
    resize(n, val);
  }

  // Copy Constructor
  Vector(const Vector& x) : Vector() {
    const size_type size = x.size();
    const size_type capacity = x.capacity();
    pointer tmp = _allocate_and_copy(capacity, x.begin(), x.end());
    _start = tmp;
    _finish = tmp + size;
    _end_of_storage = _start + capacity;
  }

  // Move Constructor
  Vector(Vector&& x) : Vector() {
    using daun::swap;
    swap(*this, x);
  }

  // Destructor
  ~Vector() { clear(); }

  // Assignment Operator
  Vector& operator=(Vector x) {
    using daun::swap;
    swap(*this, x);
    return *this;
  }

  iterator begin() { return iterator(_start); }
  const_iterator begin() const { return const_iterator(_start); }
  iterator end() { return iterator(_finish); }
  const_iterator end() const { return const_iterator(_finish); }
  const_iterator cbegin() const { return const_iterator(_start); }
  const_iterator cend() const { return const_iterator(_finish); }

  // Returns the number of elements
  size_type size() const { return size_type(_finish - _start); }

  // Resizes the Vector to the specified number of elements.
  void resize(size_type new_size) {
    if (new_size > size()) {
      _default_append(new_size - size());
    } else if (new_size < size()) {
      _erase_at_end(this->_start + new_size);
    }
  }

  // Resizes the Vector to the specified number of elements and fill with val.
  void resize(size_type new_size, const value_type& val) {
    if (new_size > size()) {
      _val_append(new_size - size(), val);
    } else if (new_size < size()) {
      _erase_at_end(this->_start + new_size);
    }
  }

  // Returns the total number of elements that the Vector can
  // hold before needing to allocate more memory.
  size_type capacity() const { return size_type(_end_of_storage - _start); }

  // Returns true if the Vector is empty.
  bool empty() const { return begin() == end(); }

  // This function attempts to reserve enough memory for the
  // Vector to hold the specified number of elements.
  void reserve(size_type n) {
    if (capacity() < n) {
      const size_type old_size = size();
      pointer tmp = _allocate_and_copy(n, _start, _finish);
      destroy(_start, _finish);
      delete[] _start;
      _start = tmp;
      _finish = tmp + old_size;
      _end_of_storage = _start + n;
    }
  }

  // Returns a read/write reference to the data at the first element of the
  // Vector.
  reference front() { return *begin(); }

  // Returns a read only reference to the data at the first element of the
  // Vector.
  reference front() const { return *begin(); }

  // Returns a read/write reference to the data at the last element of the
  // Vector.
  reference back() { return *(end() - 1); }

  // Returns a read only reference to the data at the last element of the
  // Vector.
  reference back() const { return *(end() - 1); }

  // Returns a direct pointer to the memory
  pointer data() noexcept { return _start; }

  // Returns a direct const pointer to the memory
  const_pointer data() const noexcept { return _start; }

  // Assigns n of given values to a Vector.
  void assign(size_type n, const value_type& val) {
    destroy(_start, _finish);
    if (capacity() < n) {
      _deallocate(_start, _end_of_storage - _start);
      _create_storage(n);
    }
    pointer p = _start;
    for (size_type i = 0; i < n; i++) *p++ = val;
    _finish = _start + n;
  }

  // Assigns a range to a Vector
  // template <typename InputIter,
  //           typename = std::_RequireInputIter<_InputIterator>>
  // void assign(_InputIterator __first, _InputIterator __last) {}

  // Add data to the end of the Vector.
  void push_back(value_type val) {
    using daun::swap;
    if (size() >= capacity()) {
      size_type new_capacity = capacity() == 0 ? 1 : capacity() * 2;
      reserve(new_capacity);
    }
    swap(*_finish, val);
    _finish++;
  }

  // Removes last element.
  void pop_back() {
    if (!empty()) {
      _finish--;
      destroy(_finish);
    }
  }

  // Erases all the elements.
  void clear() {
    destroy(_start, _finish);
    _deallocate(_start, _end_of_storage - _start);
    _start = nullptr;
    _finish = nullptr;
    _end_of_storage = nullptr;
  }

  // Subscript access to the data contained in the Vector.
  // @return  Read/write reference to data.
  reference operator[](size_type n) { return *(_start + n); }

  // Subscript access to the data contained in the Vector.
  // @return  Read only reference to data.
  const_reference operator[](size_type n) const { return *(_start + n); }

  // Swaps data with another Vector.
  void swap(Vector& x) {
    using daun::swap;
    swap(this->_start, x._start);
    swap(this->_finish, x._finish);
    swap(this->_end_of_storage, x._end_of_storage);
  }

 protected:
  void _default_append(size_type n) {
    if (n == 0) return;
    reserve(size() + n);
    pointer p = _finish;
    for (size_type i = 0; i < n; i++) *p++ = value_type();
    _finish = _finish + n;
  }

  void _val_append(size_type n, const_reference val) {
    if (n == 0) return;
    reserve(size() + n);
    pointer p = _finish;
    for (size_type i = 0; i < n; i++) *p++ = val;
    _finish = _finish + n;
  }

  void _erase_at_end(pointer pos) noexcept {
    destroy(pos, _finish);
    _finish = pos;
  }

  template <typename Iter>
  pointer _allocate_and_copy(size_type n, Iter first, Iter last) {
    pointer result = _allocate(n);
    copy(first, last, result);
    return result;
  }

  pointer _allocate(size_type n) {
    return n != 0 ? new value_type[n] : pointer();
  }

  void _deallocate(pointer ptr, size_type n) {
    if (n != 0) delete[] ptr;
  }

  void _create_storage(size_type n) {
    _start = _allocate(n);
    _finish = _start;
    _end_of_storage = _start + n;
  }
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
