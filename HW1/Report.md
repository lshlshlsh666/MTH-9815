# MTH 9815 Homework 1

## Gourp Members

- Shuhao Liu
- Yuxuan Wang
- Wenxin Zhao
- Shikai Yi

## Reports

### Compile

The HW is complied on MacOS with g++, using CMake:

```bash
mkdir build
cd build
cmake ../CMakeLists.txt
```

The CMakeLists.txt is as follows:

```cmake
project(MTH9815_HW1)

set(CMAKE_CXX_COMPILER g++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Exercise1 exercise1_main.cpp)

add_executable(Exercise2 exercise2_main.cpp)

add_executable(Exercise3 exercise3_main.cpp)
```

### Exercise 1

In this exercise, we defined the following classes:

- `Node.hpp`: A node with `data` and `next` pointer.
- `LinkedList.hpp`, `LinkedList.tpp`: A linked list with `head` and `tail` pointer, and member functions as the HW required.
- `ListIterator.hpp`: An iterator for the linked list, implenmenting `operator*`, `operator++` and the functions required by the HW.
- `test_struct.hpp`: A struct for testing the linked list.

In the main function in `exercise1_main.cpp`, we tested the linked list with the following steps:
- Create a linked list.
- Add elements to the linked list.
- Insert elements to the linked list.
- Get elements from the linked list.
- Find the index of an element in the linked list.
- Remove elements from the linked list.
- Use try-catch block to handle exceptions.

### Exercise 2

In this exercise, we defined the following classes:

- `DNode.hpp`: A node with `data`, `prev` and `next` pointer, inheriting from `Node`.
- `DoublyLinkedList.hpp`, `DoublyLinkedList.tpp`: A doubly linked list with `head` and `tail` pointer, inheriting from 'LinkedList', with member functions as the HW required.

Noted that the 'ListIterator' is also used in this exercise.

In the main function in `exercise2_main.cpp`, we tested the doubly linked list with the following steps:

- Create a doubly linked list.
- Add elements to the doubly linked list.
- Insert elements to the doubly linked list.
- Get elements from the doubly linked list.
- Find the index of an element in the doubly linked list.
- Remove elements from the doubly linked list.
- Use try-catch block to handle exceptions.

### Exercise 3

In this exercise, we defined the following classes:

- `Hashtable.hpp`: A hash table with a array `_table` containing `Entry` (a key-value pair), a `Hasher` and a `EqualityPredicate`. The default size of the array is 256. We also implemented the `Put`, `Get` and `Remove` functions, with the help of `Hasher` and `EqualityPredicate`. Hash collision is handled by add 1 to the index of the array.
- `Hasher.hpp`: An ABC for hash functions.
- `EqualityPredicate.hpp`: An ABC for equality predicates.
- `MyHasher_and_EqualityPredicate.hpp`: Two classes inheriting from `Hasher` and `EqualityPredicate`, respectively, with the hash function and equality designed for `test_struct`.

In the main function in `exercise3_main.cpp`, we tested the hash table with the following steps:
- Create a hash table.
- Put `test_struct` keys with `int` values to the hash table.
- Get values from the hash table.
- Remove keys from the hash table.