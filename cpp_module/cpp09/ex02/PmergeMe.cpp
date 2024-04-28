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

  std::cout << "Before (Vector): ";
  for (size_t i = 0; i < _v.size(); i++) {
    std::cout << _v[i] << " ";
  }
  std::cout << std::endl;

  pairSortVector(_ac - 1, 1);
  _vTime = clock() - start;

  std::cout << "After (Vector): ";
  for (size_t i = 0; i < _v.size(); i++) {
    std::cout << _v[i] << " ";
  }
  std::cout << std::endl;
  if (std::is_sorted(_v.begin(), _v.end())) {
    std::cout << "Sorted" << std::endl;
  } else {
    std::cout << "Not sorted" << std::endl;
  }
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
  int index = 2;
  int jacobsthal = 1;
  int square = 3;

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
    if (static_cast<int>(i) == pair && subchain.size() / pair >= 3) {
      binaryInsertVector(2, subchain[2 * pair], pair, 2, subchain);
      index = 3;
    } else if (index == jacobsthal &&
               std::pow(2, square) - std::pow(2, square - 1) <=
                   subchain.size() / pair) {
      jacobsthal = std::pow(2, square) - std::pow(2, square - 1) + 1;
      index = jacobsthal;
      binaryInsertVector(i / pair + jacobsthal - 2,
                         subchain[(jacobsthal - 1) * pair], pair,
                         jacobsthal - 1, subchain);
      jacobsthal = std::pow(2, square - 1) - std::pow(2, square - 2) + 1;
      square++;
    } else {
      binaryInsertVector(i / pair + index - 2, subchain[(index - 1) * pair],
                         pair, index - 1, subchain);
    }
    index--;
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

void PmergeMe::sortDeque() {
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

    _d.push_back(num);
  }

  std::cout << "Before (Deque): ";
  for (size_t i = 0; i < _d.size(); i++) {
    std::cout << _d[i] << " ";
  }
  std::cout << std::endl;

  pairSortDeque(_ac - 1, 1);

  _dTime = clock() - start;

  std::cout << "After (Deque): ";
  for (size_t i = 0; i < _d.size(); i++) {
    std::cout << _d[i] << " ";
  }
  std::cout << std::endl;
  if (std::is_sorted(_d.begin(), _d.end())) {
    std::cout << "Sorted" << std::endl;
  } else {
    std::cout << "Not sorted" << std::endl;
  }
}

void PmergeMe::pairSortDeque(int size, int pair) {
  if (size < 2) {
    return;
  }

  for (int i = 0; i < size - 1; i += 2) {
    if (_d[i * pair] < _d[(i + 1) * pair]) {
      std::deque<int>::iterator start = _d.begin() + i * pair;
      std::deque<int>::iterator end = start + pair;
      std::swap_ranges(start, end, end);
    }
  }
  pairSortDeque(size / 2, pair * 2);
  mergeSortDeque(size, pair);
}

void PmergeMe::mergeSortDeque(int size, int pair) {
  std::deque<int> subchain;
  std::deque<int>::iterator it = _d.begin();
  int index = 2;
  int jacobsthal = 1;
  int square = 3;

  for (int i = 1; i < size; i += 2) {
    it += pair;
    subchain.insert(subchain.end(), it, it + pair);
    it = _d.erase(it, it + pair);  // vector deque 차이
  }

  if (size % 2) {
    subchain.insert(subchain.end(), it, it + pair);
    _d.erase(it, it + pair);
  }

  _d.insert(_d.begin(), subchain.begin(), subchain.begin() + pair);

  for (size_t i = pair; i < subchain.size(); i += pair) {
    if (static_cast<int>(i) == pair && subchain.size() / pair >= 3) {
      binaryInsertDeque(2, subchain[2 * pair], pair, 2, subchain);
      index = 3;
    } else if (index == jacobsthal &&
               std::pow(2, square) - std::pow(2, square - 1) <=
                   subchain.size() / pair) {
      jacobsthal = std::pow(2, square) - std::pow(2, square - 1) + 1;
      index = jacobsthal;
      binaryInsertDeque(i / pair + jacobsthal - 2,
                        subchain[(jacobsthal - 1) * pair], pair, jacobsthal - 1,
                        subchain);
      jacobsthal = std::pow(2, square - 1) - std::pow(2, square - 2) + 1;
      square++;
    } else {
      binaryInsertDeque(i / pair + index - 2, subchain[(index - 1) * pair],
                        pair, index - 1, subchain);
    }
    index--;
  }
}

void PmergeMe::binaryInsertDeque(int range, int num, int pair, int subIndex,
                                 std::deque<int> subchain) {
  std::deque<int> temp;
  std::deque<int>::iterator it = _d.begin();

  for (int i = 0; i <= range; i++) {
    temp.push_back(*it);
    it += pair;
  }
  int index = std::lower_bound(temp.begin(), temp.end(), num) - temp.begin();

  _d.insert(_d.begin() + index * pair, subchain.begin() + subIndex * pair,
            subchain.begin() + (subIndex + 1) * pair);
}
