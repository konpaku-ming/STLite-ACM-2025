#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template <typename T> class vector {
public:
  T **vector_data = nullptr;
  size_t vector_size = 0;
  size_t vector_capacity = 0;

  class const_iterator;

  class iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::output_iterator_tag;

    T **ptr = nullptr;

    iterator() = default;

    iterator(const iterator &other) { ptr = other.ptr; }

    iterator operator+(const int &n) const {
      iterator temp(*this);
      temp.ptr += n;
      return temp;
    }

    iterator operator-(const int &n) const {
      iterator temp(*this);
      temp.ptr -= n;
      return temp;
    }

    int operator-(const iterator &rhs) const {
      const int num = ptr - rhs.ptr;
      return num;
    }

    iterator &operator+=(const int &n) {
      ptr += n;
      return *this;
    }

    iterator &operator-=(const int &n) {
      ptr -= n;
      return *this;
    }

    iterator operator++(int) {
      iterator temp(*this);
      ++ptr;
      return temp;
    }

    iterator &operator++() {
      ++ptr;
      return *this;
    }

    iterator operator--(int) {
      iterator temp(*this);
      --ptr;
      return temp;
    }

    iterator &operator--() {
      --ptr;
      return *this;
    }

    T &operator*() const { return **ptr; }

    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator==(const const_iterator &rhs) const {
      return ptr == rhs.c_ptr;
    }

    bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }

    bool operator!=(const const_iterator &rhs) const {
      return ptr != rhs.c_ptr;
    }
  };

  class const_iterator {
  public:
    friend iterator;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::output_iterator_tag;

    T **c_ptr = nullptr;

    const_iterator() = default;

    const_iterator(const const_iterator &other) { c_ptr = other.c_ptr; }

    const_iterator operator+(const int &n) const {
      c_ptr += n;
      const_iterator temp(*this);
      return temp;
    }

    const_iterator operator-(const int &n) const {
      c_ptr -= n;
      const_iterator temp(*this);
      return temp;
    }

    int operator-(const const_iterator &rhs) const {
      const int num = c_ptr - rhs.c_ptr;
      return num;
    }

    const_iterator &operator+=(const int &n) {
      c_ptr += n;
      return *this;
    }

    const_iterator &operator-=(const int &n) {
      c_ptr -= n;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator temp(*this);
      ++c_ptr;
      return temp;
    }

    const_iterator &operator++() {
      ++c_ptr;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator temp(*this);
      --c_ptr;
      return temp;
    }

    const_iterator &operator--() {
      --c_ptr;
      return *this;
    }

    const T &operator*() const { return **c_ptr; }

    bool operator==(const iterator &rhs) const { return c_ptr == rhs.ptr; }

    bool operator==(const const_iterator &rhs) const {
      return c_ptr == rhs.c_ptr;
    }

    bool operator!=(const iterator &rhs) const { return c_ptr != rhs.ptr; }

    bool operator!=(const const_iterator &rhs) const {
      return c_ptr != rhs.c_ptr;
    }
  };

public:
  vector() {
    vector_data = nullptr;
    vector_size = 0;
    vector_capacity = 0;
  }

  vector(const vector &other) {
    vector_capacity = other.vector_capacity;
    vector_size = other.vector_size;
    vector_data = new T *[vector_capacity] { nullptr };
    for (size_t i = 0; i < vector_size; i++) {
      vector_data[i] = new T(*other.vector_data[i]);
    }
  }

  ~vector() {
    for (size_t i = 0; i < vector_size; i++) {
      delete vector_data[i];
      vector_data[i] = nullptr;
    }
    delete[] vector_data;
  }

  vector &operator=(const vector &other) {
    if (other.vector_data == vector_data) {
      return *this;
    }
    vector_capacity = other.vector_capacity;
    vector_size = other.vector_size;
    vector_data = new T *[vector_capacity] { nullptr };
    for (int i = 0; i < vector_size; i++) {
      vector_data[i] = new T(*other.vector_data[i]);
    }
    return *this;
  }

  /**
   * assigns specified element with bounds checking
   * throw index_out_of_bound if pos is not in [0, size)
   */
  T &at(const size_t &pos) {
    if (pos >= vector_size) {
      throw index_out_of_bound();
    }
    return *vector_data[pos];
  }

  const T &at(const size_t &pos) const {
    if (pos >= vector_size) {
      throw index_out_of_bound();
    }
    const T res = *vector_data[pos];
    return res;
  }

  T &operator[](const size_t &pos) {
    if (pos >= vector_size) {
      throw index_out_of_bound();
    }
    return *vector_data[pos];
  }

  const T &operator[](const size_t &pos) const {
    if (pos >= vector_size) {
      throw index_out_of_bound();
    }
    return *vector_data[pos];
  }

  const T &front() const { return *vector_data[0]; }

  const T &back() const { return *vector_data[vector_size - 1]; }

  /**
   * returns an iterator to the beginning.
   */
  iterator begin() {
    iterator begin_it;
    begin_it.ptr = vector_data;
    return begin_it;
  }

  const_iterator begin() const {
    const_iterator begin_it;
    begin_it.c_ptr = vector_data;
    return begin_it;
  }

  const_iterator cbegin() const {
    const_iterator cbegin_it;
    cbegin_it.c_ptr = vector_data;
    return cbegin_it;
  }

  iterator end() {
    iterator end_it;
    end_it.ptr = vector_data + vector_size;
    return end_it;
  }

  const_iterator end() const {
    const_iterator end_it;
    end_it.c_ptr = vector_data + vector_size;
    return end_it;
  }

  const_iterator cend() const {
    const_iterator end_it;
    end_it.c_ptr = vector_data + vector_size;
    return end_it;
  }

  /**
   * checks whether the container is empty
   */
  bool empty() const { return vector_size == 0; }

  /**
   * returns the number of elements
   */
  size_t size() const { return vector_size; }

