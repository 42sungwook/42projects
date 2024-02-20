#include "Function.hpp"

void print(int const &i) { std::cout << i << std::endl; }

void print(char const &c) { std::cout << c << std::endl; }

void print(double const &d) { std::cout << d << std::endl; }

int main() {
  std::cout << "===== Int 배열 =====" << std::endl;
  int intArray[] = {1, 2, 3, 4, 5};
  iter(intArray, 5, print);

  std::cout << "===== Char 배열 =====" << std::endl;
  char charArray[] = {'a', 'b', 'c', 'd', 'e'};
  iter(charArray, 5, print);

  std::cout << "===== Double 배열 =====" << std::endl;
  double doubleArray[] = {1.1, 2.2, 3.3, 4.4, 5.5};
  iter(doubleArray, 5, print);
  return 0;
}