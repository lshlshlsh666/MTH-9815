#include "maxheap.hpp"

#include <iostream>


int main() {
    MaxHeap<int> maxHeap;
    std::cout << "Max-Heap elements: ";
    maxHeap.PrintHeap();
    // Add elements to the max-heap
    maxHeap.Add(10);
    std::cout << "Max-Heap elements: ";
    maxHeap.PrintHeap();

    maxHeap.Add(20);
    std::cout << "Max-Heap elements: ";
    maxHeap.PrintHeap();

    maxHeap.Add(15);
    std::cout << "Max-Heap elements: ";
    maxHeap.PrintHeap();
    
    maxHeap.Add(30);
    std::cout << "Max-Heap elements: ";
    maxHeap.PrintHeap();

    maxHeap.Add(5);
    std::cout << "Max-Heap elements: ";
    maxHeap.PrintHeap();

    return 0;
}