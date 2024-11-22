#ifndef MYHASHER_AND_EQUALITYPREDICATE_HPP
#define MYHASHER_AND_EQUALITYPREDICATE_HPP

#include "Hasher.hpp"
#include "EqualityPredicate.hpp"
#include "test_struct.hpp"

#include <functional>


template <typename K = test_struct>
class MyHasher : public Hasher<test_struct> {
public:
    int hash(test_struct key) {
        return std::hash<int>()(key.value);
    }
};

template <typename K = test_struct>
class MyEqualityPredicate : public EqualityPredicate<test_struct> {
public:
    bool Equals(test_struct key1, test_struct key2) {
        return key1 == key2;
    }
};

#endif