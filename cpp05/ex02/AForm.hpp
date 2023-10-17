#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>

#include "Bureaucrat.hpp"

class Bureaucrat;
class AForm {
 private:
  const std::string _name;
  bool _signed;
  const int _gradeReqToSign;
  const int _gradeReqToExec;

 public:
  AForm(std::string const &name, int gradeReqToSign, int gradeReqToExec);
  AForm(AForm const &other);
  ~AForm();

  AForm &operator=(AForm const &other);

  std::string getName() const;
  bool getSigned() const;
  int getGradeReqToSign() const;
  int getGradeReqToExec() const;

  void beSigned(Bureaucrat const &bureaucrat);

  class GradeTooLowException : public std::exception {
   public:
    virtual const char *what() const throw();
  };

  class GradeTooHighException : public std::exception {
   public:
    virtual const char *what() const throw();
  };
};

std::ostream &operator<<(std::ostream &out, AForm const &form);

#endif
