#ifndef EQUALITYPREDICATE_HPP
#define EQUALITYPREDICATE_HPP

template <typename K>
class EqualityPredicate {
public:
    virtual bool Equals(K key1, K key2) = 0;
};

#endif