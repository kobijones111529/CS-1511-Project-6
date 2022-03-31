#pragma once

#include <memory>

/**
 * @brief Rudimentary custom array container
 *
 * @tparam T Value type
 */
template <typename T> struct Array {
public:
  struct Iterator {
    Iterator(T *ptr) : m_ptr(ptr) {}

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    Iterator &operator++() {
      m_ptr++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_ptr != b.m_ptr;
    }
    friend Iterator operator+(const Iterator &left, const size_t &right) {
      return Iterator(left.m_ptr + right);
    }
    friend Iterator operator-(const Iterator &left, const size_t &right) {
      return Iterator(left.m_ptr + right);
    }
    friend size_t operator-(const Iterator &left, const Iterator &right) {
      return left.m_ptr - right.m_ptr;
    }

  private:
    T *m_ptr;
  };

  Array(std::shared_ptr<T[]> _data, size_t _size)
      : m_data(_data), m_size(_size) {}
  Array(Array &&other) noexcept : m_data(nullptr), m_size(0) {
    *this = std::move(other);
  }
  Array &operator=(Array &&other) noexcept {
    if (this != &other) {
      data = std::move(other.data);
      m_size = std::move(other.m_size);
    }
    return *this;
  }
  T &operator[](size_t i) { return m_data[i]; }

  T *data() const { return m_data.get(); }
  size_t size() const { return m_size; }

  Iterator begin() { return Iterator(m_data.get()); }
  Iterator end() { return Iterator(m_data.get() + m_size); }

private:
  std::shared_ptr<T[]> m_data;
  size_t m_size;
};