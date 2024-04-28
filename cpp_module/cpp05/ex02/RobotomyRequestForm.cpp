#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string target)
    : AForm("RobotomyRequestForm", 72, 45), _target(target) {
  srand(time(NULL));
};

RobotomyRequestForm::~RobotomyRequestForm(){};

void RobotomyRequestForm::action(Bureaucrat const &executor) const {
  AForm::execute(executor);
  std::cout << "* drilling noises *" << std::endl;

  if (rand() % 2 == 0)
    std::cout << this->_target << " has been robotomized successfully 🥳"
              << std::endl;
  else
    std::cout << "Robotomy failed 🤯" << std::endl;
}