#include "Point.hpp"

int main() {
  Point p(4, 2.5);
  Point p1(1.0, 1.0);
  Point p2(4.0, 1.0);
  Point p3(3.0, 4.0);

  if (bsp(p1, p2, p3, p)) {
    std::cout << "The point is inside the triangle." << std::endl;
  } else {
    std::cout << "The point is outside the triangle." << std::endl;
  }

  return 0;
}