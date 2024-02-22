#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <iostream>
#include <list>
#include <stack>

template <typename T>

class MutantStack : public std::stack<T> {
 public:
  MutantStack() : std::stack<T>() {}
  MutantStack(const MutantStack &src) : std::stack<T>(src) {}
  ~MutantStack() {}
  MutantStack &operator=(const MutantStack &src) {
    if (this == &src) {
      return *this;
    }
    std::stack<T>::operator=(src);
    return *this;
  }

  typedef typename std::stack<T>::container_type::iterator iterator;

  iterator begin() { return std::stack<T>::c.begin(); }
  iterator end() { return std::stack<T>::c.end(); }
};

#endif
