#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "SinglyLinkedList.h"

TEST_CASE("Singly Linked List Tests") {
    SECTION("Empty List") {
        SinglyLinkedList<int> list;
        REQUIRE(list.getSize() == 0);
        REQUIRE_THROWS_AS(list.erase(0), std::out_of_range);
        REQUIRE_THROWS_AS(list[0], std::out_of_range);
    }

    SECTION("Pushing and Popping") {
        SinglyLinkedList<int> list;
        list.pushBack(5);
        list.pushBack(10);
        REQUIRE(list.getSize() == 2);
        REQUIRE(list[0] == 5);
        REQUIRE(list[1] == 10);

        list.pushFront(1);
        REQUIRE(list.getSize() == 3);
        REQUIRE(list[0] == 1);
        REQUIRE(list[1] == 5);
        REQUIRE(list[2] == 10);

        list.popFront();
        REQUIRE(list.getSize() == 2);
        REQUIRE(list[0] == 5);
        REQUIRE(list[1] == 10);
    }

    SECTION("Initializer List Constructor") {
        SinglyLinkedList<int> list = {1, 2, 3, 4, 5};
        REQUIRE(list.getSize() == 5);
        for (int i = 0; i < 5; ++i) {
            REQUIRE(list[i] == i + 1);
        }
    }

    SECTION("Copy Constructor and Assignment Operator") {
        SinglyLinkedList<int> list1 = {1, 2, 3};
        SinglyLinkedList<int> list2 = list1;
        REQUIRE(list2.getSize() == 3);
        for (int i = 0; i < 3; ++i) {
            REQUIRE(list2[i] == i + 1);
        }

        SinglyLinkedList<int> list3;
        list3 = list2;
        REQUIRE(list3.getSize() == 3);
        for (int i = 0; i < 3; ++i) {
            REQUIRE(list3[i] == i + 1);
        }
    }

    SECTION("Move Constructor and Assignment Operator") {
        SinglyLinkedList<int> list1 = {1, 2, 3};
        SinglyLinkedList<int> list2 = std::move(list1);
        REQUIRE(list2.getSize() == 3);
        REQUIRE(list1.getSize() == 0);

        SinglyLinkedList<int> list3;
        list3 = std::move(list2);
        REQUIRE(list3.getSize() == 3);
        REQUIRE(list2.getSize() == 0);
    }

    SECTION("Iterator") {
        SinglyLinkedList<int> list = {1, 2, 3, 4, 5};
        int expected = 1;
        for (auto it = list.begin(); it != list.end(); ++it) {
            REQUIRE(*it == expected++);
        }

        expected = 1;
        for (const auto& item : list) {
            REQUIRE(item == expected++);
        }
    }

    SECTION("Erase") {
        SinglyLinkedList<int> list = {1, 2, 3, 4, 5};
        int removed = list.erase(2); // Remove element at index 2 (3)
        REQUIRE(list.getSize() == 4);
        REQUIRE(removed == 3);
        REQUIRE(list[2] == 4);
    }

    SECTION("Invalid Operations") {
        SinglyLinkedList<int> list = {1, 2, 3};
        REQUIRE_THROWS_AS(list.erase(5), std::out_of_range);
        REQUIRE_THROWS_AS(list[5], std::out_of_range);
    }
}

