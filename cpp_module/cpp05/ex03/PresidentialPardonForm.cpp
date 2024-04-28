#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target)
    : AForm("PresidentialPardonForm", 25, 5), _target(target){};

PresidentialPardonForm::~PresidentialPardonForm(){};

void PresidentialPardonForm::action(Bureaucrat const &executor) const {
  AForm::execute(executor);
  std::cout << this->_target << " has been pardoned by Zafod Beeblebrox."
            << std::endl;
}