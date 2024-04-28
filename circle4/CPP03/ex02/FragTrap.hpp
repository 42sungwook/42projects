#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
 public:
  FragTrap();
  FragTrap(const std::string &name);
  FragTrap(const FragTrap &object);
  FragTrap &operator=(const FragTrap &object);
  virtual ~FragTrap();

  void highFivesGuys();
  void attack(const std::string &target);
};

#endif
