#include "Array.hpp"
#include "Utils.hpp"

#include <fmt/format.h>

#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

size_t getSize();
template <typename T> Array<T> createArray();
template <typename T> std::unique_ptr<T[]> allocateArray(size_t);
template <typename Out, typename T> Out calculateMean(T *, size_t, Out);
template <typename InputIterator, typename T>
T calculateMean(InputIterator, InputIterator, T);

int main() {
  auto array = createArray<int>();

  // Read data
  for (size_t i = 0; i < array.size();) {
    std::stringstream ss;
    ss << "Element " << i + 1 << ": ";
    std::optional<double> data = Project6::parseDouble(Project6::prompt(ss.str()));
    if (data) {
      array[i] = *data;
      i++;
    } else {
      std::cerr << "Invalid input" << std::endl;
    }
  }

  // Calculate mean
  double mean = calculateMean(array.data(), array.size(), 0.0);
  // double mean = calculateMean(array.begin(), array.end(), 0.0);

  // Print mean
  std::cout << fmt::format("Mean: {}", mean) << std::endl;
}

/**
 * @brief Get array size from user
 * 
 * @return Size 
 */
size_t getSize() {
  std::function<size_t(void)> tryGetSize = [&tryGetSize]() {
    std::optional<size_t> size =
        Project6::parseSizeSigned(Project6::prompt("Array size: "));
    if (size && *size > 0) {
      return *size;
    } else {
      std::cout << "Invalid array size" << std::endl;
      return tryGetSize();
    }
  };
  return tryGetSize();
}

/**
 * @brief Get size from user and create array object
 * 
 * @tparam T 
 * @return Array<T> 
 */
template <typename T> Array<T> createArray() {
  std::function<std::unique_ptr<T[]>(size_t)> tryCreate =
      [&tryCreate](size_t size) {
        std::unique_ptr<T[]> array = allocateArray<T>(size);
        if (array) {
          return std::move(array);
        } else {
          std::cerr << "Unable to allocate array" << std::endl;
        }
        return tryCreate(size);
      };

  size_t size = getSize();
  auto array = tryCreate(size);
  return Array<T>(std::move(array), size);
}

/**
 * @brief Allocate memory for array
 *
 * @tparam T data type
 * @param size number of elements
 * @return Pointer to memory or empty if allocation failed
 */
template <typename T> std::unique_ptr<T[]> allocateArray(size_t size) {
  try {
    return std::unique_ptr<T[]>(new T[size]);
  } catch (const std::bad_alloc &) {
    return std::unique_ptr<T[]>();
  }
}

/**
 * @brief Calculate mean of dynamic array
 *
 * @tparam Out Return type
 * @tparam In Array element type
 * @param array Pointer to data
 * @param size Size of array
 * @param init Initial summation value
 * @return Mean
 */
template <typename Out, typename In>
Out calculateMean(In *array, size_t size, Out init) {
  if (size < 1) {
    return init;
  }

  Out sum = init;
  for (size_t i = 0; i < size; i++) {
    sum += *(array++);
  }
  return static_cast<Out>(sum / static_cast<double>(size));
}

/**
 * @brief Calculate mean of range
 *
 * @tparam InputIterator Iterator type
 * @tparam T Return type
 * @param begin Start iterator
 * @param end End iterator
 * @param init Initial summation value
 * @return Mean
 */
template <typename InputIterator, typename T>
T calculateMean(InputIterator begin, InputIterator end, T init) {
  size_t size = end - begin;

  if (size < 1) {
    return init;
  }

  return static_cast<T>(std::accumulate(begin, end, init) /
                        static_cast<double>(size));
}
