#ifndef TEST_DLINK_H
#define TEST_DLINK_H

template<typename E>
class DLink {
public:
    // Value for this node
    E element;
    // Pointer to previous node in list
    DLink *prev;
    // Pointer to next node in list
    DLink *next;

    // Constructors
    DLink() {
    }

    DLink(const E &element) {
        this->element = element;
    }

    DLink(const E &element, DLink *prev, DLink *next) {
        this->element = element;
        this->prev = prev;
        this->next = next;
    }
};

#endif //TEST_DLINK_H
