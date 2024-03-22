#include <catch2/catch_test_macros.hpp>
#define CATCH_CONFIG_MAIN
#include "Vector.h"

TEST_CASE("Vector tests") {
  SECTION("Default constructor initializes an empty vector") {
    Vector<int> vector;
    REQUIRE(vector.getSize() == 0);
    REQUIRE(vector.getCapacity() == DEFAULT_CAPACITY);
  }

  SECTION("Constructor with capacity initializes vector with given capacity") {
    size_t capacity = 20;
    Vector<int> vector(capacity);
    REQUIRE(vector.getSize() == 0);
    REQUIRE(vector.getCapacity() == capacity);
  }

  SECTION(
      "Constructor with size and value initializes vector with given size and "
      "value") {
    size_t size = 5;
    int value = 10;
    Vector<int> vector(size, value);
    REQUIRE(vector.getSize() == size);
    REQUIRE(vector.getCapacity() >= size);
    for (size_t i = 0; i < size; ++i) {
      REQUIRE(vector[i] == value);
    }
  }

  SECTION("Test Vector constructor with initializer list") {
    Vector<int> vector = {1, 2, 3, 4, 5};
    REQUIRE(vector.getSize() == 5);
    REQUIRE(vector.getCapacity() >= 5);
    for (size_t i = 0; i < vector.getSize(); ++i) {
      REQUIRE(vector[i] == i + 1);
    }
  }

  SECTION("Copy constructor creates a deep copy of the vector") {
    Vector<int> vector1(5, 10);
    Vector<int> vector2(vector1);
    REQUIRE(vector1.getSize() == vector2.getSize());
    REQUIRE(vector1.getCapacity() == vector2.getCapacity());
    for (size_t i = 0; i < vector1.getSize(); ++i) {
      REQUIRE(vector1[i] == vector2[i]);
    }
  }

  SECTION("Assignment operator performs deep copy of the vector") {
    Vector<int> vector1(5, 10);
    Vector<int> vector2;
    vector2 = vector1;
    REQUIRE(vector1.getSize() == vector2.getSize());
    REQUIRE(vector1.getCapacity() == vector2.getCapacity());
    for (size_t i = 0; i < vector1.getSize(); ++i) {
      REQUIRE(vector1[i] == vector2[i]);
    }
  }

  SECTION("Move constructor transfers ownership of data") {
    Vector<int> vector1(5, 10);
    Vector<int> vector2(std::move(vector1));
    REQUIRE(vector1.getSize() == 0);
    REQUIRE(vector1.getCapacity() == 0);
    REQUIRE(vector2.getSize() == 5);
    REQUIRE(vector2.getCapacity() >= 5);
    for (size_t i = 0; i < vector2.getSize(); ++i) {
      REQUIRE(vector2[i] == 10);
    }
  }

  SECTION("Move assignment operator transfers ownership of data") {
    Vector<int> vector1(5, 10);
    Vector<int> vector2;
    vector2 = std::move(vector1);
    REQUIRE(vector1.getSize() == 0);
    REQUIRE(vector1.getCapacity() == 0);
    REQUIRE(vector2.getSize() == 5);
    REQUIRE(vector2.getCapacity() >= 5);
    for (size_t i = 0; i < vector2.getSize(); ++i) {
      REQUIRE(vector2[i] == 10);
    }
  }

  SECTION("Pushing back increases size and possibly capacity") {
    Vector<int> vector;
    for (int i = 0; i < 20; ++i) {
      vector.pushBack(i);
      REQUIRE(vector.getSize() == i + 1);
      if (i + 1 > DEFAULT_CAPACITY) {
        REQUIRE(vector.getCapacity() >= i + 1);
      } else {
        REQUIRE(vector.getCapacity() == DEFAULT_CAPACITY);
      }
    }
    for (int i = 0; i < 20; ++i) {
      REQUIRE(vector[i] == i);
    }
  }

  SECTION("Erasing") {
    Vector<int> vector(5, 10);
    SECTION("Erasing element at valid index reduces size and shifts elements") {
      vector.erase(2);
      REQUIRE(vector.getSize() == 4);
      REQUIRE(vector[0] == 10);
      REQUIRE(vector[1] == 10);
      REQUIRE(vector[2] == 10);
      REQUIRE(vector[3] == 10);
    }

    SECTION("Erasing element at invalid index throws out_of_range exception") {
      REQUIRE_THROWS_AS(vector.erase(5), std::out_of_range);
    }
  }

  SECTION("Resizing changes the capacity and preserves existing elements") {
    Vector<int> vector(5, 10);
    vector.resize(10);
    REQUIRE(vector.getSize() == 5);
    REQUIRE(vector.getCapacity() == 10);
    for (size_t i = 0; i < 5; ++i) {
      REQUIRE(vector[i] == 10);
    }
  }

  SECTION(
      "Resizing to smaller size reduces capacity and preserves existing "
      "elements") {
    Vector<int> vector(10, 5);
    vector.resize(5);
    REQUIRE(vector.getSize() == 5);
    REQUIRE(vector.getCapacity() == 5);
    for (size_t i = 0; i < 5; ++i) {
      REQUIRE(vector[i] == 5);
    }
  }

  SECTION(
      "Accessing elements using subscript operator retrieves correct element") {
    Vector<int> vector(5, 10);
    for (size_t i = 0; i < vector.getSize(); ++i) {
      REQUIRE(vector[i] == 10);
    }
  }

  SECTION(
      "Accessing element at invalid index using subscript operator throws "
      "out_of_range exception") {
    Vector<int> vector(5, 10);
    REQUIRE_THROWS_AS(vector[vector.getSize()], std::out_of_range);
  }

  SECTION("Test begin() and end() functions for empty Vector") {
    Vector<int> vector;
    REQUIRE(vector.begin() == vector.end());
  }

  SECTION("Test begin() and end() functions for non-empty Vector") {
    Vector<int> vector = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (auto it = vector.begin(); it != vector.end(); ++it) {
      REQUIRE(*it == expected[i++]);
    }
  }

  SECTION("Test const begin() and end() functions for non-empty Vector") {
    const Vector<int> v = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (int it : v) {
      REQUIRE(it == expected[i++]);
    }
  }

  SECTION("Test range-based for loop for non-empty Vector") {
    Vector<int> v = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (auto num : v) {
      REQUIRE(num == expected[i++]);
    }
  }

  SECTION("Test range-based for loop for const non-empty Vector") {
    const Vector<int> v = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (auto num : v) {
      REQUIRE(num == expected[i++]);
    }
  }

  SECTION("Output stream operator correctly prints vector elements") {
    Vector<int> v(5, 10);
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    std::string expected = "10 10 10 10 10";
    REQUIRE(result == expected);
  }
}
