#ifndef HASHER_HPP
#define HASHER_HPP

template <typename K>
class Hasher {
public:
    virtual int hash(K key) = 0;
};

#endif