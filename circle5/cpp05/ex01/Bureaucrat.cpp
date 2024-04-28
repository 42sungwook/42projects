#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string const &name, int grade) : _name(name) {
  if (grade < 1)
    throw Bureaucrat::GradeTooHighException();
  else if (grade > 150)
    throw Bureaucrat::GradeTooLowException();
  else
    _grade = grade;
}

Bureaucrat::Bureaucrat(Bureaucrat const &other)
    : _name(other._name), _grade(other._grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat &Bureaucrat::operator=(Bureaucrat const &other) {
  if (this != &other) _grade = other._grade;
  return *this;
}

std::string Bureaucrat::getName() const { return _name; }

int Bureaucrat::getGrade() const { return _grade; }

void Bureaucrat::incrementGrade() {
  if (_grade - 1 < 1)
    throw Bureaucrat::GradeTooHighException();
  else
    _grade--;
}

void Bureaucrat::decrementGrade() {
  if (_grade + 1 > 150)
    throw Bureaucrat::GradeTooLowException();
  else
    _grade++;
}

void Bureaucrat::signForm(Form &form) {
  try {
    form.beSigned(*this);
    std::cout << _name << " signs " << form.getName() << std::endl;
  } catch (std::exception &e) {
    std::cout << _name << " cannot sign " << form.getName() << " because "
              << e.what() << std::endl;
  }
}

const char *Bureaucrat::GradeTooHighException::what() const throw() {
  return "Grade too high";
}

const char *Bureaucrat::GradeTooLowException::what() const throw() {
  return "Grade too low";
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &bureaucrat) {
  out << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
  return out;
}
