#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main() {
  Intern someRandomIntern;
  AForm *rrf;
  AForm *scf;
  AForm *ppf;
  AForm *unknown;

  rrf = someRandomIntern.makeForm("robotomy request", "Bender");
  scf = someRandomIntern.makeForm("shrubbery creation", "Bender");
  ppf = someRandomIntern.makeForm("presidential pardon", "Bender");
  unknown = someRandomIntern.makeForm("unknown", "Bender");

  std::cout << std::endl;

  Bureaucrat bender("Bender", 1);

  bender.signForm(*rrf);
  bender.executeForm(*rrf);

  std::cout << std::endl;

  bender.signForm(*scf);
  bender.executeForm(*scf);

  std::cout << std::endl;

  bender.signForm(*ppf);
  bender.executeForm(*ppf);

  std::cout << std::endl;

  delete rrf;
  delete scf;
  delete ppf;

  return 0;
}