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

void PmergeMe::makeChain(int num, int size, std::vector<int> &main,
                         std::vector<int> &sub) {
  std::vector<int>::iterator it = _v.begin();

  for (int i = 0; i < num; ++i) {
    if (i == num - 1 || i % 2 == 1)
      sub.insert(sub.end(), it + i * size, it + (i + 1) * size);
    else if (i % 2 == 0)
      main.insert(main.end(), it + i * size, it + (i + 1) * size);
  }
}

void PmergeMe::binarySearchInsert(std::vector<int> &mainChain,
                                  std::vector<int> &subChain, size_t idx,
                                  size_t size) {
  int left = 0;
  int right = idx + numOfInsert_;
  std::vector<int>::iterator subIt = subChain.begin() + idx * size;
  std::vector<int>::iterator mainIt = mainChain.begin();
  if (idx == 0) {
    mainChain.insert(mainIt, subIt, subIt + size);
    return;
  }

  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (mainChain[mid * size] < *subIt) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  mainChain.insert(mainIt + left * size, subIt, subIt + size);
  ++numOfInsert_;
}

void PmergeMe::insertion(int size, int gap, std::vector<int> &main,
                         std::vector<int> &sub) {
  int idx = 0;
  jacobsthalIndex_ = 0;
  numOfInsert_ = 0;
  int subChainNum = size / 2 + size % 2;
  makeChain(size, gap, main, sub);
  for (int i = 0; i < subChainNum; ++i) {
    idx = getNextIndex(idx);
    if (idx >= subChainNum) idx = subChainNum;
    binarySearchInsert(main, sub, idx - 1, gap);
  }
  for (size_t i = 0; i < main.size(); ++i) {
    _v[i] = main[i];
  }
}

void PmergeMe::comparePair(int size, int gap) {
  std::vector<int>::iterator it = _v.begin();

  for (int i = 0; i < size - 1; i += 2) {
    std::vector<int>::iterator first = it + i * gap;
    std::vector<int>::iterator second = it + (i + 1) * gap;
    if (*first < *second) std::swap_ranges(first, second, second);
  }
}

void PmergeMe::recursive(int size, int gap) {
  if (size == 1) return;
  std::vector<int> mainChain;
  std::vector<int> subChain;
  comparePair(size, gap);
  recursive(size / 2, gap * 2);
  insertion(size, gap, mainChain, subChain);
}

void PmergeMe::sortVector() { recursive(_v.size(), 1); }

void PmergeMe::sortDeque() {
  std::chrono::system_clock::time_point start =
      std::chrono::system_clock::now();
  std::sort(_d.begin(), _d.end());
  std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
  _dTime = std::chrono::duration<double>(end - start).count();
}
