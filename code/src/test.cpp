#include <iostream>

#include "../includes/Utils.hpp"

int main() {
  std::cout << "1m: " << convertByteUnits("1m") << std::endl;
  std::cout << "300K: " << convertByteUnits("300K") << std::endl;
  std::cout << "20: " << convertByteUnits("20") << std::endl;
  std::cout << "20g: " << convertByteUnits("20g") << std::endl;
  std::cout << "2: " << convertTimeUnits("2") << std::endl;
  std::cout << "2s: " << convertTimeUnits("2s") << std::endl;
  std::cout << "1s 1m: " << convertTimeUnits("1s 1m") << std::endl;
}