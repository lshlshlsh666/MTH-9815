#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include "ListIterator.hpp"

#include <iostream>

template <typename T>
class LinkedList {
protected:
    Node<T>* _head;
    Node<T>* _tail;
public:
    LinkedList() : _head(nullptr), _tail(nullptr) {}

    // Add the specified element to the end of the list
    void Add(T& value);
    // Add the specified element at the specified index
    void Insert(T& value, int index);
    // Get the element at the specified index
    T& Get(int index);
    // Retrieve the index of the specified element (-1 if it does not exist in the list
    int IndexOf(T& value);
    // Remove the element at the specified index and return it
    T& Remove(int index);
    // Return an iterator on this list
    ListIterator<T> Iterator();
    // Return the size of the list
    int Size();

    // print the list
    void Print() {
        for (Node<T>* current = _head; current != nullptr; current = current->next) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

#ifndef LINKEDLIST_TPP
#include "LinkedList.tpp"
#endif

#endif