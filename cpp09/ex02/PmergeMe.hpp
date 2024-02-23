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

  void PmergeMe::mergeDeque(std::deque<int>& left, std::deque<int>& right,
                            std::deque<int>& result);
  void mergeVector(std::vector<int>& arr, int left, int middle, int right);
  void mergeSort(std::deque<int>& arr);
  void mergeSort(std::vector<int>& arr, int left, int right);

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

#endif
