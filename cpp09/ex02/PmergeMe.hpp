#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <cmath>
#include <ctime>
#include <deque>
#include <iostream>
#include <sstream>
#include <vector>

class PmergeMe {
 public:
  PmergeMe(int ac, char** av);
  ~PmergeMe();
  PmergeMe(const PmergeMe& other);
  PmergeMe& operator=(const PmergeMe& other);

  void sortVector();
  void pairSortVector(int size, int pair);
  void mergeSortVector(int size, int pair);
  void binaryInsertVector(int range, int num, int pair, int subIndex,
                          std::vector<int> subchain);
  void sortDeque();
  void pairSortDeque(int size, int pair);
  void mergeSortDeque(int size, int pair);
  void binaryInsertDeque(int range, int num, int pair, int subIndex,
                          std::deque<int> subchain);

  std::deque<int> getD() const { return _d; }
  std::vector<int> getV() const { return _v; }
  clock_t getDTime() const { return _dTime; }
  clock_t getVTime() const { return _vTime; }

 private:
  int _ac;
  char** _av;
  std::deque<int> _d;
  std::vector<int> _v;
  clock_t _dTime;
  clock_t _vTime;
};

#endif
