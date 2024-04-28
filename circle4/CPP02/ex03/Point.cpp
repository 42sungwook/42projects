#include "Point.hpp"

Point::Point() : _x(0), _y(0) {}

Point::Point(const float x, const float y) : _x(x), _y(y) {}

Point::Point(const Point &src) : _x(src._x), _y(src._y) {}

Point &Point::operator=(const Point &other) {
  const_cast<Fixed &>(_x) = other._x;
  const_cast<Fixed &>(_y) = other._y;

  return *this;
}

Point::~Point() {}

Fixed Point::getX(void) const { return _x; }

Fixed Point::getY(void) const { return _y; }
