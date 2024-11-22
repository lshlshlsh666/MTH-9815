#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "DNode.hpp"
#include "LinkedList.hpp"


template <typename T>
class DoublyLinkedList : public LinkedList<T> {
private:
    DNode<T>* _head;
    DNode<T>* _tail;
public:
    DoublyLinkedList() : _head(nullptr), _tail(nullptr) {}

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
    // Return the size of the list
    int Size();

    // print the list
    void Print() {
        for (DNode<T>* current = _head; current != nullptr; current = current->next) {
            std::cout << current->data << " ";
        }
        std::cout << std::endl;
    }
};

#ifndef DOUBLYLINKEDLIST_TPP
#include "DoublyLinkedList.tpp"
#endif

#endif 