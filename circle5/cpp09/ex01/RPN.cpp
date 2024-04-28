#include "RPN.hpp"

RPN::RPN(char* str) {
  for (int i = 0; str[i]; i++) {
    if (i % 2 == 0) {
      if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '*' &&
          str[i] != '/') {
        throw std::runtime_error("Error");
      }
    } else {
      if (str[i] != ' ') {
        throw std::runtime_error("Error");
      }
    }
  }

  _str = str;
}

RPN::~RPN() {}

RPN::RPN(const RPN& other) { _stack = other._stack; }

RPN& RPN::operator=(const RPN& other) {
  _stack = other._stack;
  return *this;
}

void RPN::calculate() {
  int a, b;

  while (*_str) {
    if (*_str == ' ') {
      _str++;
      continue;
    }
    if (isdigit(*_str)) {
      _stack.push(*_str - '0');
    } else {
      if (_stack.size() < 2) {
        throw std::runtime_error("Error");
      }
      b = _stack.top();
      _stack.pop();

      a = _stack.top();
      _stack.pop();
      switch (*_str) {
        case '+':
          _stack.push(a + b);
          break;
        case '-':
          _stack.push(a - b);
          break;
        case '*':
          _stack.push(a * b);
          break;
        case '/':
          if (b == 0) {
            throw std::runtime_error("Error");
          }
          _stack.push(a / b);
          break;
      }
    }
    _str++;
  }

  if (_stack.size() != 1) {
    throw std::runtime_error("Error");
  }

  std::cout << _stack.top() << std::endl;
}