#ifndef TEST_STRUCT_HPP
#define TEST_STRUCT_HPP

#include <iostream>

struct test_struct {
    int value;

    // Default constructor
    test_struct() : value(9999) {}
    // Constructor with value
    test_struct(int value) : value(value) {}

    // Define the equality operator for the test_struct
    bool operator==(const test_struct& other) const {
        return value == other.value;
    }
    // ostream operator for the test_struct
    friend std::ostream& operator<<(std::ostream& os, const test_struct& obj) {
        return os << obj.value;
    }
};

#endif