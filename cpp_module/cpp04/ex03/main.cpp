#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

// void a() { system("leaks ex03"); }

int main() {
  IMateriaSource* src = new MateriaSource();
  src->learnMateria(new Ice());
  src->learnMateria(new Cure());

  ICharacter* me = new Character("me");
  AMateria* tmp;

  tmp = src->createMateria("ice");
  me->equip(tmp);
  me->use(1, *me);  // Cure (0) is not equipped
  tmp = src->createMateria("cure");
  me->equip(tmp);
  me->equip(new Ice());  // make Ice directly
  me->use(2, *me);       // Ice (1) is equipped

  ICharacter* bob = new Character("bob");
  me->use(0, *bob);
  me->use(1, *bob);

  delete bob;
  delete me;
  delete src;

  Character you("you");

  you.equip(new Ice());
  you.use(0, you);

  // atexit(a);
  return 0;
}