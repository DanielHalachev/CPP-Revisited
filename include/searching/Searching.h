#ifndef SEARCHING_H
#define SEARCHING_H

#include <cmath>
#include <optional>
#include <vector>

template <typename T>
std::optional<size_t> linearSearch(const std::vector<T> &array,
                                   const T &element) {
  for (size_t i = 0; i < array.size(); i++) {
    if (array[i] == element) {
      return i;
    }
  }
  return {};
}

template <typename T>
std::optional<size_t> binarySearch(const std::vector<T> &array,
                                   const T &element, size_t left,
                                   size_t rightIncl) {
  if (left > rightIncl) {
    return {};
  }

  size_t mid = left + (rightIncl - left) / 2;
  if (array[mid] == element) {
    return mid;
  }

  if (element < array[mid]) {
    return binarySearch(array, element, left, mid - 1);
  }

  return binarySearch(array, element, mid + 1, rightIncl);
}

template <typename T>
std::optional<size_t> ternarySearch(const std::vector<T> &array,
                                    const T &element, size_t left,
                                    size_t rightIncl) {
  if (left > rightIncl) {
    return {};
  }
  size_t mid1 = left + (rightIncl - left) / 3;
  size_t mid2 = rightIncl - (rightIncl - left) / 3;

  if (array[mid1] == element) {
    return mid1;
  }

  if (array[mid2] == element) {
    return mid2;
  }

  if (element < array[mid1]) {
    return ternarySearch(array, element, left, mid1 - 1);
  }

  if (element < array[mid2]) {
    return ternarySearch(array, element, mid1 + 1, mid2 - 1);
  }

  return ternarySearch(array, element, mid2 + 1, rightIncl);
}

template <typename T>
std::optional<size_t> jumpSearch(const std::vector<T> &array,
                                 const T &element) {
  size_t root = sqrt(array.size());
  size_t step = root;
  size_t prev = 0;
  while (array[step] < element) {
    prev = step;
    step += root;
    if (prev >= array.size()) {
      return {};
    }
  }

  step = std::min(step, array.size());

  while (array[prev] < element) {
    prev++;
    if (prev == step) {
      return {};
    }
  }

  if (array[step] == element) {
    return step;
  }

  return {};
}

template <typename T>
size_t randomizedSelect(std::vector<T> &array, size_t left, size_t rightIncl) {
  T pivot = array[rightIncl];
  size_t index = left;
  for (size_t i = left; i < rightIncl; i++) {
    if (array[i] <= pivot) {
      std::swap(array[i], array[index]);
      index++;
    }
  }
  std::swap(array[index], array[rightIncl]);
  return index;
}

template <typename T>
std::optional<T> kThBiggest(std::vector<T> &array, size_t k, size_t left,
                            size_t rightIncl) {
  if (left == rightIncl) {
    return array[left];
  }
  size_t pivot = randomizedSelect(array, left, rightIncl);
  size_t arrangedElementIndex = array.size() - pivot;
  if (k == arrangedElementIndex) {
    return array[pivot];
  }
  if (k > arrangedElementIndex) {
    return kThBiggest(array, k, left, pivot - 1);
  }
  return kThBiggest(array, k, pivot + 1, rightIncl);
}

#endif  // !SEARCHING_H
