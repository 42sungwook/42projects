#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public virtual ClapTrap {
 protected:
  std::string _name;
  unsigned int _hitPoints;
  unsigned int _energyPoints;
  unsigned int _attackDamage;

 public:
  ScavTrap();
  ScavTrap(const std::string name);
  ScavTrap(const ScavTrap &object);
  ScavTrap &operator=(ScavTrap &object);
  virtual ~ScavTrap();

  void guardGate();
  void attack(const std::string &target);
};

#endif
