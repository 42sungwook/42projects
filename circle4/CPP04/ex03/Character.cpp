#include "Character.hpp"

Character::Character(std::string const& name) : _name(name), _inventory() {}

Character::Character(Character const& object) { *this = object; }

Character::~Character() {
  for (int i = 0; i < 4; i++) {
    delete _inventory[i];
    _inventory[i] = NULL;
  }
}

Character& Character::operator=(Character const& object) {
  if (this != &object) {
    _name = object._name;
    for (int i = 0; i < 4; i++) {
      delete _inventory[i];
      _inventory[i] = object._inventory[i]->clone();
    }
  }

  return *this;
}

std::string const& Character::getName() const { return _name; }

void Character::equip(AMateria* m) {
  if (m == NULL) {
    std::cout << "Materia is NULL" << std::endl;
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (_inventory[i] == NULL) {
      std::cout << _name << " equipped " << m->getType() << std::endl;
      _inventory[i] = m;
      break;
    }
  }
}

void Character::unequip(int idx) {
  if (_inventory[idx] == NULL) {
    std::cout << "Nothing to unequip" << std::endl;
    return;
  }

  std::cout << _name << " unequipped " << _inventory[idx]->getType()
            << std::endl;
  delete _inventory[idx];
  _inventory[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
  if (_inventory[idx] == NULL) {
    std::cout << "Nothing to use" << std::endl;
    return;
  }

  _inventory[idx]->use(target);
}
