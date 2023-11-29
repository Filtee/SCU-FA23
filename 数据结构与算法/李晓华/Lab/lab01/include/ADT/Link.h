#ifndef LAB01_LINK_H
#define LAB01_LINK_H

template<typename E>
class Link {
public:
    // Value for this node
    E element;
    // Pointer to next node in list
    Link *next;
    // Constructors
    Link(const E &element, Link *next = nullptr) {
        this->element = element;
        this->next = next;
    }

    Link(Link *next = nullptr) {
        this->next = next;
    }
};

#endif //LAB01_LINK_H
