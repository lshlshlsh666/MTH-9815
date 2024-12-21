#include <iostream>
#include <vector>


template <typename T>
class MaxHeap {
private:
    // Here we use a vector to represent the binomial tree structure!!!
    std::vector<int> heap; // Vector to store the heap elements, not use array since the size is not fixed

    // maintain heap property after adding an element
    void _heapify_after_add(T index) {
        while (index > 0) {
            // Get parent index
            int parent = (index - 1) / 2; 

            // If current node is greater than its parent, swap
            if (heap[index] > heap[parent]) {
                std::swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // maintain heap property after removing an element
    void _heapify_after_remove(int index) {
        int size = heap.size();
        while (index < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            // Find the largest among parent, left child, and right child
            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }

            // If the largest is not the parent, swap and continue
            if (largest != index) {
                std::swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    // Add an element to the max-heap
    void Add(T element) {
        heap.push_back(element); 
        _heapify_after_add(heap.size() - 1);   // Maintain the max-heap property
    }

    T Remove(int index) {
        if (index < 0 || index >= heap.size()) {
            throw std::out_of_range("Invalid index");
        }

        T removedElement = heap[index];
        heap[index] = heap[heap.size() - 1]; // Replace the element with the last element
        heap.pop_back(); // Remove the last element
        _heapify_after_remove(index); // Maintain the max-heap property
        return removedElement; // Return the removed element
    }

    // print the heap
    void PrintHeap() const {
        for (T val : heap) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
};
