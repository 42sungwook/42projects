#include "Cat.hpp"

Cat::Cat() : AAnimal("Cat") {
  std::cout << "Cat default constructor called" << std::endl;
  _brain = new Brain();
}

Cat::Cat(const Cat &copy) {
  std::cout << "Cat copy constructor called" << std::endl;
  _brain = new Brain();
  *this = copy;
}

Cat::~Cat() {
  std::cout << "Cat destructor called" << std::endl;
  delete _brain;
}

Cat &Cat::operator=(const Cat &copy) {
  std::cout << "Cat assignation operator called" << std::endl;
  if (this != &copy) {
    this->type = copy.type;
    *_brain = *copy._brain;
  }
  return *this;
}

void Cat::makeSound() const { std::cout << "meow" << std::endl; }

Brain *Cat::accessBrain(void) { return _brain; }