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

void rearrangePairs(std::deque<int>& dq, size_t gap) {
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

  // gap을 크기로 덩어리를 나눠서 짝수는 main 덩어리, 홀수는 sub 덩어리로 나눠서
  // 정렬 mainchain에 subchain을 넣어서 정렬 (Jacobsthal number사용) erase,
  // insert 사용
}

void rearrangePairs(std::vector<int>& vc, size_t gap) {
  if (gap < 0 || gap * 2 > vc.size()) return;

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

  std::vector<int> sub_vc;

  // subchain 생성
  for (size_t i = 0; i < vc.size(); i += gap * 2) {
    // 홀수만 sub_vc에 insert로 넣기
    sub_vc.insert(sub_vc.end(), vc.begin() + i + gap, vc.begin() + i + gap * 2);

    // mainchain에서 subchain을 erase로 제거
    vc.erase(vc.begin() + i + gap, vc.begin() + i + gap * 2);
  }

  for (size_t i = 0; i < sub_vc.size() / gap; i++) {
    std::cout << "index: " << i << std::endl;
    unsigned int index = jacobsthalNumberAtIndex(i, sub_vc.size() / gap);

    vc.insert(vc.begin() + binarySearch(vc, sub_vc[index * gap], 0,
                                        (index + i) * gap, gap),
              sub_vc.begin() + index * gap, sub_vc.begin() + index * gap + gap);
  }
}

int binarySearch(std::vector<int>& vc, int target, int start, int end,
                 int gap) {
  if (start > end) return -1;

  int mid = (start + end) / 2;

  if (vc[mid] == target)
    return mid;
  else if (vc[mid] > target)
    return binarySearch(vc, target, start, mid - gap, gap);
  else
    return binarySearch(vc, target, mid + gap, end, gap);
}

unsigned int jacobsthal(unsigned int n) {
  if (n == 0) return 0;
  if (n == 1) return 1;
  return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}

bool checkJacobsthal(unsigned int n) {
  unsigned int i = 0;

  while (jacobsthal(i) < n) {
    i++;
  }

  return jacobsthal(i) == n;
}

unsigned int nextJacobsthal(unsigned int n) {
  unsigned int i = 0;

  while (jacobsthal(i) < n) {
    i++;
  }

  return jacobsthal(i);
}

unsigned int jacobsthalNumberAtIndex(unsigned int index, unsigned int size) {
  unsigned int result = 0;

  if (index == 0) return 0;
  if (index == 1) return 1;

  if (checkJacobsthal(index - 1)) {
    result = nextJacobsthal(index);
    if (result > size) return index;
    return result;
  };

  if (nextJacobsthal(index) > size) {
    result = index;
  } else {
    result = index - 1;
  }

  return result;
}
