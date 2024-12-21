#include "maxheap.hpp"

#include <iostream>


int main() {
    MaxHeap<int> maxHeap;

    // Add elements to the max-heap
    maxHeap.Add(-100);
    maxHeap.Add(10);
    maxHeap.Add(20);
    maxHeap.Add(15);
    maxHeap.Add(30);
    maxHeap.Add(5);

    std::cout << "Initial Max-Heap: ";
    maxHeap.PrintHeap();

    // Remove the maximum element
    int removedElement = maxHeap.Remove(0);
    std::cout << "Removed element: " << removedElement << std::endl;

    // Print the heap after removal
    std::cout << "Max-Heap after removal: ";
    maxHeap.PrintHeap();

    // Remove an element at index 1
    removedElement = maxHeap.Remove(1);
    std::cout << "Removed element: " << removedElement << std::endl;

    // Print the heap after removal
    std::cout << "Max-Heap after removal: ";
    maxHeap.PrintHeap();

    return 0;
}