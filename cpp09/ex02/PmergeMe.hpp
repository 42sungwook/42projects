#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <deque>
#include <iostream>
#include <vector>

class PmergeMe {
 public:
  PmergeMe(std::deque<int> d, std::vector<int> v);
  ~PmergeMe();
  PmergeMe(const PmergeMe& other);
  PmergeMe& operator=(const PmergeMe& other);

  void mergeDeque();
  void mergeVector();

  std::deque<int> getD() const { return _d; }
  std::vector<int> getV() const { return _v; }
  double getDTime() const { return _dTime; }
  double getVTime() const { return _vTime; }

 private:
  std::deque<int> _d;
  std::vector<int> _v;
  double _dTime;
  double _vTime;
};

void rearrangePairs(std::deque<int>& dq, size_t gap);
void rearrangePairs(std::vector<int>& vc, size_t gap);
unsigned int jacobsthalNumberAtIndex(unsigned int index, unsigned int size);
int binarySearch(std::vector<int>& vc, int target, int start, int end, int gap);

#endif
