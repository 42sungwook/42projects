#include "Bureaucrat.hpp"

int main() {
  Bureaucrat a("sungwook", 1);

  std::cout << a << std::endl;

  try {
    a.incrementGrade();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << a << std::endl;

  try {
    a.decrementGrade();
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  std::cout << a << std::endl;

  try {
    Bureaucrat b("ex2", 151);
    std::cout << b << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    Bureaucrat c("ex3", 0);
    std::cout << c << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}