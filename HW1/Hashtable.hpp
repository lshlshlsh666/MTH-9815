#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "Hasher.hpp"
#include "EqualityPredicate.hpp"

#include <array> 
#include <iostream>


template <typename K, typename V>
class Hashtable {
private:
    static const int DEFAULT_CAPACITY = 256;
    struct Entry {
        K key;
        V value;
    };

    Hasher<K>* _hasher;
    EqualityPredicate<K>* _predicate;

    std::array<Entry, DEFAULT_CAPACITY> _table;
public:
    Hashtable(Hasher<K>* hasher, EqualityPredicate<K>* predicate) : _hasher(hasher), _predicate(predicate) {}

    void Put(K key, V value) {
        int index = _hasher->hash(key) % DEFAULT_CAPACITY;
        while (_table[index].key != key && _table[index].key != K()) {
            index = (index + 1) % DEFAULT_CAPACITY;
        }
        _table[index].key = key;
        _table[index].value = value;
    }

    V Get(K key) {
        int index = _hasher->hash(key) % DEFAULT_CAPACITY;
        while (!_predicate->Equals(_table[index].key, key)) {
            index = (index + 1) % DEFAULT_CAPACITY;
        }
        return _table[index].value;
    }

    void Remove(K key) {
        int index = _hasher->hash(key) % DEFAULT_CAPACITY;
        while (!_predicate->Equals(_table[index].key, key)) {
            index = (index + 1) % DEFAULT_CAPACITY;
        }
        _table[index].key = K();
        _table[index].value = V();
    }
    
    // Print the table
    void PrintTable() {
        for (int i = 0; i < DEFAULT_CAPACITY; i++) {
            if (_table[i].key != K()){
                std::cout << "Index: " << i << " Key: " << _table[i].key << " Value: " << _table[i].value << std::endl;
            }
        }
    }
};
#endif