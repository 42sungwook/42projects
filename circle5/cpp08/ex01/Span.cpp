#include "Span.hpp"

Span::Span(unsigned int n) : _n(n), _size(0) {}

Span::~Span() {}

Span::Span(const Span &src) { *this = src; }

Span &Span::operator=(const Span &src) {
  if (this != &src) {
    _n = src._n;
    _arr = src._arr;
    _size = src._size;
  }

  return *this;
}

void Span::addNumber(int n) {
  if (easyfind(_arr, n)) {
    throw std::runtime_error("ERROR: Number already exists");
  }

  if (_size < _n) {
    _arr.push_back(n);
    _size++;
  } else {
    throw std::runtime_error("ERROR: Array is full");
  }
}

void Span::addNumber(int start, int end) {
  if (start > end) {
    throw std::range_error("ERROR: Start is greater than end");
  }
  if (_size + (end - start) > _n) {
    throw std::runtime_error("ERROR: Array is full");
  }
  for (int i = start; i <= end; i++) {
    if (easyfind(_arr, i)) {
      throw std::runtime_error("ERROR: Number already exists");
    }
  }

  for (int i = start; i <= end; i++) {
    _arr.push_back(i);
    _size++;
  }
}

int Span::shortestSpan() {
  if (_size < 2) {
    throw std::runtime_error("ERROR: Array is too short");
  }
  std::sort(_arr.begin(), _arr.end());
  int minLength = _arr[1] - _arr[0];
  for (unsigned int i = 2; i < _size; i++) {
    if (_arr[i] - _arr[i - 1] < minLength) {
      minLength = _arr[i] - _arr[i - 1];
    }
  }
  return minLength;
}

int Span::longestSpan() {
  if (_size < 2) {
    throw std::runtime_error("ERROR: Array is too short");
  }
  std::sort(_arr.begin(), _arr.end());
  return _arr[_size - 1] - _arr[0];
}
