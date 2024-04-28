#include "Cure.hpp"

Cure::Cure() : AMateria("cure") {}

Cure::Cure(Cure const& object) : AMateria(object) {}

Cure::~Cure() {}

Cure& Cure::operator=(Cure const& object) {
  if (this != &object) {
    AMateria::operator=(object);
  }

  return *this;
}

AMateria* Cure::clone() const { return new Cure(*this); }

void Cure::use(ICharacter& target) {
  std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
