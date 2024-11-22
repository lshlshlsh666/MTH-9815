#include "LinkedList.hpp"
#include "test_struct.hpp"

#include <iostream>


int main() {
    LinkedList<test_struct> list;
    test_struct v1 = {1}, v2 = {2}, v3 = {3}, v4 = {4};
    std::cout << "The initial list is empty: " << std::endl;
    list.Print();

    std::cout << "The list after adding 1, 2, and 3: " << std::endl;
    list.Add(v1);
    list.Add(v2);
    list.Add(v3);
    list.Print();

    std::cout << "The list after inserting 4 at index 1: " << std::endl;
    list.Insert(v4, 1);
    list.Print();

    std::cout << "Get the element at index 2: " << std::endl;
    std::cout << list.Get(2).value << std::endl;

    std::cout << "The index of the element with value 3 is: " << std::endl;
    std::cout << list.IndexOf(v3) << std::endl;

    std::cout << "The list after removing the element at index 2: " << std::endl;
    list.Remove(2);
    list.Print();

    std::cout << "The size of the list is: " << std::endl;
    std::cout << list.Size() << std::endl;

    std::cout << "If we try to get an element at an index that is out of bounds: " << std::endl;
    try {
        list.Get(10);
    } catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
}