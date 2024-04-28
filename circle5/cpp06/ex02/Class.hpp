#ifndef BASE_HPP
#define BASE_HPP

#include <stdlib.h>

#include <iostream>
#include <typeinfo>

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