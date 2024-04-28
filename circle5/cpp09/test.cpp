// 0 8 2 4 3 5 7 6 1 9
// 80  42  53 76 91
// 8042 7653 91
// 80427653 91

// 8042        /3
// 7653 91
// 76 53 80 42 91 /2

1 3 5 11 21 x xx x

// 0 2 6 3 1 9 8 5 7 4
// 20 63 91 85 74
// 6320 9185 74
// 91856320 74

// 9185
// 6320 74
// 6320 9185 74
// 63 20 91 85 74
/*
// 63 91
// 20 85 74
*/
/*
// 20 63 91
// 20 85 74
*/
/*
// 20 63 74 91
//    20 85 74
*/
/*
// 20 63 74 85 91
//    20 85 74
*/
/*
// 2 6 7 8 9
// 0 3 4 5 1
*/
/*
// 0 2 6 7 8 9
//   0 3 4 5 1
*/
/*
// 0 2 4 6 7 8 9
//     0 3 4 5 1
*/
/*
// 0 2 3 4 6 7 8 9
//       0 3 4 5 1
*/
/*
// 0 2 3 4 6 7 8 9
//       0 3 4 5 1
*/


#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <ctime>
#include <deque>
#include <iostream>
#include <limits>
#include <list>
#include <sstream>
#include <utility>
#include <vector>

typedef std::vector<unsigned int> vector;
typedef std::list<unsigned int> list;
typedef std::deque<unsigned int> deque;
typedef std::vector<unsigned int>::iterator vectorIt;
typedef std::list<unsigned int>::iterator listIt;
typedef std::deque<unsigned int>::iterator dequeIt;

class PmergeMe {
 private:
  static vector _vec;
  static list _lst;
  static deque _deq;

  PmergeMe();
  PmergeMe(const PmergeMe &src);
  PmergeMe &operator=(const PmergeMe &src);

  static void validationTransformContainers(int argc, const char *argv[]);

  template <typename Container>
  static clock_t playFordJohnsonCountTime(Container &container) {
    clock_t temp;

    temp = clock();
    fordJohnsonRecursion(container, 1, container.size() / 2);
    return (clock() - temp);
  }

  template <typename Container>
  static void fordJohnsonRecursion(Container &numbers, size_t elementSize,
                                   size_t pairCount) {
    bool unpairedFlag;

    // Pair 내부 비교 -> 큰 순으로 배열, Pair을 없는 element가 있는지 확인
    unpairedFlag = pairComparison(numbers, elementSize, pairCount);
    // Pair가 하나가 될때까지 재귀적 반복
    if (pairCount != 1)
      fordJohnsonRecursion(numbers, elementSize * 2, pairCount / 2);
    // Binary Search를 이용한 Insertion
    pendingElementsInsertion(numbers, unpairedFlag, elementSize, pairCount);
  }

  static bool pairComparison(vector &numbers, size_t elementSize,
                             size_t pairCount);
  static void pendingElementsInsertion(vector &numbers, bool upFlag,
                                       size_t elemSize, size_t pairCnt);
  static void binarySearchInsertion(vector &lgElements, vector &pdElement,
                                    size_t elemSize);

  static bool pairComparison(list &numbers, size_t elementSize,
                             size_t pairCount);
  static void pendingElementsInsertion(list &numbers, bool upFlag,
                                       size_t elemSize, size_t pairCnt);
  static void binarySearchInsertion(list &lgElements, list &pdElements,
                                    size_t elemSize);

  static bool pairComparison(deque &numbers, size_t elementSize,
                             size_t pairCount);
  static void pendingElementsInsertion(deque &numbers, bool upFlag,
                                       size_t elemSize, size_t pairCnt);
  static void binarySearchInsertion(deque &lgElements, deque &pdElement,
                                    size_t elemSize);

 public:
  ~PmergeMe();

  static void fordJohnsonSort(int argc, const char *argv[]);
};

