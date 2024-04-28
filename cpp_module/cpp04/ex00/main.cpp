#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main() {
  const Animal* meta = new Animal();
  const Animal* j = new Dog();
  const Animal* i = new Cat();

  std::cout << "-------------------------------" << std::endl;

  std::cout << meta->getType() << " " << std::endl;
  std::cout << j->getType() << " " << std::endl;
  std::cout << i->getType() << " " << std::endl;
  meta->makeSound();
  i->makeSound();
  j->makeSound();

  std::cout << "-------------------------------" << std::endl;

  delete meta;
  delete j;
  delete i;

  const WrongAnimal* wrongMeta = new WrongAnimal();
  const WrongAnimal* wrongI = new WrongCat();
  std::cout << wrongMeta->getType() << " " << std::endl;
  std::cout << wrongI->getType() << " " << std::endl;
  wrongMeta->makeSound();
  wrongI->makeSound();

  std::cout << "-------------------------------" << std::endl;

  delete wrongMeta;
  delete wrongI;

  return 0;
}
