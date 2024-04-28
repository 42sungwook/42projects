#include "Zombie.hpp"

// void a()
//{
//	system("leaks ex00");
// }

int main() {
  Zombie *zombie1 = newZombie("Zombie1");
  zombie1->announce();
  delete zombie1;

  randomChump("Zombie2");

  // atexit(a);
}