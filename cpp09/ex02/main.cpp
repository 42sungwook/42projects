#include "PmergeMe.hpp"

int main(int ac, char** av) {
  if (ac < 2) {
    std::cout << "Error" << std::endl;
    return 1;
  }

  PmergeMe pm(ac, av);

  pm.sortVector();
  pm.sortDeque();

  time_t vTime = pm.getVTime();
  time_t dTime = pm.getDTime();
  std::vector<int> v = pm.getV();
  std::deque<int> d = pm.getD();

  std::cout << "Time to process a range of " << v.size()
            << " elements with std::vector: " << vTime << " ms" << std::endl;
  std::cout << "Time to process a range of " << d.size()
            << " elements with std::deque: " << dTime << " ms" << std::endl;
  return 0;
}
