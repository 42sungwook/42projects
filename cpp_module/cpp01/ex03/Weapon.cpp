#include "Weapon.hpp"

Weapon::Weapon() {}

Weapon::~Weapon() {}

Weapon &Weapon::operator=(const Weapon &type) {
  _type = type._type;
  return (*this);
}

Weapon::Weapon(const std::string &type) : _type(type) {}

const std::string &Weapon::getType(void) const { return (_type); }

void Weapon::setType(std::string type) { _type = type; }

Weapon::Weapon(const Weapon &object) { *this = object; }
