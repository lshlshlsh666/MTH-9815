#include "Hashtable.hpp"
#include "MyHasher_and_EqualityPredicate.hpp"
#include "test_struct.hpp"

#include <iostream>


int main() {
    test_struct test1{10086}, test2{222333}, test3{369369369}, test4{4396}, test5{55};
    MyHasher<test_struct> hasher;
    MyEqualityPredicate<test_struct> predicate;
    Hashtable<test_struct, int> table(&hasher, &predicate);

    std::cout << "Initial table: " << std::endl;
    table.PrintTable();

    std::cout << "Adding test1 to the table: " << std::endl;
    table.Put(test1, 1);
    table.PrintTable();

    std::cout << "Adding test2 to the table: " << std::endl;
    table.Put(test2, 2);
    table.PrintTable();

    std::cout << "Adding test3 to the table: " << std::endl;
    table.Put(test3, 3);
    table.PrintTable();

    std::cout << "Getting the value of test1: " << std::endl;
    std::cout << table.Get(test1) << std::endl;

    std::cout << "Adding test4 to the table: " << std::endl;
    table.Put(test4, 4);
    table.PrintTable();

    std::cout << "Removing test2 from the table: " << std::endl;
    table.Remove(test2);
    table.PrintTable();

    std::cout << "Adding test5 to the table: " << std::endl;
    table.Put(test5, 5);
    table.PrintTable();
}