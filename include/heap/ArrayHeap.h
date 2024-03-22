#ifndef ARRAY_HEAP_H
#define ARRAY_HEAP_H

#include <cstddef>
#include <functional>
#include <optional>
#include <vector>
template <typename T, typename Compare = std::less<T>>
class ArrayHeap {
 private:
  std::vector<T> array;
  size_t size = 0;
  void heapify(size_t rootIndex);

 public:
  ArrayHeap() = default;
  ArrayHeap(size_t capacity);
  ArrayHeap(const ArrayHeap<T, Compare> &other) = default;
  ArrayHeap &operator=(const ArrayHeap<T, Compare> &other) = default;
  ArrayHeap(ArrayHeap<T, Compare> &&other) = default;
  ArrayHeap &operator=(ArrayHeap<T, Compare> &&other) = default;
  ~ArrayHeap() = default;
  [[nodiscard]] size_t parentIndex(size_t index) const;
  [[nodiscard]] size_t leftChildIndex(size_t index) const;
  [[nodiscard]] size_t rightChildIndex(size_t index) const;
  void insert(const T &element);
  std::optional<T> pop();
};

template <typename T, typename Compare>
ArrayHeap<T, Compare>::ArrayHeap(size_t capacity) {
  this->array = std::vector<T>();
  this->array.resize(capacity);
}

template <typename T, typename Compare>
size_t ArrayHeap<T, Compare>::parentIndex(size_t index) const {
  return (index - 1) / 2;
}

template <typename T, typename Compare>
size_t ArrayHeap<T, Compare>::leftChildIndex(size_t index) const {
  return 2 * index + 1;
}

template <typename T, typename Compare>
size_t ArrayHeap<T, Compare>::rightChildIndex(size_t index) const {
  return 2 * index + 2;
}

template <typename T, typename Compare>
void ArrayHeap<T, Compare>::insert(const T &element) {
  if (this->array.capacity() == this->size) {
    this->array.reserve(this->size * 2);
  }
  size_t index = this->size - 1;
  this->array.emplace(this->size, element);
  this->size++;
  Compare comparator;
  while (index != 0 &&
         comparator(this->array[parentIndex(index)], this->array[index])) {
    std::swap(this->array[parentIndex(index)], this->array[index]);
    index = parentIndex(index);
  }
}

template <typename T, typename Compare>
std::optional<T> ArrayHeap<T, Compare>::pop() {
  if (this->size() <= 0) {
    return {};
  }
  if (this->size() == 1) {
    this->size--;
    return this->array[0];
  }
  T root = this->array[0];
  this->array[0] = this->array[this->size - 1];
  this->size--;
  heapify(0);
  return root;
}

template <typename T, typename Compare>
void ArrayHeap<T, Compare>::heapify(size_t rootIndex) {
  size_t left = leftChildIndex(rootIndex);
  size_t right = rightChildIndex(rootIndex);
  size_t top = rootIndex;
  Compare comparator;
  if (left < this->size && comparator(this->array[top], this->array[left])) {
    top = left;
  }
  if (right < this->size && comparator(this->array[top], this->array[right])) {
    top = right;
  }
  if (top != rootIndex) {
    std::swap(this->array[rootIndex], this->array[top]);
    heapify(top);
  }
}

#endif  //! ARRAY_HEAP_H