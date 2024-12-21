#include <iostream>
#include <array>


template <typename T, size_t N>
int partition(std::array<T, N>& arr, int low, int high) {
    T pivot = arr[high]; // Pivot element
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]); // Place pivot in correct position
    return i + 1; // Return the partition index
}


template <typename T, size_t N>
void quicksort(std::array<int, N>& arr, int low = 0, int high = N - 1) {
    if (low < high) {
        int pi = partition<T, N>(arr, low, high); // Partition the array

        // Recursively sort elements before and after partition
        quicksort<T, N>(arr, low, pi - 1);
        quicksort<T, N>(arr, pi + 1, high);
    }
}

template <typename T, size_t N>
void printArray(std::array<T, N>& arr) {
    for (T x : arr) {
        std::cout << x << " ";
    }
    std::cout << std::endl;
}