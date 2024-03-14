#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cstddef>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
template <typename T>
class DoublyLinkedList {
 private:
  struct ListNode {
    T value;
    ListNode *previous;
    ListNode *next;
    ListNode(const T &value, ListNode *previous = nullptr,
             ListNode *next = nullptr)
        : value(value), previous(previous), next(next) {}
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
  DoublyLinkedList();
  DoublyLinkedList(size_t size, const T &value);
  DoublyLinkedList(const std::initializer_list<T> &initList);
  DoublyLinkedList(const DoublyLinkedList &other);
  DoublyLinkedList &operator=(const DoublyLinkedList &other);
  DoublyLinkedList(DoublyLinkedList &&other) noexcept;
  DoublyLinkedList &operator=(DoublyLinkedList &&other) noexcept;
  ~DoublyLinkedList();
  [[nodiscard]] size_t getSize() const;
  void pushFront(const T &value);
  void pushBack(const T &value);
  void popFront();
  void popBack();
  T erase(size_t index);
  T operator[](size_t index) const;
  T &operator[](size_t index);
  Iterator begin();
  Iterator end();
  Iterator begin() const;
  Iterator end() const;
  template <typename S>
  friend std::ostream &operator<<(std::ostream &outputStream,
                                  const DoublyLinkedList<S> &list);
};

template <typename T>
void DoublyLinkedList<T>::free() {
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
DoublyLinkedList<T>::DoublyLinkedList() {
  this->head = nullptr;
  this->tail = nullptr;
  this->size = 0;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(size_t size, const T &value) {
  for (size_t i = 0; i < size; i++) {
    pushBack(value);
  }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(
    const std::initializer_list<T> &initList) {
  for (auto &element : initList) {
    pushBack(element);
  }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &other) {
  if (other.head != nullptr) {
    ListNode *otherNode = other.head;
    this->head = new ListNode(otherNode->value, nullptr, nullptr);
    ListNode *previous = this->head;
    ListNode *currentNode = nullptr;

    otherNode = otherNode->next;

    while (otherNode != nullptr) {
      currentNode = new ListNode(otherNode->value, previous, nullptr);
      previous->next = currentNode;
      previous = previous->next;
      otherNode = otherNode->next;
    }
    this->tail = previous;
  }
  this->size = other.size;
}

template <typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(
    const DoublyLinkedList<T> &other) {
  if (this != &other) {
    free();
    if (other.head != nullptr) {
      ListNode *otherNode = other.head;
      this->head = new ListNode(otherNode->value, nullptr, nullptr);
      ListNode *previous = head;
      ListNode *currentNode = nullptr;

      otherNode = otherNode->next;

      while (otherNode != nullptr) {
        currentNode = new ListNode(otherNode->value, previous, nullptr);
        previous->next = currentNode;
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
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T> &&other) noexcept {
  this->size = other.size;
  this->head = other.head;
  this->tail = other.tail;

  other.size = 0;
  other.head = nullptr;
  other.tail = nullptr;
}

template <typename T>
DoublyLinkedList<T> &DoublyLinkedList<T>::operator=(
    DoublyLinkedList<T> &&other) noexcept {
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
DoublyLinkedList<T>::~DoublyLinkedList() {
  free();
}

template <typename T>
[[nodiscard]] size_t DoublyLinkedList<T>::getSize() const {
  return this->size;
}

template <typename T>
void DoublyLinkedList<T>::pushFront(const T &value) {
  if (head == nullptr) {
    this->head = new ListNode(value, nullptr, nullptr);
    this->tail = this->head;
  } else {
    auto temp = new ListNode(value, nullptr, this->head);
    head->previous = temp;
    this->head = temp;
  }
  this->size++;
}

template <typename T>
void DoublyLinkedList<T>::pushBack(const T &value) {
  if (this->tail == nullptr) {
    this->tail = new ListNode(value, nullptr, nullptr);
    this->head = this->tail;
  } else {
    auto temp = new ListNode(value, this->tail, nullptr);
    this->tail->next = temp;
    this->tail = temp;
  }
  this->size++;
}

template <typename T>
void DoublyLinkedList<T>::popFront() {
  if (this->head != nullptr) {
    ListNode *temp = this->head;
    this->head = this->head->next;
    if (this->head) {
      this->head->previous = nullptr;
    }
    delete temp;
    this->size--;
  }
  if (this->head == nullptr) {
    this->tail = nullptr;
  }
}

template <typename T>
void DoublyLinkedList<T>::popBack() {
  if (this->tail != nullptr) {
    ListNode *temp = this->tail;
    this->tail = this->tail->previous;
    delete temp;
    if (this->tail) {
      this->tail->next = nullptr;
    }
    this->size--;
  }
  if (this->tail == nullptr) {
    this->head = nullptr;
  }
}

template <typename T>
T DoublyLinkedList<T>::erase(size_t index) {
  if (index >= this->size) {
    throw std::out_of_range("Invalid index for deletion");
  }
  ListNode *toBeErased = this->head;
  for (int i = 0; i < index; i++) {
    toBeErased = toBeErased->next;
  }
  if (toBeErased != this->head) {
    toBeErased->previous->next = toBeErased->next;
  } else {
    this->head = toBeErased->next;
  }
  if (toBeErased != this->tail) {
    toBeErased->next->previous = toBeErased->previous;
  } else {
    this->tail = toBeErased->previous;
  }
  T temp = toBeErased->value;
  delete toBeErased;
  this->size--;
  return temp;
}

template <typename T>
T DoublyLinkedList<T>::operator[](size_t index) const {
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
T &DoublyLinkedList<T>::operator[](size_t index) {
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
DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() {
  return Iterator(this->head);
}

template <typename T>
DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() {
  return Iterator(nullptr);
}

template <typename T>
DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::begin() const {
  return Iterator(this->head);
}

template <typename T>
DoublyLinkedList<T>::Iterator DoublyLinkedList<T>::end() const {
  return Iterator(nullptr);
}

template <typename T>
std::ostream &operator<<(std::ostream &outputStream,
                         const DoublyLinkedList<T> &list) {
  for (auto num : list) {
    outputStream << num << " ";
  }
  return outputStream;
}
#endif  // !DOUBLY_LINKED_LIST_H
