#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
  ClapTrap *clapTrap = new ScavTrap("evaluator");
  ScavTrap *scavTrap = new ScavTrap("sungwook");

  std::cout << "----------- clapTrap -----------" << std::endl;

  clapTrap->attack("target1");
  clapTrap->takeDamage(5);
  clapTrap->beRepaired(5);
  for (int i = 0; i < 7; i++) {
    clapTrap->attack("target2");
  }
  clapTrap->attack("target3");
  clapTrap->takeDamage(5);
  clapTrap->beRepaired(5);
  // clapTrap->guardGate();

  std::cout << "----------- scavTrap -----------" << std::endl;

  scavTrap->attack("target1");
  scavTrap->takeDamage(5);
  scavTrap->beRepaired(5);
  for (int i = 0; i < 7; i++) {
    scavTrap->attack("target2");
  }
  scavTrap->attack("target3");
  scavTrap->takeDamage(5);
  scavTrap->beRepaired(5);
  scavTrap->guardGate();
  delete clapTrap;
  delete scavTrap;
  return 0;
}