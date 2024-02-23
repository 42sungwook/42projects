// vector, deque

#include "PmergeMe.hpp"

int main(int ac, char** av) {
  if (ac < 2) {
    std::cout << "Error" << std::endl;
    return 1;
  }

  std::deque<int> d;
  std::vector<int> v;
  int tmp;

  for (int i = 1; i < ac; i++) {
    tmp = atoi(av[i]);

    if (tmp == 0 && av[i][0] != '0') {
      std::cout << "Error" << std::endl;
      return 1;
    }

    d.push_back(tmp);
    v.push_back(tmp);
  }

  PmergeMe p(d, v);

  p.mergeDeque();
  p.mergeVector();

  return 0;
}