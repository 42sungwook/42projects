#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
  try {
    Form test("Invalid Form 1", 0, 1);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    Form test("Invalid Form 2", 1, 0);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    Form test("Invalid Form 3", 151, 1);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  try {
    Form test("Invalid Form 4", 1, 151);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  Bureaucrat bureaucrat("sungwook", 1);
  Bureaucrat intern("intern", 120);
  Form form("42seoul", 1, 1);

  std::cout << bureaucrat << std::endl;
  std::cout << form << std::endl;

  bureaucrat.signForm(form);
  std::cout << form << std::endl;

  intern.signForm(form);

  return 0;
}