#include "Point.hpp"

static int calculateOrientation(const Point &p1, const Point &p2,
                                const Point &p3) {
  Fixed value = (p2.getY() - p1.getY()) * (p3.getX() - p2.getX()) -
                (p2.getX() - p1.getX()) * (p3.getY() - p2.getY());
  if (value == 0)
    return 0;  // Collinear
  else if (value > 0)
    return 1;  // Clockwise
  else
    return 2;  // Counterclockwise
}

bool bsp(const Point &p1, const Point &p2, const Point &p3, const Point &p) {
  int orientation1 = calculateOrientation(p1, p2, p);
  int orientation2 = calculateOrientation(p2, p3, p);
  int orientation3 = calculateOrientation(p3, p1, p);

  return (orientation1 == orientation2 && orientation2 == orientation3);
}