#include "AMateria.hpp"

AMateria::AMateria(std::string const& type) : _type(type) {}

AMateria::AMateria(AMateria const& object) { *this = object; }

AMateria::~AMateria() {}

AMateria& AMateria::operator=(AMateria const& object) {
  if (this != &object) {
    _type = object._type;
  }
  return *this;
}

std::string const& AMateria::getType() const { return _type; }

void AMateria::use(ICharacter& target) {
  std::cout << "* Materia has no effect on " << target.getName() << "*"
            << std::endl;
}
