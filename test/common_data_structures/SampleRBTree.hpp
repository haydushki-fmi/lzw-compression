#ifndef SAMPLERBTREE_HPP
#define SAMPLERBTREE_HPP

#include "common_data_structures/implementations/RBNode.hpp"

/* Sample Red-Black tree:
 *
 *                 bA: 13
 *                /     \
 *               /       \
 *              /         \
 *          rB: 8         rC: 17
 *         /  \           /    \
 *      bD: 1  bE: 11   bF: 15   bG: 25
 *        \                     /    \
 *        rH: 6              rI: 22  rJ: 27
 *
 */
class SampleRBTree
{
public:
    using ValueType = int;

    RBNode<ValueType> j;
    RBNode<ValueType> i;
    RBNode<ValueType> h;
    RBNode<ValueType> g;
    RBNode<ValueType> f;
    RBNode<ValueType> e;
    RBNode<ValueType> d;
    RBNode<ValueType> c;
    RBNode<ValueType> b;
    RBNode<ValueType> a;

    RBNode<ValueType> &root = a;
    RBNode<ValueType> *rootptr = &a;

    const ValueType valueNotInTheTree = 1000000;

    SampleRBTree()
    {
        this->j = RBNode<ValueType>(27, nullptr, nullptr, &g);
        this->i = RBNode<ValueType>(22, nullptr, nullptr, &g);
        this->h = RBNode<ValueType>(6, nullptr, nullptr, &d);
        this->g = RBNode<ValueType>(25, &i, &j, &c);
        this->f = RBNode<ValueType>(15, nullptr, nullptr, &c);
        this->e = RBNode<ValueType>(11, nullptr, nullptr, &b);
        this->d = RBNode<ValueType>(1, nullptr, &h, &b);
        this->c = RBNode<ValueType>(17, &f, &g, &a);
        this->b = RBNode<ValueType>(8, &d, &e, &a);
        this->a = RBNode<ValueType>(13, &b, &c);
    }
};

#endif // SAMPLERBTREE_HPP
