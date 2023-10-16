#include "Form.hpp"

Form::Form(std::string const &name, int gradeReqToSign, int gradeReqToExec)
    : _name(name),
      _signed(false),
      _gradeReqToSign(gradeReqToSign),
      _gradeReqToExec(gradeReqToExec) {
  if (gradeReqToSign < 1 || gradeReqToExec < 1)
    throw Form::GradeTooHighException();
  else if (gradeReqToSign > 150 || gradeReqToExec > 150)
    throw Form::GradeTooLowException();
}

Form::Form(Form const &other)
    : _name(other._name),
      _signed(other._signed),
      _gradeReqToSign(other._gradeReqToSign),
      _gradeReqToExec(other._gradeReqToExec) {}

Form::~Form() {}

Form &Form::operator=(Form const &other) {
  if (this != &other) _signed = other._signed;
  return *this;
}

std::string Form::getName() const { return _name; }

bool Form::getSigned() const { return _signed; }

int Form::getGradeReqToSign() const { return _gradeReqToSign; }

int Form::getGradeReqToExec() const { return _gradeReqToExec; }

void Form::beSigned(Bureaucrat const &bureaucrat) {
  if (bureaucrat.getGrade() > _gradeReqToSign)
    throw Form::GradeTooLowException();
  else
    _signed = true;
}

const char *Form::GradeTooLowException::what() const throw() {
  return "Grade too low";
}

std::ostream &operator<<(std::ostream &out, Form const &form) {
  out << "form name: " << form.getName()
      << "\nform grade required to sign: " << form.getGradeReqToSign()
      << "\nform grade required to execute: " << form.getGradeReqToExec()
      << "\nform is ";
  if (form.getSigned())
    out << "signed";
  else
    out << "not signed";
  return out;
}
