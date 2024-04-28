#ifndef CAT_HPP
#define CAT_HPP

#include <iostream>

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {
 private:
  Brain *_brain;

 public:
  Cat();
  Cat(const Cat &copy);
  virtual ~Cat();
  Cat &operator=(const Cat &copy);
  Brain *accessBrain(void);

  virtual void makeSound() const;
};

#endif
