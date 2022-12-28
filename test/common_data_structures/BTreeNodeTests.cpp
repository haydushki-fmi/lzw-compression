#include "catch2/catch_all.hpp"
#include "common_data_structures/implementations/BTreeNode.hpp"

class sampleTree
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
    sampleTree()
    {
        //Set keys;
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
};

TEST_CASE("common_data_structures_implementations::BTreeNode() constructs node with right data")
{
    SECTION("Isn't leaf")
    {
        BTreeNode<int> node = BTreeNode<int>(5, false);
        CHECK(node.degree == 5);
        CHECK_FALSE(node.isLeaf);
        CHECK(node.keyCount == 0);
        CHECK(node.keys != nullptr);
        CHECK(node.children != nullptr);
    }
    SECTION("Is leaf")
    {
        BTreeNode<int> node = BTreeNode<int>(6, true);
        CHECK(node.degree == 6);
        CHECK(node.isLeaf);
        CHECK(node.keyCount == 0);
        CHECK(node.keys != nullptr);
        CHECK(node.children == nullptr);
    }
}

TEST_CASE(
    "common_data_structures_implementations::BTreeNode::traverse() traverses subtree as it should")
{
    sampleTree st;
    std::vector<int> result;
    st.root.traverse(result);

    CHECK(result.size() == 19);
    CHECK(result[0] == 10);
    CHECK(result[1] == 20);
    CHECK(result[2] == 35);
    CHECK(result[3] == 40);
    CHECK(result[4] == 50);
    CHECK(result[5] == 65);
    CHECK(result[6] == 70);
    CHECK(result[7] == 80);
    CHECK(result[8] == 90);
    CHECK(result[9] == 100);
    CHECK(result[10] == 110);
    CHECK(result[11] == 120);
    CHECK(result[12] == 130);
    CHECK(result[13] == 140);
    CHECK(result[14] == 160);
    CHECK(result[15] == 180);
    CHECK(result[16] == 190);
    CHECK(result[17] == 240);
    CHECK(result[18] == 260);
}
