#include "SampleRBTree.hpp"
#include "catch2/catch_all.hpp"
#include "common_data_structures/implementations/RBNodeIterator.hpp"

TEST_CASE("RBNodeIterator::RBNodeIterator(nullptr) creates an iterator that has reached the end",
          "[RBTree][RBNodeIterator]")
{
    RBNodeIterator<int> it(nullptr);
    CHECK(it.atEnd());
}

TEST_CASE("RBNodeIterator walks the tree in the correct order and returns correct values",
          "[RBTree][RBNodeIterator]")
{
    SampleRBTree tree;
    RBNodeIterator<SampleRBTree::ValueType> it(tree.rootptr);
    RBNodeIterator<SampleRBTree::ValueType> end(nullptr);

    int itemCounter = 0;

    // Values are retrieved in the correct order
    for (; it != end; ++it, ++itemCounter) {
        CHECK(it->data == tree.values[itemCounter]);
        CHECK((*it).data == tree.values[itemCounter]);
        CHECK_FALSE(it.atEnd());
    }

    CHECK(itemCounter == tree.values.size()); // All elements have been visited
}

TEST_CASE("RBNodeIterators pointing at the same node are equal", "[RBTree][RBNodeIterator]")
{
    SampleRBTree tree;
    RBNodeIterator<SampleRBTree::ValueType> it1(tree.rootptr);
    RBNodeIterator<SampleRBTree::ValueType> it2(tree.rootptr);
    RBNodeIterator<SampleRBTree::ValueType> end(nullptr);

    for (; it1 != end; ++it1, ++it2) {
        CHECK(it1 == it2);
        CHECK_FALSE(it1 != it2);
    }

    CHECK(it1 == it2);
    CHECK_FALSE(it1 != it2);
    CHECK(it1 == end);
    CHECK_FALSE(it1 != end);
}