#endif


#include "PmergeMe.hpp"

    vector PmergeMe::_vec;
list PmergeMe::_lst;
deque PmergeMe::_deq;

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src) { *this = src; }

PmergeMe &PmergeMe::operator=(const PmergeMe &src) {
  (void)src;
  return *this;
}

void PmergeMe::fordJohnsonSort(int argc, const char *argv[]) {
  clock_t vecTime;
  clock_t lstTime;
  clock_t deqTime;

  validationTransformContainers(argc, argv);
  std::cout << "Before:";
  for (size_t i = 0; i < _vec.size(); i++) std::cout << " " << _vec[i];
  std::cout << std::endl;

  vecTime = playFordJohnsonCountTime(_vec);
  lstTime = playFordJohnsonCountTime(_lst);
  deqTime = playFordJohnsonCountTime(_deq);

  std::cout << "After:";
  for (size_t i = 0; i < _vec.size(); i++) std::cout << " " << _vec[i];
  std::cout << std::endl << "After:";
  for (listIt it = _lst.begin(); it != _lst.end(); it++)
    std::cout << " " << *it;
  std::cout << std::endl << "After:";
  for (dequeIt it = _deq.begin(); it != _deq.end(); it++)
    std::cout << " " << *it;
  std::cout << std::endl;
  std::cout << "Time to process a range of " << _vec.size()
            << " elements with std::vector : " << vecTime << " us" << std::endl;
  std::cout << "Time to process a range of " << _lst.size()
            << " elements with std::list : " << lstTime << " us" << std::endl;
  std::cout << "Time to process a range of " << _deq.size()
            << " elements with std::deque : " << deqTime << " us" << std::endl;
}

void PmergeMe::validationTransformContainers(int argc, const char *argv[]) {
  std::string temp;
  unsigned long num;
  char *str_end;

  for (int i = 1; i < argc; i++) {
    std::stringstream ss(argv[i]);

    while (ss >> temp) {
      errno = 0;
      num = std::strtoul(temp.c_str(), &str_end, 10);
      if (*str_end != '\0')
        throw std::runtime_error("Non-numeric Argument Error");

      if (errno == ERANGE || num <= 0 ||
          num > std::numeric_limits<unsigned int>::max())
        throw std::runtime_error("Argument Range Error");
      _vec.push_back(num);
      _lst.push_back(num);
      _deq.push_back(num);
      temp.clear();
    }
  }
  if (_vec.size() < 2) throw std::runtime_error("Argument Count Error");
}

bool PmergeMe::pairComparison(vector &numbers, size_t elementSize,
                              size_t pairCount) {
  vectorIt fir = numbers.begin();
  vectorIt sec;
  for (size_t i = 0; i < pairCount; i++) {
    sec = fir + elementSize;
    if (*fir < *sec)
      fir = std::swap_ranges(fir, sec, sec);
    else
      fir = sec + elementSize;
  }
  // Pair을 이루지 못한 element가 있는지 확인 -> 단, 현재 나의 elementSize 기준
  if (static_cast<size_t>(std::distance(fir, numbers.end())) >= elementSize)
    return true;
  else
    return false;
}

// Jacobsthal number의 사용이 필요함
void PmergeMe::pendingElementsInsertion(vector &numbers, bool upFlag,
                                        size_t elemSize, size_t pairCnt) {
  vector mainchains;
  vector pendingElem;
  vectorIt numbersIt = numbers.begin();
  vectorIt tempIt;

  mainchains.reserve(numbers.size());
  pendingElem.reserve(elemSize);
  for (size_t i = 0; i < pairCnt; i++) {
    tempIt = numbersIt + elemSize;
    mainchains.insert(mainchains.end(), numbersIt, tempIt);
    numbersIt = tempIt + elemSize;
    pendingElem.insert(pendingElem.end(), tempIt, numbersIt);
    binarySearchInsertion(mainchains, pendingElem, elemSize);
    pendingElem.clear();
  }
  if (upFlag) {
    tempIt = numbersIt;
    numbersIt += elemSize;
    pendingElem.insert(pendingElem.end(), tempIt, numbersIt);
    if (pendingElem.front() >= mainchains[mainchains.size() - elemSize])
      mainchains.insert(mainchains.end(), pendingElem.begin(),
                        pendingElem.end());
    else
      binarySearchInsertion(mainchains, pendingElem, elemSize);
  }
  if (numbersIt != numbers.end())
    mainchains.insert(mainchains.end(), numbersIt, numbers.end());
  numbers.swap(mainchains);
}

