#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main() {
  FragTrap fragTrap("sungwook");
  ScavTrap scavTrap("evaluator");

  std::cout << "----------- fragTrap -----------" << std::endl;
  std::cout << fragTrap.getHitPoints() << std::endl;
  std::cout << fragTrap.getEnergyPoints() << std::endl;
  std::cout << fragTrap.getName() << "\n" << std::endl;

  fragTrap.attack("target1");
  fragTrap.highFivesGuys();
  fragTrap.takeDamage(5);
  fragTrap.beRepaired(5);

  std::cout << "----------- scavTrap -----------" << std::endl;
  std::cout << scavTrap.getHitPoints() << std::endl;
  std::cout << scavTrap.getEnergyPoints() << std::endl;
  std::cout << scavTrap.getName() << "\n" << std::endl;

  scavTrap.attack("target2");
  scavTrap.guardGate();
  scavTrap.takeDamage(5);
  scavTrap.beRepaired(5);
  std::cout << "---------------------------------" << std::endl;
  return 0;
}