#include "Array.hpp"

int main() {
  Array<int> intArray(5);
  Array<char> charArray(5);

  std::cout << intArray.size() << std::endl;
  try {
    intArray[5] = 1;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    intArray[0] = 'a';
    charArray[0] = 'a';
    std::cout << "===== Int 배열 =====" << std::endl;
    std::cout << intArray[0] << std::endl;
    std::cout << "===== Char 배열 =====" << std::endl;
    std::cout << charArray[0] << std::endl;

  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}