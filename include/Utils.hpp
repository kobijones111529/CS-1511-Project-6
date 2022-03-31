#pragma once

#include <functional>
#include <iostream>
#include <limits>
#include <optional>
#include <string>

namespace Project6 {

/**
 * @brief String conversion wrapper that only succeeds if the entire string was
 * read
 *
 * @tparam T Result type
 * @param str String to convert
 * @param convert Base convert function
 * @param idx Set to total characters read if not null
 * @return Converted value
 */
template <typename T>
T strict_conversion(
    const std::string &str,
    const std::function<T(const std::string &, size_t *)> convert,
    size_t *idx = nullptr) {
  size_t read;
  T value = convert(str, &read);
  if (read == str.size()) {
    if (idx != nullptr) {
      *idx = read;
    }
    return value;
  } else {
    throw std::invalid_argument("strict_conversion: no conversion");
  }
}

/**
 * @brief String conversion wrapper that only succeeds if the entire string was
 * read
 *
 * @tparam T Result type
 * @param str String to convert
 * @param convert Base convert function
 * @param idx Set to total characters read if not null
 * @return Converted value
 */
template <typename T>
T strict_conversion(
    const std::wstring &str,
    const std::function<T(const std::wstring &, size_t *)> convert,
    size_t *idx = nullptr) {
  size_t read;
  T value = convert(str, &read);
  if (read == str.size()) {
    if (idx != nullptr) {
      *idx = read;
    }
    return value;
  } else {
    throw std::invalid_argument("strict_conversion: no conversion");
  }
}

/**
 * @brief Converts string to size_t on current system
 *
 * @param str String to convert
 * @param idx Set to total characters read if not null
 * @return Converted value
 */
size_t stosz(const std::string &str, size_t *idx = nullptr) {
  size_t read;
  unsigned long long value = std::stoull(str, &read);
  if (value > std::numeric_limits<size_t>::max()) {
    throw std::out_of_range("stosz: no conversion");
  } else {
    if (idx != nullptr) {
      *idx = read;
    }
    return static_cast<size_t>(value);
  }
}

/**
 * @brief Converts string to size_t on current system, fails instead of wrapping
 * negative values
 *
 * @param str String to convert
 * @param idx Set to total characters read if not null
 * @return Converted value
 */
size_t stosz_signed(const std::string &str, size_t *idx = nullptr) {
  size_t read;
  long long value = std::stoll(str, &read);
  if (value > std::numeric_limits<size_t>::max() || value < 0) {
    throw std::out_of_range("stosz_signed: no conversion");
  } else {
    if (idx != nullptr) {
      *idx = read;
    }
    return static_cast<size_t>(value);
  }
}

/**
 * @brief Prompt user for input
 *
 * @param msg Message to prompt with
 * @return User input
 */
std::string prompt(const std::string &msg) {
  std::string input;
  std::cout << msg;
  std::getline(std::cin, input);
  return input;
}

/**
 * @brief Parse string to double
 *
 * @param str String to parse
 * @return Value or empty
 */
std::optional<double> parseDouble(const std::string &str, bool strict = true) {
  try {
    const auto convert = [](const std::string &str, size_t *idx = nullptr) {
      return std::stod(str, idx);
    };
    double value =
        strict ? strict_conversion<double>(str, convert) : convert(str);
    return std::optional(value);
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {
  }
  return std::nullopt;
}

/**
 * @brief Parse string to int
 *
 * @param str String to parse
 * @return Value or empty
 */
std::optional<int> parseInt(const std::string &str, bool strict = true) {
  const auto convert = [](const std::string &str, size_t *idx = nullptr) {
    return std::stoi(str, idx);
  };
  try {
    int value = strict ? strict_conversion<int>(str, convert) : convert(str);
    return std::optional(value);
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {
  }
  return std::nullopt;
}

/**
 * @brief Parse long long
 *
 * @param str String to parse
 * @param strict Only succeed if all characters read
 * @return Value or empty
 */
std::optional<long long> parseLongLong(const std::string &str,
                                       bool strict = true) {
  const auto convert = [](const std::string &str, size_t *idx = nullptr) {
    return std::stoll(str, idx);
  };
  try {
    long long value =
        strict ? strict_conversion<long long>(str, convert) : convert(str);
    return value;
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {
  }
  return std::nullopt;
}

std::optional<size_t> parseSize(const std::string &str, bool strict = true) {
  const auto convert = [](const std::string &str, size_t *idx = nullptr) {
    return stosz(str, idx);
  };
  try {
    size_t value =
        strict ? strict_conversion<size_t>(str, convert) : convert(str);
    return std::optional(value);
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {
  }
  return std::nullopt;
}

std::optional<size_t> parseSizeSigned(const std::string &str,
                                      bool strict = true) {
  const auto convert = [](const std::string &str, size_t *idx = nullptr) {
    return stosz_signed(str, idx);
  };
  try {
    size_t value =
        strict ? strict_conversion<size_t>(str, convert) : convert(str);
    return std::optional(value);
  } catch (const std::invalid_argument &) {
  } catch (const std::out_of_range &) {
  }
  return std::nullopt;
}

} // namespace Project6