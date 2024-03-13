#ifndef SORTING_H
#define SORTING_H

#include <algorithm>
#include <vector>

template <typename T>
void bubbleSort(std::vector<T> &toBeSorted) {
  for (int i = 0; i < toBeSorted.size(); i++) {
    for (int j = 0; j < toBeSorted.size() - i - 1; j++) {
      if (toBeSorted[j] > toBeSorted[j + 1]) {
        std::swap(toBeSorted[j], toBeSorted[j + 1]);
      }
    }
  }
}

template <typename T>
void alternativeBubbleSort(std::vector<T> &toBeSorted) {
  for (int i = 0; i < toBeSorted.size(); i++) {
    for (int j = i + 1; j < toBeSorted.size(); j++) {
      if (toBeSorted[i] > toBeSorted[j]) {
        std::swap(toBeSorted[i], toBeSorted[j]);
      }
    }
  }
}

template <typename T>
void selectionSort(std::vector<T> &array) {
  for (int selection = 0; selection < array.size(); selection++) {
    size_t minIndex = selection;
    for (int j = selection; j < array.size(); j++) {
      if (array[j] < array[minIndex]) {
        minIndex = j;
      }
    }
    std::swap(array[selection], array[minIndex]);
  }
}

template <typename T>
void insertionSort(std::vector<T> &toBeSorted) {
  for (size_t i = 1; i < toBeSorted.size(); i++) {
    T unsorted = toBeSorted[i];
    size_t j = i - 1;
    while (toBeSorted[j] > unsorted && j >= 0) {
      toBeSorted[j + 1] = toBeSorted[j];
      j--;
    }
    // in case the cycle isn't executed, j+1 should be equal to i
    // in order to preserve the order,as it is correct
    toBeSorted[j + 1] = unsorted;
  }
}

template <typename T>
void mergeInPlace(std::vector<T> &array, size_t leftIncl, size_t middle,
                  size_t rightIncl) {
  size_t leftIndex = leftIncl;  // the first in the left to be put in its place
  size_t rightIndex =
      middle + 1;  // the first in the right to be put in its place

  while (leftIndex <= middle && rightIndex <= rightIncl) {
    if (array[leftIndex] <= array[rightIndex]) {
      leftIndex++;
    } else {
      size_t tempIndex = rightIndex;
      T temp = array[rightIndex];
      while (tempIndex != leftIndex) {
        array[tempIndex] = array[tempIndex - 1];
        tempIndex--;
      }
      array[leftIndex] = temp;
      middle++;
      leftIndex++;
      rightIndex++;
    }
  }
}

template <typename T>
void merge(std::vector<T> &array, size_t leftIncl, size_t middle,
           size_t rightIncl) {
  size_t leftIndex = 0;
  size_t rightIndex = 0;
  size_t index = leftIncl;

  std::vector<T> leftArray(array.begin() + leftIncl,
                           array.begin() + middle + 1);
  std::vector<T> rightArray(array.begin() + middle + 1,
                            array.begin() + rightIncl + 1);

  while (leftIndex < leftArray.size() && rightIndex < rightArray.size()) {
    if (leftArray[leftIndex] <= rightArray[rightIndex]) {
      array[index] = leftArray[leftIndex];
      leftIndex++;
    } else {
      array[index] = rightArray[rightIndex];
      rightIndex++;
    }
    index++;
  }

  while (leftIndex < leftArray.size()) {
    array[index] = leftArray[leftIndex];
    leftIndex++;
    index++;
  }

  while (rightIndex < rightArray.size()) {
    array[index] = rightArray[rightIndex];
    rightIndex++;
    index++;
  }
}

template <typename T>
void mergeSort(std::vector<T> &array, size_t leftIncl, size_t rightIncl) {
  if (rightIncl >= array.size()) {
    rightIncl = array.size() - 1;
  }
  if (leftIncl < 0) {
    leftIncl = 0;
  }
  if (leftIncl < rightIncl) {
    size_t mid = leftIncl + (rightIncl - leftIncl) / 2;
    mergeSort(array, leftIncl, mid);
    mergeSort(array, mid + 1, rightIncl);
    mergeInPlace(array, leftIncl, mid, rightIncl);
    // merge(array, leftIncl, mid, rightIncl);
  }
}

template <class T>
T medianOfThree(std::vector<T> &array, size_t leftIncl, size_t rightIncl) {
  size_t mid = leftIncl + (rightIncl - leftIncl) / 2;
  if (array[mid] < array[leftIncl]) {
    std::swap(array[mid], array[leftIncl]);
  }
  if (array[rightIncl] < array[leftIncl]) {
    std::swap(array[rightIncl], array[leftIncl]);
  }
  if (array[rightIncl] < array[mid]) {
    std::swap(array[rightIncl], array[mid]);
  }
  return array[mid];
}

template <typename T>
size_t pivot(std::vector<T> &array, size_t leftIncl, size_t rightIncl,
             bool useMedianOfThree = false) {
  size_t pivotIndex = leftIncl;
  T pivot = (useMedianOfThree ? medianOfThree(array, leftIncl, rightIncl)
                              : array[pivotIndex]);
  size_t i = leftIncl - 1;
  size_t j = rightIncl + 1;
  while (true) {
    while (array[++i] < pivot) {
    }
    while (array[--j] > pivot) {
    }
    if (i >= j) {
      return j;
    }
    std::swap(array[i], array[j]);
  }
  return pivotIndex;
}

template <typename T>
size_t easyPivot(std::vector<T> &array, size_t leftIncl, size_t rightIncl) {
  T pivot = array[rightIncl];
  size_t index = leftIncl;  // index of smaller element
  for (size_t i = leftIncl; i < rightIncl; i++) {
    if (array[i] <= pivot) {
      std::swap(array[i], array[index]);
      index++;
    }
  }
  std::swap(array[index], array[rightIncl]);
  return index;
}

template <typename T>
void quickSort(std::vector<T> &array, size_t left, size_t right,
               bool useMedianOfThree = false) {
  if (left >= right || left < 0 || right >= array.size()) {
    return;
  }
  size_t pivotIndex = pivot(array, left, right, useMedianOfThree);
  // size_t pivotIndex = easyPivot(array, left, right);
  if (useMedianOfThree) {
    quickSort(array, left, pivotIndex);
  } else {
    quickSort(array, left, pivotIndex - 1);
  }
  quickSort(array, pivotIndex + 1, right);
}

void countingSort(std::vector<int> &array) {
  std::vector<int> copy(array);
  int max = *std::max_element(array.begin(), array.end());
  std::vector<int> occurences(max + 1, 0);
  for (auto &num : array) {
    occurences[num]++;
  }

  for (int i = 1; i <= max; i++) {
    occurences[i] += occurences[i - 1];
  }

  for (auto i = copy.rbegin(); i != copy.rend(); ++i) {
    array[occurences[*i] - 1] = *i;
    occurences[*i]--;
  }
}

#endif  // SORTING_H
