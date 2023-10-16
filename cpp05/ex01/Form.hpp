#include <iostream>

#include "Bureaucrat.hpp"

class Form {
 private:
  const std::string _name;
  bool _signed;
  const int _gradeReqToSign;
  const int _gradeReqToExec;

 public:
  Form(std::string const &name, int gradeReqToSign, int gradeReqToExec);
  Form(Form const &other);
  ~Form();

  Form &operator=(Form const &other);

  std::string getName() const;
  bool getSigned() const;
  int getGradeReqToSign() const;
  int getGradeReqToExec() const;

  void beSigned(Bureaucrat const &bureaucrat);

  class GradeTooLowException : public std::exception {
   public:
    virtual const char *what() const throw();
  };
};

std::ostream &operator<<(std::ostream &out, Form const &form);
