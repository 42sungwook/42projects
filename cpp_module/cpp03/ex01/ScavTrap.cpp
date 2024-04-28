#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
  _hitPoints = 100;
  _energyPoints = 50;
  _attackDamage = 20;
  std::cout << "ScavTrap name constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &object) {
  std::cout << "ScavTrap copy constructor called" << std::endl;
  *this = object;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &object) {
  std::cout << "ScavTrap copy assignment operator called" << std::endl;
  _name = object._name;
  _hitPoints = object._hitPoints;
  _energyPoints = object._energyPoints;
  _attackDamage = object._attackDamage;
  return *this;
}

ScavTrap::~ScavTrap() {
  std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ScavTrap" << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ScavTrap " << _name << " attacks " << target << ", causing "
            << _attackDamage << " points of damage!" << std::endl;
  _energyPoints--;
}

void ScavTrap::guardGate() {
  std::cout << "ScavTrap " << _name << " has entered in Gate keeper mode"
            << std::endl;
}
