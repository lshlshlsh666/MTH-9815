#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP

#include "Node.hpp"
#include "DNode.hpp"

#include <stdexcept>


template <typename T>
class ListIterator {
private:
    Node<T>* _current;
public:
    ListIterator(Node<T>* current) : _current(current) {}

    // Return whether there is another element to return in this iterator
    bool HasNext() {
        return _current != nullptr;
    }

    // Return the next element in this iterator
    T& Next() {
        if (!HasNext()) {
            throw std::out_of_range("No more elements to return");
        }
        T& data = _current->data;
        _current = _current->next;
        return data;
    }

    ListIterator<T>& operator++() {
        if (!HasNext()) {
            throw std::out_of_range("No more elements to return");
        }
        _current = _current->next;
        return *this;
    }
};

#endif