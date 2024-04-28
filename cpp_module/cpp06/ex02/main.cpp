#include "Class.hpp"

Base *generate() {
  int random = rand() % 3;
  if (random == 0) {
    return new A;
  } else if (random == 1) {
    return new B;
  } else {
    return new C;
  }
}

void identify(Base *p) {
  if (dynamic_cast<A *>(p)) {
    std::cout << "A" << std::endl;
  } else if (dynamic_cast<B *>(p)) {
    std::cout << "B" << std::endl;
  } else if (dynamic_cast<C *>(p)) {
    std::cout << "C" << std::endl;
  }
}

void identify(Base &p) {
  try {
    A &a = dynamic_cast<A &>(p);
    std::cout << a.getType() << std::endl;
  } catch (std::bad_cast &e) {
  }
  try {
    B &b = dynamic_cast<B &>(p);
    std::cout << b.getType() << std::endl;
  } catch (std::bad_cast &e) {
  }
  try {
    C &c = dynamic_cast<C &>(p);
    std::cout << c.getType() << std::endl;
  } catch (std::bad_cast &e) {
  }
}

int main() {
  srand(time(NULL));

  std::cout << "=====random class=====" << std::endl;
  Base *base = generate();
  identify(base);
  identify(*base);

  std::cout << "===== A class =====" << std::endl;
  A *a = new A;
  identify(a);
  identify(*a);

  std::cout << "===== B class =====" << std::endl;
  B *b = new B;
  identify(b);
  identify(*b);

  std::cout << "===== C class =====" << std::endl;
  C *c = new C;
  identify(c);
  identify(*c);

  delete a;
  delete b;
  delete c;
  delete base;

  return 0;
}