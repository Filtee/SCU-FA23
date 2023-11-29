#ifndef TEST_TESTSTACK_H
#define TEST_TESTSTACK_H

#include "doctest/doctest.h"
#include "ADT/Stack.h"
#include "ADT/Queue.h"

/*
 * 栈的单元测试
 */
TEST_CASE("Testing ADTs") {
    SUBCASE("Testing stack.") {
        Stack<int> *stack = new Stack<int>();
        int nums[]{1, 2, 3, 4, 5, 6, 7, 2, 9, 3, 5};
        for (int num: nums) {
            stack->push(num);
        }

        for (int i = 10; i != -1; --i) {
            CHECK_EQ(nums[i], stack->pop());
        }
    }

    SUBCASE("Testing stack2.") {
        Stack<char> *stack = new Stack<char>();
        char nums[]{'1', '2', '3', '4', '5', '6', '7', '2', '9', '3', '5'};
        for (int num: nums) {
            stack->push(num);
        }

        for (int i = 10; i != -1; --i) {
            CHECK_EQ(nums[i], stack->pop());
        }
    }

    SUBCASE("Testing deque.") {
        Queue<int> *deque = new Queue<int>();
        int nums[]{1, 2, 3, 4, 5, 6, 7, 2, 9, 3, 5};
        for (int num: nums) {
            deque->add(num);
        }

        for (int i = 0; i < deque->length(); ++i) {
            CHECK_EQ(nums[i], deque->removeLast());
        }
    }
}

#endif //TEST_TESTSTACK_H
