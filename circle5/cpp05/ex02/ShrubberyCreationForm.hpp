#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include <fstream>

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {
 private:
  std::string _target;

 public:
  ShrubberyCreationForm(std::string target);
  ~ShrubberyCreationForm();

  void action(Bureaucrat const &executor) const;
};

#endif
