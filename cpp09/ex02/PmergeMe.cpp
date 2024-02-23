#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::deque<int> d, std::vector<int> v) {
  _d = d;
  _v = v;
}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) {
  _d = other._d;
  _v = other._v;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
  _d = other._d;
  _v = other._v;
  return *this;
}

void PmergeMe::mergeDeque() {
	

}

void PmergeMe::mergeVector() {

}
