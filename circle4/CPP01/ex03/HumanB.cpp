#include "HumanB.hpp"

HumanB::HumanB(const std::string &name) : _name(name) { _weapon = NULL; }

void HumanB::attack(void) const {
  if (!_weapon) {
    std::cout << _name << " has no weapon" << std::endl;
    return;
  }
  std::cout << _name << " attacks with his " << _weapon->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &weapon) { _weapon = &weapon; }