void PmergeMe::binarySearchInsertion(vector &mainchains, vector &pdElement,
                                     size_t elemSize) {
  size_t low = 0;
  size_t high = (mainchains.size() / elemSize) - 1;
  size_t mid;

  if (pdElement.front() <= mainchains.front()) {
    mainchains.insert(mainchains.begin(), pdElement.begin(), pdElement.end());
    return;
  }
  while (low + 1 < high) {
    mid = (low + high) / 2;
    if (mainchains[mid * elemSize] == pdElement.front()) {
      mainchains.insert(mainchains.begin() + (mid * elemSize),
                        pdElement.begin(), pdElement.end());
      return;
    } else if (mainchains[mid * elemSize] > pdElement.front())
      high = mid;
    else
      low = mid;
  }
  mainchains.insert(mainchains.begin() + (high * elemSize), pdElement.begin(),
                    pdElement.end());
}

// vector와 차이점 : std::advance ( + oprator overloading이 없음)
bool PmergeMe::pairComparison(list &numbers, size_t elementSize,
                              size_t pairCount) {
  listIt fir = numbers.begin();
  listIt sec;
  for (size_t i = 0; i < pairCount; i++) {
    sec = fir;
    std::advance(sec, elementSize);
    if (*fir < *sec)
      fir = std::swap_ranges(fir, sec, sec);
    else {
      fir = sec;
      std::advance(fir, elementSize);
    }
  }
  // Pair을 이루지 못한 element가 있는지 확인 -> 단, 현재 나의 elementSize 기준
  if (static_cast<size_t>(std::distance(fir, numbers.end())) >= elementSize)
    return true;
  else
    return false;
}

// vector와 차이점 : std::advance, splice, Jacobsthal number의 사용이 필요함
void PmergeMe::pendingElementsInsertion(list &numbers, bool upFlag,
                                        size_t elemSize, size_t pairCnt) {
  list mainchains;
  list pendingElem;
  listIt tempIt;

  for (size_t i = 0; i < pairCnt; i++) {
    tempIt = numbers.begin();
    std::advance(tempIt, elemSize);
    mainchains.splice(mainchains.end(), numbers, numbers.begin(), tempIt);
    tempIt = numbers.begin();
    std::advance(tempIt, elemSize);
    pendingElem.splice(pendingElem.end(), numbers, numbers.begin(), tempIt);
    binarySearchInsertion(mainchains, pendingElem, elemSize);
  }
  if (upFlag) {
    tempIt = numbers.begin();
    std::advance(tempIt, elemSize);
    pendingElem.splice(pendingElem.end(), numbers, numbers.begin(), tempIt);
    tempIt = mainchains.end();
    std::advance(tempIt, -elemSize);
    if (pendingElem.front() >= *tempIt)
      mainchains.splice(mainchains.end(), pendingElem);
    else
      binarySearchInsertion(mainchains, pendingElem, elemSize);
  }
  numbers.splice(numbers.begin(), mainchains);
}

