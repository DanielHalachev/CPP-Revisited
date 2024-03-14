#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
template <typename T>
class SinglyLinkedList {
 private:
  struct ListNode {
    T value;
    ListNode *next;
    ListNode(const T &value, ListNode *next = nullptr)
        : value(value), next(next) {}
  };
  ListNode *head = nullptr;
  ListNode *tail = nullptr;
  size_t size = 0;

  void free();

 public:
  class Iterator {
   private:
    ListNode *current;

   public:
    Iterator(ListNode *node) : current(node) {}

    Iterator &operator++() {
      this->current = this->current->next;
      return *this;
    }

    bool operator!=(const Iterator &other) const {
      return this->current != other.current;
    }

    T &operator*() const { return this->current->value; }
  };
  SinglyLinkedList();
  SinglyLinkedList(size_t size, const T &value);
  SinglyLinkedList(const std::initializer_list<T> &initList);
  SinglyLinkedList(const SinglyLinkedList &other);
  SinglyLinkedList &operator=(const SinglyLinkedList &other);
  SinglyLinkedList(SinglyLinkedList &&other) noexcept;
  SinglyLinkedList &operator=(SinglyLinkedList &&other) noexcept;
  ~SinglyLinkedList();
  [[nodiscard]] size_t getSize() const;
  void pushFront(const T &value);
  void pushBack(const T &value);
  void popFront();
  T erase(size_t index);
  T operator[](size_t index) const;
  T &operator[](size_t index);
  Iterator begin();
  Iterator end();
  Iterator begin() const;
  Iterator end() const;
  template <typename S>
  friend std::ostream &operator<<(std::ostream &outputStream,
                                  const SinglyLinkedList<S> &list);
};

template <typename T>
void SinglyLinkedList<T>::free() {
  ListNode *next = nullptr;
  while (head != nullptr) {
    next = head->next;
    delete head;
    head = next;
  }
  this->tail = nullptr;
  this->size = 0;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList() {
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(size_t size, const T &value) {
  for (size_t i = 0; i < size; i++) {
    pushBack(value);
  }
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(
    const std::initializer_list<T> &initList) {
  for (auto &element : initList) {
    pushBack(element);
  }
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList &other) {
  if (other.head != nullptr) {
    ListNode *otherNode = other.head;
    this->head = new ListNode(otherNode->value, nullptr);
    ListNode *previous = this->head;

    otherNode = otherNode->next;

    while (otherNode != nullptr) {
      previous->next = new ListNode(otherNode->value, nullptr);
      previous = previous->next;
      otherNode = otherNode->next;
    }
    this->tail = previous;
  }
  this->size = other.size;
}

template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(
    const SinglyLinkedList<T> &other) {
  if (this != &other) {
    free();
    if (other.head != nullptr) {
      ListNode *otherNode = other.head;
      this->head = new ListNode(otherNode->value, nullptr);
      ListNode *previous = head;

      otherNode = otherNode->next;

      while (otherNode != nullptr) {
        previous->next = new ListNode(otherNode->value, nullptr);
        previous = previous->next;
        otherNode = otherNode->next;
      }
      this->tail = previous;
    }
    this->size = other.size;
  }
  return *this;
}

template <typename T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T> &&other) noexcept {
  this->size = other.size;
  this->head = other.head;
  this->tail = other.tail;

  other.size = 0;
  other.head = nullptr;
  other.tail = nullptr;
}

template <typename T>
SinglyLinkedList<T> &SinglyLinkedList<T>::operator=(
    SinglyLinkedList<T> &&other) noexcept {
  if (this != &other) {
    free();
    this->size = other.size;
    this->head = other.head;
    this->tail = other.tail;

    other.size = 0;
    other.head = nullptr;
    other.tail = nullptr;
  }
  return *this;
}

template <typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
  free();
}

template <typename T>
[[nodiscard]] size_t SinglyLinkedList<T>::getSize() const {
  return this->size;
}

template <typename T>
void SinglyLinkedList<T>::pushFront(const T &value) {
  if (head == nullptr) {
    this->head = new ListNode(value, nullptr);
    this->tail = this->head;
  } else {
    auto temp = new ListNode(value, this->head);
    this->head = temp;
  }
  this->size++;
}

template <typename T>
void SinglyLinkedList<T>::pushBack(const T &value) {
  if (this->tail == nullptr) {
    this->tail = new ListNode(value, nullptr);
    this->head = this->tail;
  } else {
    auto temp = new ListNode(value, nullptr);
    this->tail->next = temp;
    this->tail = temp;
  }
  this->size++;
}

template <typename T>
void SinglyLinkedList<T>::popFront() {
  if (this->head != nullptr) {
    ListNode *temp = this->head;
    this->head = this->head->next;
    delete temp;
    this->size--;
  }
  if (this->head == nullptr) {
    this->tail = nullptr;
  }
}

template <typename T>
T SinglyLinkedList<T>::erase(size_t index) {
  if (index >= this->size) {
    throw std::out_of_range("Invalid index for deletion");
  }
  if (index == 0) {
    T temp = this->head->value;
    popFront();
    return temp;
  }
  ListNode *iterator = this->head;
  for (int i = 0; i < index - 1; i++) {
    iterator = iterator->next;
  }
  ListNode *prev = iterator;
  iterator = iterator->next;
  T temp = iterator->value;
  prev->next = iterator->next;
  if (prev->next == nullptr) {
    this->tail = prev;
  }
  delete iterator;
  this->size--;
  return temp;
}

template <typename T>
T SinglyLinkedList<T>::operator[](size_t index) const {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  ListNode *toBeReturned = this->head;
  for (int i = 0; i < index; i++) {
    toBeReturned = toBeReturned->next;
  }
  return toBeReturned->value;
}

template <typename T>
T &SinglyLinkedList<T>::operator[](size_t index) {
  if (index >= this->size) {
    throw std::out_of_range("Index out of range");
  }
  ListNode *toBeReturned = this->head;
  for (int i = 0; i < index; i++) {
    toBeReturned = toBeReturned->next;
  }

  return toBeReturned->value;
}

template <typename T>
SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() {
  return Iterator(this->head);
}

template <typename T>
SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() {
  return Iterator(nullptr);
}

template <typename T>
SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::begin() const {
  return Iterator(this->head);
}

template <typename T>
SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end() const {
  return Iterator(nullptr);
}

template <typename T>
std::ostream &operator<<(std::ostream &outputStream,
                         const SinglyLinkedList<T> &list) {
  for (auto num : list) {
    outputStream << num << " ";
  }
  return outputStream;
}
#endif  // !SINGLY_LINKED_LIST_H
