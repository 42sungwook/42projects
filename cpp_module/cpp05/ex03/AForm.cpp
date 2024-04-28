#include "AForm.hpp"

AForm::AForm(std::string const &name, int gradeReqToSign, int gradeReqToExec)
    : _name(name),
      _signed(false),
      _gradeReqToSign(gradeReqToSign),
      _gradeReqToExec(gradeReqToExec) {
  if (gradeReqToSign < 1 || gradeReqToExec < 1)
    throw AForm::GradeTooHighException();
  else if (gradeReqToSign > 150 || gradeReqToExec > 150)
    throw AForm::GradeTooLowException();
}

AForm::AForm(AForm const &other)
    : _name(other._name),
      _signed(other._signed),
      _gradeReqToSign(other._gradeReqToSign),
      _gradeReqToExec(other._gradeReqToExec) {}

AForm::~AForm() {}

AForm &AForm::operator=(AForm const &other) {
  if (this != &other) _signed = other._signed;
  return *this;
}

std::string AForm::getName() const { return _name; }

bool AForm::getSigned() const { return _signed; }

int AForm::getGradeReqToSign() const { return _gradeReqToSign; }

int AForm::getGradeReqToExec() const { return _gradeReqToExec; }

void AForm::beSigned(Bureaucrat const &bureaucrat) {
  if (bureaucrat.getGrade() > _gradeReqToSign)
    throw AForm::GradeTooLowException();
  else
    _signed = true;
}

void AForm::execute(Bureaucrat const &executor) const {
  if (_signed == false)
    throw AForm::FormNotSignedException();
  else if (executor.getGrade() > _gradeReqToExec)
    throw AForm::GradeTooLowException();
}

const char *AForm::GradeTooLowException::what() const throw() {
  return "Grade too low";
}

const char *AForm::GradeTooHighException::what() const throw() {
  return "Grade too high";
}

const char *AForm::FormNotSignedException::what() const throw() {
  return "Form not signed";
}

std::ostream &operator<<(std::ostream &out, AForm const &AForm) {
  out << "AForm name: " << AForm.getName()
      << "\nAForm grade required to sign: " << AForm.getGradeReqToSign()
      << "\nAForm grade required to execute: " << AForm.getGradeReqToExec()
      << "\nAForm is ";
  if (AForm.getSigned())
    out << "signed";
  else
    out << "not signed";
  return out;
}