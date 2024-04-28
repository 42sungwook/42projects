#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap {
 private:
  std::string _name;
  unsigned int _hitPoints;
  unsigned int _energyPoints;
  unsigned int _attackDamage;

 public:
  DiamondTrap();
  DiamondTrap(const std::string name);
  DiamondTrap(const DiamondTrap &object);
  DiamondTrap &operator=(DiamondTrap &object);
  virtual ~DiamondTrap();
  void whoAmI();
  using ScavTrap::attack;

  std::string getName() const;
  unsigned int getHitPoints() const;
  unsigned int getEnergyPoints() const;
  unsigned int getAttackDamage() const;
};

#endif
