#ifndef SAMPLEBTREE_HPP
#define SAMPLEBTREE_HPP

#include "common_data_structures/implementations/BTreeNode.hpp"

class SampleBTree
{
    //                         A: 100
    //                           /   \
    //        B: 35 65                            C: 130 180
    //     /      |     \                       /       |       \
    // D: 10 20  E: 40 50  F: 70 80 90   G: 110 120  H: 140 160  I: 190 240 260

public:
    BTreeNode<int> *a = new BTreeNode<int>(5, false);
    BTreeNode<int> *b = new BTreeNode<int>(5, false);
    BTreeNode<int> *c = new BTreeNode<int>(5, false);
    BTreeNode<int> *d = new BTreeNode<int>(5, true);
    BTreeNode<int> *e = new BTreeNode<int>(5, true);
    BTreeNode<int> *f = new BTreeNode<int>(5, true);
    BTreeNode<int> *g = new BTreeNode<int>(5, true);
    BTreeNode<int> *h = new BTreeNode<int>(5, true);
    BTreeNode<int> *i = new BTreeNode<int>(5, true);

    BTreeNode<int> &root = *a;

public:
    SampleBTree()
    {
        //Set keys
        a->keyCount = 1;
        a->keys[0] = 100;

        b->keyCount = 2;
        b->keys[0] = 35;
        b->keys[1] = 65;

        c->keyCount = 2;
        c->keys[0] = 130;
        c->keys[1] = 180;

        d->keyCount = 2;
        d->keys[0] = 10;
        d->keys[1] = 20;

        e->keyCount = 2;
        e->keys[0] = 40;
        e->keys[1] = 50;

        f->keyCount = 3;
        f->keys[0] = 70;
        f->keys[1] = 80;
        f->keys[2] = 90;

        g->keyCount = 2;
        g->keys[0] = 110;
        g->keys[1] = 120;

        h->keyCount = 2;
        h->keys[0] = 140;
        h->keys[1] = 160;

        i->keyCount = 3;
        i->keys[0] = 190;
        i->keys[1] = 240;
        i->keys[2] = 260;

        // Set realtion
        b->children[0] = d;
        b->children[1] = e;
        b->children[2] = f;

        c->children[0] = g;
        c->children[1] = h;
        c->children[2] = i;

        a->children[0] = b;
        a->children[1] = c;
    }

    ~SampleBTree() { delete &this->root; }
};

#endif // SAMPLEBTREE_HPP
