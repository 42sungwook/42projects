#include <iostream>

class Bureaucrat {
 private:
  const std::string _name;
  int _grade;

 public:
  Bureaucrat(std::string const &name, int grade);
  Bureaucrat(Bureaucrat const &other);
  ~Bureaucrat();
  Bureaucrat &operator=(Bureaucrat const &other);

  std::string getName() const;
  int getGrade() const;

  void incrementGrade();
  void decrementGrade();

  class GradeTooHighException : public std::exception {
   public:
    virtual const char *what() const throw();
  };
  class GradeTooLowException : public std::exception {
   public:
    virtual const char *what() const throw();
  };
};

std::ostream &operator<<(std::ostream &out, Bureaucrat const &bureaucrat);