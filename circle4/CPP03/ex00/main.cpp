#include "ClapTrap.hpp"

int main() {
  ClapTrap clapTrap("sungwook");

  clapTrap.attack("target1");
  clapTrap.takeDamage(5);
  clapTrap.beRepaired(5);
  for (int i = 0; i < 7; i++) {
    clapTrap.attack("target2");
  }
  clapTrap.attack("target3");
  clapTrap.takeDamage(5);
  clapTrap.beRepaired(5);
  return 0;
}
