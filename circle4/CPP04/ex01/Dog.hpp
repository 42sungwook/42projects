#ifndef DOG_HPP
#define DOG_HPP

#include <iostream>

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
 private:
  Brain *_brain;

 public:
  Dog();
  Dog(const Dog &copy);
  virtual ~Dog();
  Dog &operator=(const Dog &copy);
  Brain *accessBrain(void);

  virtual void makeSound() const;
};

#endif
