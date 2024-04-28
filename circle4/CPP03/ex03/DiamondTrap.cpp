#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
    : ClapTrap(), ScavTrap(), FragTrap(), _name("Default") {
  std::cout << "DiamondTrap default constructor called" << std::endl;

  ClapTrap::_name += "_clap_name";
  _hitPoints = FragTrap::_hitPoints;
  _energyPoints = ScavTrap::_energyPoints;
  _attackDamage = FragTrap::_attackDamage;
}

DiamondTrap::DiamondTrap(const std::string name)
    : ClapTrap(name), ScavTrap(name), FragTrap(name), _name(name) {
  std::cout << "DiamondTrap name constructor called" << std::endl;

  ClapTrap::_name += "_clap_name";
  _hitPoints = FragTrap::_hitPoints;
  _energyPoints = ScavTrap::_energyPoints;
  _attackDamage = FragTrap::_attackDamage;
}

DiamondTrap::DiamondTrap(const DiamondTrap &object) {
  std::cout << "DiamondTrap copy constructor called" << std::endl;

  *this = object;
}

DiamondTrap &DiamondTrap::operator=(DiamondTrap &object) {
  std::cout << "DiamondTrap copy assignment operator called" << std::endl;

  _name = object._name;
  _hitPoints = object._hitPoints;
  _energyPoints = object._energyPoints;
  _attackDamage = object._attackDamage;
  return *this;
}

DiamondTrap::~DiamondTrap() {
  std::cout << "DiamondTrap destructor called" << std::endl;
}

void DiamondTrap::whoAmI() {
  std::cout << "DiamondTrap name is " << _name << " and ClapTrap name is "
            << ClapTrap::getName() << std::endl;
}

std::string DiamondTrap::getName() const { return _name; }

unsigned int DiamondTrap::getHitPoints() const { return _hitPoints; }

unsigned int DiamondTrap::getEnergyPoints() const { return _energyPoints; }

unsigned int DiamondTrap::getAttackDamage() const { return _attackDamage; }
