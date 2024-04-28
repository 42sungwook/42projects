#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
  std::cout << "Dog default constructor called" << std::endl;
  _brain = new Brain();
}

Dog::Dog(const Dog &copy) {
  std::cout << "Dog copy constructor called" << std::endl;
  _brain = new Brain();
  *this = copy;
}

Dog::~Dog() {
  std::cout << "Dog destructor called" << std::endl;
  delete _brain;
}

Dog &Dog::operator=(const Dog &copy) {
  std::cout << "Dog assignation operator called" << std::endl;
  if (this != &copy) {
    this->type = copy.type;
    *_brain = *copy._brain;
  }
  return *this;
}

void Dog::makeSound() const { std::cout << "woof" << std::endl; }

Brain *Dog::accessBrain(void) { return _brain; }