// vector와 차이점 : std::advance, splice member function
void PmergeMe::binarySearchInsertion(list &lgElements, list &pdElement,
                                     size_t elemSize) {
  size_t low = 0;
  size_t high = (lgElements.size() / elemSize) - 1;
  size_t mid;
  listIt lowIt = lgElements.begin();
  listIt highIt = lgElements.end();
  listIt tempIt;

  if (pdElement.front() <= lgElements.front()) {
    lgElements.splice(lgElements.begin(), pdElement);
    return;
  }
  std::advance(highIt, -elemSize);
  while (low + 1 < high) {
    mid = (low + high) / 2;
    if (mid - low <= high - mid) {
      tempIt = lowIt;
      std::advance(tempIt, (mid - low) * elemSize);
    } else {
      tempIt = highIt;
      std::advance(tempIt, (mid - high) * elemSize);
    }
    if (*tempIt == pdElement.front()) {
      lgElements.splice(tempIt, pdElement);
      return;
    } else if (*tempIt > pdElement.front()) {
      high = mid;
      highIt = tempIt;
    } else {
      low = mid;
      lowIt = tempIt;
    }
  }
  lgElements.splice(highIt, pdElement);
}

// vector와 차이점 : 없음
bool PmergeMe::pairComparison(deque &numbers, size_t elementSize,
                              size_t pairCount) {
  dequeIt fir = numbers.begin();
  dequeIt sec;
  for (size_t i = 0; i < pairCount; i++) {
    sec = fir + elementSize;
    if (*fir < *sec)
      fir = std::swap_ranges(fir, sec, sec);
    else
      fir = sec + elementSize;
  }
  // Pair을 이루지 못한 element가 있는지 확인 -> 단, 현재 나의 elementSize 기준
  if (static_cast<size_t>(std::distance(fir, numbers.end())) >= elementSize)
    return true;
  else
    return false;
}

// vector와 차이점 : 없음, Jacobsthal number의 사용이 필요함
void PmergeMe::pendingElementsInsertion(deque &numbers, bool upFlag,
                                        size_t elemSize, size_t pairCnt) {
  deque mainchains;
  deque pendingElem;
  dequeIt numbersIt = numbers.begin();
  dequeIt tempIt;

  for (size_t i = 0; i < pairCnt; i++) {
    tempIt = numbersIt + elemSize;
    mainchains.insert(mainchains.end(), numbersIt, tempIt);
    numbersIt = tempIt + elemSize;
    pendingElem.insert(pendingElem.end(), tempIt, numbersIt);
    binarySearchInsertion(mainchains, pendingElem, elemSize);
    pendingElem.clear();
  }
  if (upFlag) {
    tempIt = numbersIt;
    numbersIt += elemSize;
    pendingElem.insert(pendingElem.end(), tempIt, numbersIt);
    if (pendingElem.front() >= mainchains[mainchains.size() - elemSize])
      mainchains.insert(mainchains.end(), pendingElem.begin(),
                        pendingElem.end());
    else
      binarySearchInsertion(mainchains, pendingElem, elemSize);
  }
  if (numbersIt != numbers.end())
    mainchains.insert(mainchains.end(), numbersIt, numbers.end());
  numbers.swap(mainchains);
}

// vector와 차이점 : 없음
void PmergeMe::binarySearchInsertion(deque &mainchains, deque &pdElement,
                                     size_t elemSize) {
  size_t low = 0;
  size_t high = (mainchains.size() / elemSize) - 1;
  size_t mid;

  if (pdElement.front() <= mainchains.front()) {
    mainchains.insert(mainchains.begin(), pdElement.begin(), pdElement.end());
    return;
  }
  while (low + 1 < high) {
    mid = (low + high) / 2;
    if (mainchains[mid * elemSize] == pdElement.front()) {
      mainchains.insert(mainchains.begin() + (mid * elemSize),
                        pdElement.begin(), pdElement.end());
      return;
    } else if (mainchains[mid * elemSize] > pdElement.front())
      high = mid;
    else
      low = mid;
  }
  mainchains.insert(mainchains.begin() + (high * elemSize), pdElement.begin(),
                    pdElement.end());
}