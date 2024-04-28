#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main() {
  DiamondTrap diamondTrap("sungwook");
  std::cout << diamondTrap.getHitPoints() << std::endl;
  std::cout << diamondTrap.getEnergyPoints() << std::endl;
  std::cout << diamondTrap.getName() << "\n" << std::endl;

  diamondTrap.attack("target");
  diamondTrap.guardGate();
  diamondTrap.highFivesGuys();
  diamondTrap.whoAmI();
  diamondTrap.getAttackDamage();
  return 0;
}