private:
  void doubleSpace() {
    vector_capacity = (vector_capacity + 1) * 2;
    T **new_data = new T *[vector_capacity] { nullptr };
    for (size_t i = 0; i < vector_size; i++) {
      new_data[i] = vector_data[i];
    }
    delete[] vector_data;
    vector_data = new_data;
  }

public:
  void clear() {
    for (int i = 0; i < vector_size; i++) {
      delete vector_data[i];
      vector_data[i] = nullptr;
    }
    vector_size = 0;
  }

  /**
   * inserts value before pos
   * returns an iterator pointing to the inserted value.
   */
  iterator insert(iterator pos, const T &value) {
    if (vector_size == vector_capacity) {
      doubleSpace();
    }
    vector_data[vector_size] = new T(value);
    vector_size++;
    iterator it = end();
    --it;
    while (it != pos) {
      *it = *(it - 1);
      --it;
    }
    iterator temp(pos);
    ++pos;
    *temp = value;
    return temp;
  }

  /**
   * inserts value at index ind.
   * after inserting, this->at(ind) == value
   * returns an iterator pointing to the inserted value.
   * throw index_out_of_bound if ind > size (in this situation ind can be size
   * because after inserting the size will increase 1.)
   */
  iterator insert(const size_t &ind, const T &value) {
    if (ind > vector_size) {
      throw index_out_of_bound();
    }
    if (vector_size == vector_capacity) {
      doubleSpace();
    }
    vector_data[vector_size] = new T(value);
    vector_size++;
    size_t i = vector_size - 1;
    while (i != ind) {
      *vector_data[i] = *vector_data[i - 1];
      i--;
    }
    *vector_data[ind] = value;
    iterator temp;
    temp.ptr = vector_data + ind;
    return temp;
  }

  /**
   * removes the element at pos.
   * return an iterator pointing to the following element.
   * If the iterator pos refers the last element, the end() iterator is
   * returned.
   */
  iterator erase(iterator pos) {
    iterator it(pos);
    ++it;
    while (it != end()) {
      *(it - 1) = *it;
      ++it;
    }
    vector_size--;
    delete vector_data[vector_size];
    vector_data[vector_size] = nullptr;
    iterator temp(pos);
    ++temp;
    return temp;
  }

  /**
   * removes the element with index ind.
   * return an iterator pointing to the following element.
   * throw index_out_of_bound if ind >= size
   */
  iterator erase(const size_t &ind) {
    if (ind >= vector_size) {
      throw index_out_of_bound();
    }
    vector_size--;
    size_t i = ind;
    while (i != vector_size) {
      *vector_data[i] = *vector_data[i + 1];
      i++;
    }
    delete vector_data[vector_size];
    iterator temp;
    temp.ptr = vector_data + ind + 1;
    return temp;
  }

  /**
   * adds an element to the end.
   */
  void push_back(const T &value) {
    if (vector_size < vector_capacity) {
      vector_data[vector_size] = new T(value);
      vector_size++;
      return;
    }
    doubleSpace();
    vector_data[vector_size] = new T(value);
    vector_size++;
  }

  /**
   * remove the last element from the end.
   * throw container_is_empty if size() == 0
   */
  void pop_back() {
    if (empty()) {
      throw container_is_empty();
    } else {
      delete vector_data[vector_size - 1];
      vector_data[vector_size - 1] = nullptr;
      vector_size--;
    }
  }
};
} // namespace sjtu

#endif
