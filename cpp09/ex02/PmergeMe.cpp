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
  rearrangePairs(_d, 1);

  std::cout << "Deque: ";
  for (std::deque<int>::iterator it = _d.begin(); it != _d.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

void PmergeMe::mergeVector() {
  rearrangePairs(_v, 1);

  std::cout << "Vector: ";
  for (std::vector<int>::iterator it = _v.begin(); it != _v.end(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

size_t rearrangePairs(std::deque<int>& dq, size_t gap) {
  if (gap < 0 || gap * 2 > dq.size()) return;

  int tmp;

  for (size_t i = 0; i < dq.size() - gap; i += gap * 2) {
    if (dq[i] > dq[i + gap]) continue;
    for (size_t j = 0; j < gap; j++) {
      tmp = dq[i + j];
      dq[i + j] = dq[i + gap + j];
      dq[i + gap + j] = tmp;
    }
  }

  rearrangePairs(dq, gap * 2);
}

size_t rearrangePairs(std::vector<int>& vc, size_t gap) {
  if (gap < 0 || gap * 2 > vc.size()) return gap;

  int tmp;

  for (size_t i = 0; i < vc.size() - gap; i += gap * 2) {
    if (vc[i] > vc[i + gap]) continue;
    for (size_t j = 0; j < gap; j++) {
      tmp = vc[i + j];
      vc[i + j] = vc[i + gap + j];
      vc[i + gap + j] = tmp;
    }
  }

  rearrangePairs(vc, gap * 2);
}

// insert 함수 활용해서 insert 구현