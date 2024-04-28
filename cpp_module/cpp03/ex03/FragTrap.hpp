#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public virtual ClapTrap {
 protected:
  std::string _name;
  unsigned int _hitPoints;
  unsigned int _energyPoints;
  unsigned int _attackDamage;

 public:
  FragTrap();
  FragTrap(const std::string name);
  FragTrap(const FragTrap &object);
  FragTrap &operator=(FragTrap &object);
  ~FragTrap();

  void highFivesGuys();
  void attack(const std::string &target);
};

#endif
