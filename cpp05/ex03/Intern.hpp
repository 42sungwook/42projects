#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern {
 private:
  static const int FORM_COUNT = 3;
  typedef AForm *(Intern::*FormType)(const std::string &);
  FormType formTypes[FORM_COUNT];

 public:
  Intern();
  ~Intern();

  Intern(Intern const &other);
  Intern &operator=(Intern const &other);

  AForm *makeRobotomyRequestForm(std::string const &target);
  AForm *makePresidentialPardonForm(std::string const &target);
  AForm *makeShrubberyCreationForm(std::string const &target);
  AForm *makeForm(std::string const &formName, std::string const &target);
};

#endif
