#include "Intern.hpp"

Intern::Intern() {
  formTypes[0] = &Intern::makeRobotomyRequestForm;
  formTypes[1] = &Intern::makePresidentialPardonForm;
  formTypes[2] = &Intern::makeShrubberyCreationForm;
}

Intern::~Intern() {}

Intern::Intern(Intern const &other) { *this = other; }

Intern &Intern::operator=(Intern const &other) {
  if (this != &other) {
    (void)other;
  }
  return *this;
}

AForm *Intern::makeRobotomyRequestForm(std::string const &target) {
  return new RobotomyRequestForm(target);
}

AForm *Intern::makePresidentialPardonForm(std::string const &target) {
  return new PresidentialPardonForm(target);
}

AForm *Intern::makeShrubberyCreationForm(std::string const &target) {
  return new ShrubberyCreationForm(target);
}

AForm *Intern::makeForm(std::string const &formName,
                        std::string const &target) {
  int formType = ((formName == "robotomy request") * 1) +
                 ((formName == "presidential pardon") * 2) +
                 ((formName == "shrubbery creation") * 3);

  if (formType == 0) {
    std::cout << "Intern can't create " << formName << " form" << std::endl;
    return NULL;
  } else {
    std::cout << "Intern creates " << formName << " form" << std::endl;
    return (this->*formTypes[formType - 1])(target);
  }
}
