#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "catch2/catch_template_test_macros.hpp"
#include "BinaryTree.h"


TEMPLATE_TEST_CASE("BinaryTree tests", "[BinaryTree]", int) {
  BinaryTree<TestType> testTree;

  SECTION("Test insertion") {
    testTree.insert(5);
    REQUIRE(testTree.getElements() == std::vector<TestType>{5});

    testTree.insert(3);
    testTree.insert(7);
    REQUIRE(testTree.getElements() == std::vector<TestType>{3, 5, 7});

    testTree.insert(4);
    testTree.insert(6);
    testTree.insert(8);
    REQUIRE(testTree.getElements() == std::vector<TestType>{3, 4, 5, 6, 7, 8});
  }

  SECTION("Test removal") {
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);
    testTree.insert(4);
    testTree.insert(6);
    testTree.insert(8);

    testTree.remove(4);
    REQUIRE(testTree.getElements() == std::vector<TestType>{3, 5, 6, 7, 8});

    testTree.remove(7);
    REQUIRE(testTree.getElements() == std::vector<TestType>{3, 5, 6, 8});

    testTree.remove(5);
    REQUIRE(testTree.getElements() == std::vector<TestType>{3, 6, 8});
  }

  SECTION("Test copy constructor") {
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);

    BinaryTree<TestType> copiedTree(testTree);
    REQUIRE(testTree.getElements() == copiedTree.getElements());
  }

  SECTION("Test copy assignment operator") {
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);

    BinaryTree<TestType> anotherTree;
    anotherTree = testTree;
    REQUIRE(testTree.getElements() == anotherTree.getElements());
  }

  SECTION("Test move constructor") {
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);

    BinaryTree<TestType> movedTree(std::move(testTree));
    REQUIRE(movedTree.getElements() == std::vector<TestType>{3, 5, 7});
  }

  SECTION("Test move assignment operator") {
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);

    BinaryTree<TestType> anotherTree;
    anotherTree = std::move(testTree);
    REQUIRE(anotherTree.getElements() == std::vector<TestType>{3, 5, 7});
  }

  SECTION("Test operator<<") {
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);

    std::ostringstream oss;
    oss << testTree;

    std::string expectedOutput = "5\n\t3\n\t7";
    REQUIRE(oss.str() == expectedOutput);
  }

  SECTION("Test getElements()") {
    testTree.insert(5);
    testTree.insert(3);
    testTree.insert(7);

    std::vector<TestType> elements = testTree.getElements();
    REQUIRE(elements == std::vector<TestType>{3, 5, 7});
  }
}
