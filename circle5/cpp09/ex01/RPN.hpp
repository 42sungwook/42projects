#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

class RPN {
 public:
  RPN(char* str);
  ~RPN();
  RPN(const RPN& other);
  RPN& operator=(const RPN& other);
  void calculate();

 private:
  std::stack<int> _stack;
  char* _str;
};

#endif
