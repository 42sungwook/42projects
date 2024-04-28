#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {}

Ice::Ice(Ice const& object) : AMateria(object) {}

Ice::~Ice() {}

Ice& Ice::operator=(Ice const& object) {
  if (this != &object) {
    AMateria::operator=(object);
  }

  return *this;
}

AMateria* Ice::clone() const { return new Ice(*this); }

void Ice::use(ICharacter& target) {
  std::cout << "* shoots an ice bolt at " << target.getName() << " *"
            << std::endl;
}
