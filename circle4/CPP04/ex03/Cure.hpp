#ifndef CURE_HPP
#define CURE_HPP

#include <iostream>

#include "AMateria.hpp"

class Cure : public AMateria {
 public:
  Cure();
  Cure(Cure const& object);
  virtual ~Cure();
  Cure& operator=(Cure const& object);

  virtual AMateria* clone() const;
  virtual void use(ICharacter& target);
};

#endif
