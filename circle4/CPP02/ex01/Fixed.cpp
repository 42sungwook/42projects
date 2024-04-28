#include "Fixed.hpp"

Fixed::Fixed() : _value(0) {
  std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) {
  std::cout << "Int constructor called" << std::endl;
  _value = value << _bits;
}

Fixed::Fixed(const float value) {
  std::cout << "Float constructor called" << std::endl;
  _value = (int)roundf(value * (1 << _bits));
}

Fixed::Fixed(const Fixed &src) {
  std::cout << "Copy constructor called" << std::endl;
  *this = src;
}

int Fixed::getRawBits(void) const {
  std::cout << "getRawBits member function called" << std::endl;
  return _value;
}

void Fixed::setRawBits(int const raw) {
  std::cout << "setRawBits member function called" << std::endl;
  _value = raw;
}

Fixed &Fixed::operator=(const Fixed &other) {
  std::cout << "Copy assignment operator called" << std::endl;
  _value = other.getRawBits();
  return *this;
}

Fixed::~Fixed() { std::cout << "Destructor called" << std::endl; }

float Fixed::toFloat(void) const { return (float)_value / (1 << _bits); }

int Fixed::toInt(void) const { return _value >> _bits; }

std::ostream &operator<<(std::ostream &os, const Fixed &other) {
  os << other.toFloat();
  return os;
}