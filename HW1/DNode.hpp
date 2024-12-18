#ifndef DNODE_HPP
#define DNODE_HPP

#include "Node.hpp"


template <typename T>
class DNode : public Node<T> {
public:
    DNode* prev;
    DNode* next;
    DNode(T data) : Node<T>(data), prev(nullptr), next(nullptr) {}
};

#endif