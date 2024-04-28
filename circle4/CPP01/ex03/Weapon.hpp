#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon {
 private:
  std::string _type;

 public:
  Weapon();
  ~Weapon();
  Weapon &operator=(const Weapon &type);
  Weapon(const Weapon &object);
  Weapon(const std::string &type);
  const std::string &getType(void) const;
  void setType(std::string type);
};

#endif
