#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <stdlib.h>

#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

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
