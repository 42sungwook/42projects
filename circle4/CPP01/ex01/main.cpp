#include "Zombie.hpp"

// void a()
//{
//	system("leaks ex01");
// }

int main() {
  Zombie *zombie = zombieHorde(1, "ZombieA");

  delete[] zombie;

  Zombie *zombie2 = zombieHorde(2, "ZombieB");

  for (int i = 0; i < 2; i++) zombie2[i].announce();

  delete[] zombie2;
  // atexit(a);
}