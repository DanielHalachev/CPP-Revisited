#define CATCH_CONFIG_MAIN
#include "catch2/catch_all.hpp"
#include "../include/vector/Vector.h"

TEST_CASE("Default constructor initializes an empty vector") {
    Vector<int> v;
    REQUIRE(v.getSize() == 0);
    REQUIRE(v.getCapacity() == DEFAULT_CAPACITY);
}

TEST_CASE("Constructor with capacity initializes vector with given capacity") {
    size_t capacity = 20;
    Vector<int> v(capacity);
    REQUIRE(v.getSize() == 0);
    REQUIRE(v.getCapacity() == capacity);
}

TEST_CASE("Constructor with size and value initializes vector with given size and value") {
    size_t size = 5;
    int value = 10;
    Vector<int> v(size, value);
    REQUIRE(v.getSize() == size);
    REQUIRE(v.getCapacity() >= size);
    for (size_t i = 0; i < size; ++i) {
        REQUIRE(v[i] == value);
    }
}

TEST_CASE("Test Vector constructor with initializer list") {
    Vector<int> v = {1, 2, 3, 4, 5};
    REQUIRE(v.getSize() == 5);
    REQUIRE(v.getCapacity() >= 5);
    for (size_t i = 0; i < v.getSize(); ++i) {
        REQUIRE(v[i] == i + 1);
    }
}

TEST_CASE("Copy constructor creates a deep copy of the vector") {
    Vector<int> v1(5, 10);
    Vector<int> v2(v1);
    REQUIRE(v1.getSize() == v2.getSize());
    REQUIRE(v1.getCapacity() == v2.getCapacity());
    for (size_t i = 0; i < v1.getSize(); ++i) {
        REQUIRE(v1[i] == v2[i]);
    }
}

TEST_CASE("Assignment operator performs deep copy of the vector") {
    Vector<int> v1(5, 10);
    Vector<int> v2;
    v2 = v1;
    REQUIRE(v1.getSize() == v2.getSize());
    REQUIRE(v1.getCapacity() == v2.getCapacity());
    for (size_t i = 0; i < v1.getSize(); ++i) {
        REQUIRE(v1[i] == v2[i]);
    }
}

TEST_CASE("Move constructor transfers ownership of data") {
    Vector<int> v1(5, 10);
    Vector<int> v2(std::move(v1));
    REQUIRE(v1.getSize() == 0);
    REQUIRE(v1.getCapacity() == 0);
    REQUIRE(v2.getSize() == 5);
    REQUIRE(v2.getCapacity() >= 5);
    for (size_t i = 0; i < v2.getSize(); ++i) {
        REQUIRE(v2[i] == 10);
    }
}

TEST_CASE("Move assignment operator transfers ownership of data") {
    Vector<int> v1(5, 10);
    Vector<int> v2;
    v2 = std::move(v1);
    REQUIRE(v1.getSize() == 0);
    REQUIRE(v1.getCapacity() == 0);
    REQUIRE(v2.getSize() == 5);
    REQUIRE(v2.getCapacity() >= 5);
    for (size_t i = 0; i < v2.getSize(); ++i) {
        REQUIRE(v2[i] == 10);
    }
}

TEST_CASE("Pushing back increases size and possibly capacity") {
    Vector<int> v;
    for (int i = 0; i < 20; ++i) {
        v.pushBack(i);
        REQUIRE(v.getSize() == i + 1);
        if (i + 1 > DEFAULT_CAPACITY) {
            REQUIRE(v.getCapacity() >= i + 1);
        } else {
            REQUIRE(v.getCapacity() == DEFAULT_CAPACITY);
        }
    }
    for (int i = 0; i < 20; ++i) {
        REQUIRE(v[i] == i);
    }
}

TEST_CASE("Erasing element at valid index reduces size and shifts elements") {
    Vector<int> v(5, 10);
    v.erase(2);
    REQUIRE(v.getSize() == 4);
    REQUIRE(v[0] == 10);
    REQUIRE(v[1] == 10);
    REQUIRE(v[2] == 10);
    REQUIRE(v[3] == 10);
}

TEST_CASE("Erasing element at invalid index throws out_of_range exception") {
    Vector<int> v(5, 10);
    REQUIRE_THROWS_AS(v.erase(5), std::out_of_range);
}

TEST_CASE("Resizing changes the capacity and preserves existing elements") {
    Vector<int> v(5, 10);
    v.resize(10);
    REQUIRE(v.getSize() == 5);
    REQUIRE(v.getCapacity() == 10);
    for (size_t i = 0; i < 5; ++i) {
        REQUIRE(v[i] == 10);
    }
}

TEST_CASE("Resizing to smaller size reduces capacity and preserves existing elements") {
    Vector<int> v(10, 5);
    v.resize(5);
    REQUIRE(v.getSize() == 5);
    REQUIRE(v.getCapacity() == 5);
    for (size_t i = 0; i < 5; ++i) {
        REQUIRE(v[i] == 5);
    }
}

TEST_CASE("Accessing elements using subscript operator retrieves correct element") {
    Vector<int> v(5, 10);
    for (size_t i = 0; i < v.getSize(); ++i) {
        REQUIRE(v[i] == 10);
    }
}

TEST_CASE("Accessing element at invalid index using subscript operator throws out_of_range exception") {
    Vector<int> v(5, 10);
    REQUIRE_THROWS_AS(v[v.getSize()], std::out_of_range);
}

TEST_CASE("Test begin() and end() functions for empty Vector") {
    Vector<int> v;
    REQUIRE(v.begin() == v.end());
}

TEST_CASE("Test begin() and end() functions for non-empty Vector") {
    Vector<int> v = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        REQUIRE(*it == expected[i++]);
    }
}

TEST_CASE("Test const begin() and end() functions for non-empty Vector") {
    const Vector<int> v = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        REQUIRE(*it == expected[i++]);
    }
}

TEST_CASE("Test range-based for loop for non-empty Vector") {
    Vector<int> v = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (auto num : v) {
        REQUIRE(num == expected[i++]);
    }
}

TEST_CASE("Test range-based for loop for const non-empty Vector") {
    const Vector<int> v = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t i = 0;
    for (auto num : v) {
        REQUIRE(num == expected[i++]);
    }
}

TEST_CASE("Output stream operator correctly prints vector elements") {
    Vector<int> v(5, 10);
    std::ostringstream oss;
    oss << v;
    std::string result = oss.str();
    std::string expected = "10 10 10 10 10";
    REQUIRE(result == expected);
}

