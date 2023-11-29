#ifndef TEST_DEQUE_H
#define TEST_DEQUE_H

#include "DLink.h"
#include "assert.h"

#define DEFAULT_SIZE 0

// Linked stack implementation
template<typename E>
class Queue {
private:
    // Pointer to first element
    DLink<E> *head = new DLink<E>();
    // Number of formula
    int size;
public:
    // Constructor
    Queue(int sz = DEFAULT_SIZE) {
        size = sz;
        head->next = head;
        head->prev = head;
    }

    // Destructor
    ~Queue() { clear(); }

    // Reinitialize
    void clear() {
        // Delete link nodes
        while (head != nullptr) {
            DLink<E> *temp = head->next;
            removeLast();
        }
        size = 0;
    }

    // Put "it" into deque
    void add(const E &it) {
        DLink<E> *temp = new DLink<E>(it);

        temp->next = head->next;
        head->next = temp;
        temp->next->prev = temp;
        temp->prev = head;

        size++;
    }

    // Remove the first value of the deque
    E removeFirst() {
        if (size == 0) {
            assert("栈已空");
        }

        E it = head->next->element;
        DLink<E> *temp = head->next;

        head->next = temp->next;
        temp->next->prev = head;

        delete temp;
        size--;
        return it;
    }

    // Remove the last value of the deque
    E removeLast() {
        if (size == 0) {
            assert("栈已空");
        }

        E it = head->prev->element;
        DLink<E> *temp = head->prev;

        head->prev = temp->prev;
        temp->prev->next = head;

        delete temp;
        size--;
        return it;
    }

    // Return first value
    const E &getFirst() const {
        if (size == 0) {
            assert("栈已空");
        }

        return head->next->element;
    }

    // Return last value
    const E &getLast() const {
        if (size == 0) {
            assert("栈已空");
        }

        return head->prev->element;
    }

    // Return length
    int length() const { return size; }
};

#endif //TEST_DEQUE_H
