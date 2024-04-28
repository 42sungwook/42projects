#include "AAnimal.hpp"

AAnimal::AAnimal() : type("AAnimal") {
  std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(std::string type) : type(type) {
  std::cout << "AAnimal type constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &copy) {
  std::cout << "AAnimal copy constructor called" << std::endl;
  *this = copy;
}

AAnimal::~AAnimal() { std::cout << "AAnimal destructor called" << std::endl; }

AAnimal &AAnimal::operator=(const AAnimal &copy) {
  std::cout << "AAnimal assignation operator called" << std::endl;
  if (this != &copy) this->type = copy.type;
  return *this;
}

std::string AAnimal::getType() const { return this->type; }
