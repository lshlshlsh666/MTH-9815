#include "LinkedList.hpp"

#include <stdexcept>


template <typename T>
void LinkedList<T>::Add(T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (_head == nullptr) {
        _head = newNode;
        _tail = newNode;
    } else {
        _tail->next = newNode;
        _tail = newNode;
    }
}

template <typename T>
void LinkedList<T>::Insert(T& value, int index) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    Node<T>* newNode = new Node<T>(value);
    // If the index is 0, insert the new node at the head
    if (index == 0) {
        newNode->next = _head;
        _head = newNode;
    } else {
        Node<T>* current = _head;
        for (int i = 0; i < index - 1; i++) {
            if (current == nullptr) {
                throw std::out_of_range("Index out of bounds");
            }
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

template <typename T>
T& LinkedList<T>::Get(int index) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    Node<T>* current = _head;
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
int LinkedList<T>::IndexOf(T& value) {
    int index = 0;
    for (Node<T>* current = _head; current != nullptr; current = current->next) {
        if (current->data == value) {
            return index;
        }
        index++;
    }
    return -1;
}

template <typename T>
T& LinkedList<T>::Remove(int index) {
    if (index < 0) {
        throw std::out_of_range("Index out of range");
    }
    Node<T>* current = _head;
    // If the index is 0, remove the head
    if (index == 0) {
        _head = current->next;
        T& data = current->data;
        delete current;
        return data;
    }
    // Traverse the list to the specified index
    for (int i = 0; i < index - 1; i++) {
        if (current == nullptr) {
            throw std::out_of_range("Index out of bounds");
        }
        current = current->next;
    }
    Node<T>* next = current->next;
    current->next = next->next;
    T& data = next->data;
    delete next;
    return data;
}

template <typename T>
ListIterator<T> LinkedList<T>::Iterator() {
    return ListIterator<T>(_head);
}

template <typename T>
int LinkedList<T>::Size() {
    int size = 0;
    for (ListIterator<T> iterator = Iterator(); iterator.HasNext(); ++iterator) {
        size++;
    }
    return size;
}