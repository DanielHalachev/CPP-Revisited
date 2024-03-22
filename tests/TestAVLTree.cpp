#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "Avl.h"

TEST_CASE("AVLTree tests", "[AVLTree]") {
  AVLTree<int> tree;

  SECTION("Default constructor creates empty tree") {
    REQUIRE(tree.getElements().empty());
  }

  SECTION("Insertion works correctly") {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    REQUIRE(tree.getElements() == std::vector<int>{2, 3, 4, 5, 6, 7, 8});
  }

  SECTION("Removal works correctly") {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.remove(3);
    tree.remove(7);
    REQUIRE(tree.getElements() == std::vector<int>{2, 4, 5, 6, 8});
  }

  SECTION("Tree maintains balance") {
    for (int i = 0; i < 1000; ++i) tree.insert(i);
    REQUIRE(tree.isBalanced());

    for (int i = 0; i < 1000; ++i) tree.remove(i);
    REQUIRE(tree.isBalanced());
  }

  SECTION("Copy constructor works correctly") {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    AVLTree<int> copiedTree(tree);
    REQUIRE(copiedTree.getElements() == tree.getElements());
  }

  SECTION("Move constructor works correctly") {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    AVLTree<int> movedTree(std::move(tree));
    REQUIRE(movedTree.getElements() == std::vector<int>{3, 5, 7});
    REQUIRE(tree.getElements().empty());
  }

  SECTION("Copy assignment works correctly") {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    AVLTree<int> copiedTree;
    copiedTree = tree;
    REQUIRE(copiedTree.getElements() == tree.getElements());
  }

  SECTION("Move assignment works correctly") {
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    AVLTree<int> movedTree;
    movedTree = std::move(tree);
    REQUIRE(movedTree.getElements() == std::vector<int>{3, 5, 7});
    REQUIRE(tree.getElements().empty());
  }
}
