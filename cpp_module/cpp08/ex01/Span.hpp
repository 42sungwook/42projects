#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

class Span {
 public:
  Span(unsigned int n);
  Span(const Span &src);
  ~Span();
  Span &operator=(const Span &src);

  void addNumber(int n);
  void addNumber(int start, int end);
  int shortestSpan();
  int longestSpan();

 private:
  unsigned int _n;
  std::vector<int> _arr;
  unsigned int _size;
};

template <typename T>

bool easyfind(T &container, int value) {
  typename T::iterator it =
      std::find(container.begin(), container.end(), value);

  if (it != container.end()) {
    return true;
  }

  return false;
}

#endif
