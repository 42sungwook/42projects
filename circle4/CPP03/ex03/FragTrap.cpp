#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
  _name = ClapTrap::_name;
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
  std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string name) : ClapTrap(name) {
  _name = ClapTrap::_name;
  _hitPoints = 100;
  _energyPoints = 100;
  _attackDamage = 30;
  std::cout << "FragTrap name constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &object) {
  std::cout << "FragTrap copy constructor called" << std::endl;
  *this = object;
}

FragTrap &FragTrap::operator=(FragTrap &object) {
  std::cout << "FragTrap copy assignment operator called" << std::endl;
  _name = object._name;
  _hitPoints = object._hitPoints;
  _energyPoints = object._energyPoints;
  _attackDamage = object._attackDamage;
  return *this;
}

FragTrap::~FragTrap() {
  std::cout << "FragTrap destructor called" << std::endl;
}

void FragTrap::highFivesGuys() {
  std::cout << "FragTrap " << _name << " wants to high five!" << std::endl;
  _energyPoints--;
}

void FragTrap::attack(const std::string &target) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "FragTrap" << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "FragTrap " << _name << " attacks " << target << ", causing "
            << _attackDamage << " points of damage!" << std::endl;
  _energyPoints--;
}
