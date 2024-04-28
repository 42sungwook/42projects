#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : _name("Default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
  std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name)
    : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
  std::cout << "ClapTrap name constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) {
  std::cout << "ClapTrap copy constructor called" << std::endl;
  *this = other;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
  std::cout << "ClapTrap copy assignment operator called" << std::endl;
  _name = other._name;
  _hitPoints = other._hitPoints;
  _energyPoints = other._energyPoints;
  _attackDamage = other._attackDamage;
  return *this;
}

ClapTrap::~ClapTrap() {
  std::cout << "ClapTrap destructor called" << std::endl;
}

void ClapTrap::attack(const std::string &target) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ClapTrap " << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ClapTrap " << _name << " attacks " << target << ", causing "
            << _attackDamage << " points of damage!" << std::endl;
  _energyPoints--;
}

void ClapTrap::takeDamage(unsigned int amount) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ClapTrap " << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ClapTrap " << _name << " takes " << amount
            << " points of damage!" << std::endl;
  if (_hitPoints < amount)
    _hitPoints = 0;
  else
    _hitPoints -= amount;

  _energyPoints--;
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (_energyPoints == 0 || _hitPoints == 0) {
    std::cout << "ClapTrap " << _name << " can't do anything" << std::endl;
    return;
  }

  std::cout << "ClapTrap " << _name << " is repaired " << amount
            << " points of damage!" << std::endl;
  _hitPoints += amount;
  _energyPoints--;
}

std::string ClapTrap::getName() const { return _name; }

unsigned int ClapTrap::getHitPoints() const { return _hitPoints; }

unsigned int ClapTrap::getEnergyPoints() const { return _energyPoints; }

unsigned int ClapTrap::getAttackDamage() const { return _attackDamage; }
