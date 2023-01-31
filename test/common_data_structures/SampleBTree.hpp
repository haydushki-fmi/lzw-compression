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
        a->keys.push_back(100);

        b->keys.push_back(35);
        b->keys.push_back(65);

        c->keys.push_back(130);
        c->keys.push_back(180);

        d->keys.push_back(10);
        d->keys.push_back(20);

        e->keys.push_back(40);
        e->keys.push_back(50);

        f->keys.push_back(70);
        f->keys.push_back(80);
        f->keys.push_back(90);

        g->keys.push_back(110);
        g->keys.push_back(120);

        h->keys.push_back(140);
        h->keys.push_back(160);

        i->keys.push_back(190);
        i->keys.push_back(240);
        i->keys.push_back(260);

        // Set realtion
        b->children.push_back(d);
        b->children.push_back(e);
        b->children.push_back(f);

        c->children.push_back(g);
        c->children.push_back(h);
        c->children.push_back(i);

        a->children.push_back(b);
        a->children.push_back(c);
    }

    ~SampleBTree() { delete &this->root; }
};

#endif // SAMPLEBTREE_HPP
