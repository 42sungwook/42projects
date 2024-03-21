#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int ac, char **av)
    : _ac(ac), _av(av), _dTime(0), _vTime(0) {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : _ac(other._ac),
      _av(other._av),
      _d(other._d),
      _v(other._v),
      _dTime(other._dTime),
      _vTime(other._vTime) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
  if (this != &other) {
    _ac = other._ac;
    _av = other._av;
    _d = other._d;
    _v = other._v;
    _dTime = other._dTime;
    _vTime = other._vTime;
  }

  return *this;
}

void PmergeMe::sortVector() {
  int num;

  clock_t start = clock();

  for (int i = 1; i < _ac; i++) {
    std::string str(_av[i]);
    std::istringstream iss(str);

    iss >> num;

    if (num < 1 || iss.fail()) {
      std::cout << "Error" << std::endl;
      exit(1);
    }

    _v.push_back(num);
  }

  pairSortVector(_ac - 1, 1);

  _vTime = clock() - start;
}

void PmergeMe::pairSortVector(int size, int pair) {
  if (size < 2) {
    return;
  }

  for (int i = 0; i < size - 1; i += 2) {
    if (_v[i * pair] < _v[(i + 1) * pair]) {
      std::vector<int>::iterator start = _v.begin() + i * pair;
      std::vector<int>::iterator end = start + pair;
      std::swap_ranges(start, end, end);
    }
  }
  pairSortVector(size / 2, pair * 2);
  mergeSortVector(size, pair);
}

void PmergeMe::mergeSortVector(int size, int pair) {
  std::vector<int> subchain;
  std::vector<int>::iterator it = _v.begin();
  int index = 1;
  int jacobsthal = 1;
  int square = 2;

  for (int i = 1; i < size; i += 2) {
    it += pair;
    subchain.insert(subchain.end(), it, it + pair);
    _v.erase(it, it + pair);
  }

  if (size % 2) {
    subchain.insert(subchain.end(), it, it + pair);
    _v.erase(it, it + pair);
  }

  _v.insert(_v.begin(), subchain.begin(), subchain.begin() + pair);

  for (size_t i = pair; i < subchain.size(); i += pair) {
    if (index == jacobsthal &&
        std::pow(2, square) - index <= subchain.size() / pair) {
      jacobsthal = std::pow(2, square) - index;
      binaryInsertVector(i / pair + jacobsthal - 2,
                         subchain[(jacobsthal - 1) * pair], pair,
                         jacobsthal - 1, subchain);
      square++;
    } else {
      if (index == jacobsthal) {
        index++;
      }
      binaryInsertVector(i / pair + index - 2, subchain[(index - 1) * pair],
                         pair, index - 1, subchain);
    }
    index++;
  }
}

void PmergeMe::binaryInsertVector(int range, int num, int pair, int subIndex,
                                  std::vector<int> subchain) {
  std::vector<int> temp;
  std::vector<int>::iterator it = _v.begin();

  for (int i = 0; i <= range; i++) {
    temp.push_back(*it);
    it += pair;
  }
  int index = std::lower_bound(temp.begin(), temp.end(), num) - temp.begin();

  _v.insert(_v.begin() + index * pair, subchain.begin() + subIndex * pair,
            subchain.begin() + (subIndex + 1) * pair);
}

