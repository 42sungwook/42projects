#include "Function.hpp"

int main() {
  std::cout << "===== Int 배열 =====" << std::endl;
  int intArray[] = {1, 2, 3, 4, 5};
  iter(intArray, 5, print<const int>);

  std::cout << "===== Char 배열 =====" << std::endl;
  char charArray[] = {'a', 'b', 'c', 'd', 'e'};
  iter(charArray, 5, print<const char>);

  std::cout << "===== Double 배열 =====" << std::endl;
  double doubleArray[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  iter(doubleArray, 5, print<const double>);
  return 0;
}