#include "PmergeMe.hpp"

int main(int ac, char** av) {
  if (ac < 2) {
    std::cout << "Error" << std::endl;
    return 1;
  }

  PmergeMe pm(ac, av);

  pm.sortVector();

  time_t v = pm.getVTime();

  std::cout << v << std::endl;

  return 0;
}
