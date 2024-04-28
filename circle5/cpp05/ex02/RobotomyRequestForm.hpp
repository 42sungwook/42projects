#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <time.h>

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
 private:
  std::string _target;

 public:
  RobotomyRequestForm(std::string target);
  ~RobotomyRequestForm();

  void action(Bureaucrat const &executor) const;
};

#endif
