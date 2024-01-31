#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
  try {
    Bureaucrat bureaucrat("sungwook", 71);

    // reqSign: 25, reqExec: 5
    PresidentialPardonForm form1("PresidentialPardonForm");
    // reqSign: 72, reqExec: 45
    RobotomyRequestForm form2("RobotomyRequestForm");
    // reqSign: 145, reqExec: 137
    ShrubberyCreationForm form3("ShrubberyCreationForm");

    bureaucrat.executeForm(form1);
    bureaucrat.executeForm(form2);
    bureaucrat.executeForm(form3);
    std::cout << "----------------------------------------" << std::endl;

    bureaucrat.signForm(form1);
    bureaucrat.signForm(form2);
    bureaucrat.signForm(form3);

    bureaucrat.executeForm(form1);
    bureaucrat.executeForm(form2);
    bureaucrat.executeForm(form3);
    std::cout << "----------------------------------------" << std::endl;

    for (int i = 0; i < 70; i++) {
      bureaucrat.incrementGrade();
    };
    std::cout << "Bureaucrat's grade: " << bureaucrat.getGrade() << "\n"
              << std::endl;

    bureaucrat.signForm(form1);
    bureaucrat.executeForm(form1);
    bureaucrat.executeForm(form2);
    bureaucrat.executeForm(form3);
    std::cout << "----------------------------------------" << std::endl;

    form1.action(bureaucrat);
    form2.action(bureaucrat);
    form3.action(bureaucrat);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
