#include "Brain.hpp"

Brain::Brain() { std::cout << "Brain default constructor called" << std::endl; }

Brain::Brain(const Brain &copy) {
  std::cout << "Brain copy constructor called" << std::endl;
  *this = copy;
}

Brain::~Brain() { std::cout << "Brain destructor called" << std::endl; }

Brain &Brain::operator=(const Brain &copy) {
  std::cout << "Brain assignation operator called" << std::endl;
  if (this != &copy) {
    for (int i = 0; i < 100; i++) {
      this->ideas[i] = copy.ideas[i];
    }
  }
  return *this;
}

std::string Brain::getIdea(int i) const {
  if (this->ideas[i] != "")
    return this->ideas[i];
  else
    std::cout << "There is no idea [" << i << "] in the brain" << std::endl;
  return "";
}

void Brain::setIdea(int i, std::string idea) { this->ideas[i] = idea; }
