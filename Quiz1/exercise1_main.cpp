#include "quicksort.hpp"

#include <iostream>
#include <array>


int main() {
    const int N = 6;
    std::array<int, N> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    std::cout << "Original array: ";
    printArray<int, N>(arr);

    quicksort<int, N>(arr);

    std::cout << "Sorted array: ";
    printArray<int, N>(arr);

    // Test with an array of size 100
    const int N2 = 100;
    std::array<int, N2> arr2;
    for (int i = 0; i < N2; ++i) {
        arr2[i] = N2 - i;
    }

    std::cout << "Original array: ";
    printArray<int, N2>(arr2);

    quicksort<int, N2>(arr2);

    std::cout << "Sorted array: ";
    printArray<int, N2>(arr2);

    return 0;
}