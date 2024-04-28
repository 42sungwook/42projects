#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <iostream>
#include <vector>

template <typename T>

bool easyfind(T &container, int value) {
  typename T::iterator it =
      std::find(container.begin(), container.end(), value);

  if (it != container.end()) {
    std::cout << "Value " << value << " found in index " << *it << std::endl;
    return true;
  }

  std::cout << "Value " << value << " not found" << std::endl;
  return false;
}

#endif
