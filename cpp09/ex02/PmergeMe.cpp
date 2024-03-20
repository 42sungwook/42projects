#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::deque<int> d, std::vector<int> v) : _d(d), _v(v) {
  _dTime = 0;
  _vTime = 0;
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) {
  _d = other._d;
  _v = other._v;
  _dTime = other._dTime;
  _vTime = other._vTime;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  _d = other._d;
  _v = other._v;
  _dTime = other._dTime;
  _vTime = other._vTime;
  return *this;
}
