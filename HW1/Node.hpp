#ifndef NODE_HPP
#define NODE_HPP


template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T data) : data(data), next(nullptr) {}
};

#endif