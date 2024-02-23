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

void PmergeMe::mergeDeque(std::deque<int>& left, std::deque<int>& right,
                          std::deque<int>& result) {
  while (!left.empty() && !right.empty()) {
    if (left.front() < right.front()) {
      result.push_back(left.front());
      left.pop_front();
    } else {
      result.push_back(right.front());
      right.pop_front();
    }
  }

  // 남은 요소들을 추가
  while (!left.empty()) {
    result.push_back(left.front());
    left.pop_front();
  }
  while (!right.empty()) {
    result.push_back(right.front());
    right.pop_front();
  }
}

void PmergeMe::mergeVector(std::vector<int>& arr, int left, int middle,
                           int right) {
  std::vector<int> leftArr(arr.begin() + left, arr.begin() + middle + 1);
  std::vector<int> rightArr(arr.begin() + middle + 1, arr.begin() + right + 1);

  int leftSize = middle - left + 1;
  int rightSize = right - middle;

  int i = 0, j = 0, k = left;
  while (i < leftSize && j < rightSize) {
    if (leftArr[i] <= rightArr[j]) {
      arr[k] = leftArr[i];
      i++;
    } else {
      arr[k] = rightArr[j];
      j++;
    }
    k++;
  }

  // 남은 요소들을 추가
  while (i < leftSize) {
    arr[k] = leftArr[i];
    i++;
    k++;
  }
  while (j < rightSize) {
    arr[k] = rightArr[j];
    j++;
    k++;
  }
}

// 병합 정렬 함수
void PmergeMe::mergeSort(std::deque<int>& arr) {
  if (arr.size() <= 1) return;

  std::deque<int> left, right, result;
  int middle = arr.size() / 2;

  // 원본 배열을 절반으로 분할
  for (int i = 0; i < middle; ++i) left.push_back(arr[i]);
  for (int i = middle; i < arr.size(); ++i) right.push_back(arr[i]);

  // 각 부분 리스트를 재귀적으로 정렬
  mergeSort(left);
  mergeSort(right);

  // 정렬된 부분 리스트를 병합
  mergeDeque(left, right, result);
  arr = result;  // 결과를 원본 배열에 복사
}

void PmergeMe::mergeSort(std::vector<int>& arr, int left, int right) {
  if (left < right) {
    int middle = left + (right - left) / 2;

    // 분할
    mergeSort(arr, left, middle);
    mergeSort(arr, middle + 1, right);

    // 병합
    mergeVector(arr, left, middle, right);
  }
}