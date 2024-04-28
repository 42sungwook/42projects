#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
 private:
  std::string _target;

 public:
  PresidentialPardonForm(std::string target);
  ~PresidentialPardonForm();

  void action(Bureaucrat const &executor) const;
};

#endif
