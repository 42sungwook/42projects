#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
class ScalarConverter {
 public:
  static void convert(std::string input);

 private:
  ScalarConverter();
  ~ScalarConverter();
  ScalarConverter(ScalarConverter &src);
  ScalarConverter &operator=(ScalarConverter &src);
};

#endif
