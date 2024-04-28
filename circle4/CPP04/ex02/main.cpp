#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
  AAnimal* j = new Dog();
  AAnimal* i = new Cat();

  delete i;
  delete j;

  std::cout << std::endl;

  AAnimal* animals[4];
  for (int k = 0; k < 4; k++) {
    if (k % 2 == 0)
      animals[k] = new Dog();
    else
      animals[k] = new Cat();
  }

  std::cout << std::endl;

  for (int k = 0; k < 4; k++) {
    delete animals[k];
  }

  std::cout << std::endl;

  Cat a;

  a.accessBrain()->setIdea(0, "Eat");
  a.accessBrain()->setIdea(1, "Sleep");
  a.accessBrain()->setIdea(2, "Play");

  Cat b(a);  // copy
  std::cout << "b brain idea: " << b.accessBrain()->getIdea(0) << std::endl;
  std::cout << "b brain idea: " << b.accessBrain()->getIdea(1) << std::endl;
  std::cout << "b brain idea: " << b.accessBrain()->getIdea(2) << std::endl;
  std::cout << "b brain idea: " << b.accessBrain()->getIdea(3) << std::endl;

  a.accessBrain()->setIdea(0, "Work");
  std::cout << "a brain idea: " << a.accessBrain()->getIdea(0) << std::endl;
  std::cout << "b brain idea: " << b.accessBrain()->getIdea(0) << std::endl;

  return 0;
}
