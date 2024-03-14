#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "searching/Searching.h"
#include "sorting/Sorting.h"
#include "vector/Vector.h"

template <typename T>
void testSorting(std::vector<T> &myVector) {
  for (auto num : myVector) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  // bubbleSort(myVector);
  // alternativeBubbleSort(myVector);
  // selectionSort(myVector);
  // insertionSort(myVector);
  // inPlaceMergeSort(myVector, 0, myVector.size());
  // standardMergeSort(myVector, 0, myVector.size() - 1);
  // quickSort(myVector, 0, myVector.size() - 1);
  countingSort(myVector);

  for (auto num : myVector) {
    std::cout << num << " ";
  }
}

template <typename T>
void testSearch(std::vector<T> &myVector) {
  quickSort(myVector, 0, myVector.size() - 1);
  for (auto num : myVector) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  // std::optional<size_t> index = linearSearch(myVector,
  // myVector[myVector.size() - 2]); std::optional<size_t> index =
  // binarySearch(myVector, myVector[myVector.size() - 2], 0, myVector.size() -
  // 1); std::optional<size_t> index = ternarySearch(myVector,
  // myVector[myVector.size() - 2], 0, myVector.size() - 1);
  std::optional<size_t> index =
      jumpSearch(myVector, myVector[myVector.size() - 2]);
  std::cout << "Index:"
            << (index.has_value() ? std::to_string(index.value()) : "Not found")
            << "\n";
}

int main() {
  // const size_t SIZE = 10;
  // std::vector<int> myVector;
  // myVector.resize(SIZE);
  // std::random_device randomDevice;
  // std::uniform_int_distribution<int> dist(1, SIZE);
  // for (int &num : myVector) {
  //   num = dist(randomDevice);
  // }

  // testSorting(myVector);
  // testSearch(myVector);

  Vector<int> myVec = {5,3,10};
  myVec.erase(1);

  Vector mySecondVec = myVec;
  std::cout<<mySecondVec << "\n";

  myVec.erase(0);
  myVec.erase(0);

  for (auto num : myVec){
    std::cout<<num << " ";
  }
  return 0;
}
