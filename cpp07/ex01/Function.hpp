#ifndef FUNCTION_HPP
#define FUNCTION_HPP

#include <iostream>

template <typename T, typename F>

void iter(T *array, size_t length, F &func) {
  for (size_t i = 0; i < length; i++) {
    func(array[i]);
  }
}

template <typename T>

void print(T const &t) {
  std::cout << t << std::endl;
}

#endif