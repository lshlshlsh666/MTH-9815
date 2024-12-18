#include "DoublyLinkedList.hpp"

#include <stdexcept>


template <typename T>
void DoublyLinkedList<T>::Add(T& value) {
    DNode<T>* newNode = new DNode<T>(value);
    if (this->_head == nullptr) {
        this->_head = newNode;
        this->_tail = newNode;
    } else {
        this->_tail->next = newNode;
        newNode->prev = this->_tail;
        this->_tail = newNode;
    }
}

template <typename T>
void DoublyLinkedList<T>::Insert(T& value, int index) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    DNode<T>* newNode = new DNode<T>(value);
    if (index == 0) {
        newNode->next = this->_head;
        this->_head->prev = newNode;
        this->_head = newNode;
    } else {
        DNode<T>* current = _head;
        for (int i = 0; i < index - 1; i++) {
            if (current == nullptr) {
                throw std::out_of_range("Index out of bounds");
            }
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }
}

template <typename T>
T& DoublyLinkedList<T>::Get(int index) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    DNode<T>* current = _head;
    // Traverse the list to the specified index
    for (int i = 0; i < index; i++) {
        if (current == nullptr) {
            throw std::out_of_range("Index out of bounds");
        }
        current = current->next;
    }
    return current->data;
}

template <typename T>
int DoublyLinkedList<T>::IndexOf(T& value) {
    int index = 0;
    for (DNode<T>* current = this->_head; current != nullptr; current = current->next) {
        if (current->data == value) {
            return index;
        }
        index++;
    }
    return -1;
}

template <typename T>
T& DoublyLinkedList<T>::Remove(int index) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    DNode<T>* current = this->_head;
    for (int i = 0; i < index; i++) {
        if (current == nullptr) {
            throw std::out_of_range("Index out of bounds");
        }
        current = current->next;
    }
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }
    return current->data;
}

template <typename T>
int DoublyLinkedList<T>::Size() {
    int size = 0;
    for (DNode<T>* current = this->_head; current != nullptr; current = current->next) {
        size++;
    }
    return size;
}