#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <stdexcept>

#define DEFAULT_CAPACITY 16
template <typename T>
class Vector {
  protected:
    T* array = nullptr;
    size_t size = 0;
    size_t capacity = DEFAULT_CAPACITY;
  public:
    Vector();
    Vector(size_t capacity);
    Vector(size_t size, const T &value);
    Vector(const Vector<T> &other);
    Vector& operator=(const Vector<T> &other);
    ~Vector();
    size_t pushBack(const T &value);
    T erase(size_t index);
    bool resize(size_t newSize);
    [[nodiscard]] size_t getSize() const;
    [[nodiscard]] size_t getCapacity() const;
    T operator[] (size_t index) const;
    T& operator[] (size_t index);

};

template <typename T>
Vector<T>::Vector() {
  this->size = 0;
  this->capacity = DEFAULT_CAPACITY;
  this->array = new T[this->capacity];
}

template <typename T>
Vector<T>::Vector(size_t capacity){
  this->size = 0;
  this->capacity = capacity;
  this->array = new T [this->capacity];
}

template <typename T>
Vector<T>::Vector(size_t size, const T&value){
  this->size = size;
  this->capacity = 2 * size;
  this->array = new T [this->capacity];
  for (size_t i = 0; i<this->size; i++){
    this->array[i] = value;
  }
}

template <typename T>
Vector<T>::Vector(const Vector &other){
  this->size = other.size;
  this->capacity = other.capacity;
  this->array = new T[this->capacity];
  for(size_t i = 0; i < this->size; i++){
    this->array[i] = other.array[i];
  }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T> &other){
  if (this != &other){
    delete[] this->array;

    this->size = other.size;
    this->capacity = other.capacity;

    this->array = new T[this->capacity];
    for(size_t i = 0; i < this->size; i++){
      this->array[i] = other.array[i];
    }
  }
  return *this;
}

template <typename T>
Vector<T>::~Vector() {
  delete [] this->array;
}

template <typename T>
size_t Vector<T>::pushBack(const T &value) {
  if (this->size == this->capacity){
    this->resize(2*this->capacity);
  }
  this->array[this->size] = value;
  this->size ++;
  return this->size - 1;
}

template <typename T>
T Vector<T>::erase(size_t index) {
  if (index < 0 || index >= this->size){
    throw std::out_of_range("Provided index is out of range");
  }
  T temp = this->array[index];
  for(size_t i = index; i<this->size - 1; i++){
    this->array[i] = this->array[i+1];
  }
  this->size --;
  return temp;
}

template <typename T>
bool Vector<T>::resize(size_t newSize){
  if (newSize < 0) {
    throw std::out_of_range("Invalid new size");
  }
  this->capacity = newSize;
  this->size = std::min(this->size, this->capacity);
  T* newArray = new T[this->capacity];
  for(size_t i = 0; i < this->size; i++){
    newArray[i] = this->array[i];
  }
  delete[] this->array;
  this->array = newArray;
  return true;
}

template <typename T>
T Vector<T>::operator[](size_t index) const{
  if (index < 0 || index >= this->size) {
    throw std::out_of_range("Invalid range of element");
  }
  return this->array[index];
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
  if (index < 0 || index >= this->size) {
    throw std::out_of_range("Invalid range of element");
  }
  return this->array[index];
}

template <typename T>
size_t Vector<T>::getSize() const{
  return this->size;
}

template <typename T>
size_t Vector<T>::getCapacity() const{
  return this->capacity;
}

#endif // !VECTOR_H
