#ifndef BASE_HPP
#define BASE_HPP

#include <iostream>

// orthodox canonical class form 지킬필요 x
class Base {
 public:
  virtual ~Base() {}
  virtual std::string getType() = 0;
};

class A : public Base {
 public:
  std::string getType();
};

class B : public Base {
 public:
  std::string getType();
};

class C : public Base {
 public:
  std::string getType();
};

#endif