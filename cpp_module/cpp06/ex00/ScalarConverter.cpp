#include "ScalarConverter.hpp"

// ref: https://en.cppreference.com/w/cpp/string/byte/strtof

void ScalarConverter::convert(std::string input) {
  // float형 예외 (가장 뒷 자리에 f가 있을 때)
  if (input.length() > 1 && input[input.length() - 1] == 'f') {
    input = input.substr(0, input.length() - 1);
  }

  // Convert using stdtod
  char *str_end;
  double value = std::strtod(input.c_str(), &str_end);
  // str_end string 타입으로 변환
  std::string str_end_str(str_end);
  // str_end가 빈 문자열이 아니고, 길이가 1보다 클 때
  if (*str_end != '\0' && str_end_str.length() > 1) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: nanf" << std::endl;
    std::cout << "double: nan" << std::endl;
    return;
  }
  // 숫자 + string 조합일 때
  else if (value != 0 && str_end_str.length() > 0) {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: nanf" << std::endl;
    std::cout << "double: nan" << std::endl;
    return;
  }
  // char형일 때
  else if (value == 0 && str_end_str.length() == 1) {
    value = str_end[0];
  }

  // Convert to char
  char charValue = static_cast<char>(value);
  if (value >= -128 && value <= 127) {
    if (std::isprint(charValue)) {
      std::cout << "char: '" << charValue << "'" << std::endl;
    } else {
      std::cout << "char: Non displayable" << std::endl;
    }
  } else {
    std::cout << "char: impossible" << std::endl;
  }

  // Convert to int
  int intValue = static_cast<int>(value);
  if (value >= INT_MIN && value <= INT_MAX) {
    std::cout << "int: " << intValue << std::endl;
  } else {
    std::cout << "int: impossible" << std::endl;
  }

  // Convert to float
  float floatValue = static_cast<float>(value);
  if (std::isnan(floatValue)) {
    std::cout << "float: nanf" << std::endl;
  } else if (std::isinf(floatValue)) {
    if (floatValue > 0)
      std::cout << "float: +inff" << std::endl;
    else
      std::cout << "float: -inff" << std::endl;
  } else {
    std::cout << "float: " << std::setprecision(1) << std::fixed << floatValue
              << "f" << std::endl;
  }

  // Convert to double
  double doubleValue = value;
  if (std::isnan(doubleValue)) {
    std::cout << "double: nan" << std::endl;
  } else if (std::isinf(doubleValue)) {
    if (doubleValue > 0)
      std::cout << "double: +inf" << std::endl;
    else
      std::cout << "double: -inf" << std::endl;
  } else {
    std::cout << "double: " << std::setprecision(1) << std::fixed << doubleValue
              << std::endl;
  }
}
