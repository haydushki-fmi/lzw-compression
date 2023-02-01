#include "SampleRBTree.hpp"
#include "catch2/catch_all.hpp"
#include "common_data_structures/implementations/RBNodeOperations.hpp"

TEST_CASE("RBNodeOPerations::sameTrees() returns true for two empty trees",
          "[RBTree][RBNodeOperations]")
{
    REQUIRE(RBNodeOPerations<int>::sameTrees(nullptr, nullptr));
}

TEST_CASE(
    "RBNodeOPerations::sameTrees() returns false when comparing an empty and a non-empty tree",
    "[RBTree][RBNodeOperations]")
{
    RBNode<int> n;
    SECTION("Left is non-empty, right is empty")
    {
        REQUIRE_FALSE(RBNodeOPerations<int>::sameTrees(&n, nullptr));
    }
    SECTION("Left is empty, right is non-empty")
    {
        REQUIRE_FALSE(RBNodeOPerations<int>::sameTrees(nullptr, &n));
    }
}

TEST_CASE("RBNodeOPerations::sameTrees() returns true when comparing equivalent trees",
          "[RBTree][RBNodeOperations]")
{
    SampleRBTree t1, t2;
    REQUIRE(RBNodeOPerations<int>::sameTrees(&t1.root, &t2.root));
}

TEST_CASE("RBNodeOPerations::sameTrees() returns false when comparing different trees",
          "[RBTree][RBNodeOperations]")
{
    SampleRBTree t1, t2;

    t1.e.data -= 1;

    REQUIRE_FALSE(RBNodeOPerations<int>::sameTrees(&t1.root, &t2.root));
}

template<typename T>
inline bool areSameObject(const T &a, const T &b)
{
    return &a == &b;
}

TEST_CASE("RBNodeOPerations::findPointerTo() returns the starting pointer when searching in an "
          "empty tree",
          "[RBTree][RBNodeOperations]")
{
    RBNode<int> *rootptr = nullptr;
    CHECK(areSameObject(rootptr, RBNodeOPerations<int>::findPointerTo(rootptr, 0)));
}

TEST_CASE("RBNodeOPerations::findPointerTo() returns the starting pointer when "
          "searching in a single-node tree",
          "[RBTree][RBNodeOperations]")
{
    int someRandomValue = 42; // A random value
    RBNode<int> node(someRandomValue);
    RBNode<int> *rootptr = nullptr;

    CHECK(areSameObject(rootptr, RBNodeOPerations<int>::findPointerTo(rootptr, someRandomValue)));
}

TEST_CASE("RBNodeOPerations::findPointerTo() locates the pointer to a node with specific value in "
          "the tree.",
          "[RBTree][RBNodeOperations]")
{
    SampleRBTree t;

    CHECK(areSameObject(t.rootptr, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.a.data)));
    CHECK(areSameObject(t.a.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.b.data)));
    CHECK(areSameObject(t.a.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.c.data)));
    CHECK(areSameObject(t.b.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.d.data)));
    CHECK(areSameObject(t.b.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.e.data)));
    CHECK(areSameObject(t.c.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.f.data)));
    CHECK(areSameObject(t.c.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.g.data)));
    CHECK(areSameObject(t.d.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.h.data)));
    CHECK(areSameObject(t.g.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.i.data)));
    CHECK(areSameObject(t.g.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.j.data)));
}

TEST_CASE("RBNodeOPerations::findPointerTo() returns the correct position where a node "
          "should be inserted when it is not present in the tree",
          "[RBTree][RBNodeOperations]")
{
    SampleRBTree t;

    // Check values for each node which has one or more missing successors.
    // The values being inserted are +/-1 from the value stored in the respective node.
    // They should be added exactly under the said node to the left or to the right.
    CHECK(areSameObject(t.d.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.d.data - 1)));
    CHECK(areSameObject(t.e.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.e.data - 1)));
    CHECK(areSameObject(t.e.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.e.data + 1)));
    CHECK(areSameObject(t.f.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.f.data - 1)));
    CHECK(areSameObject(t.f.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.f.data + 1)));
    CHECK(areSameObject(t.h.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.h.data - 1)));
    CHECK(areSameObject(t.h.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.h.data + 1)));
    CHECK(areSameObject(t.i.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.i.data - 1)));
    CHECK(areSameObject(t.i.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.i.data + 1)));
    CHECK(areSameObject(t.j.left, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.j.data - 1)));
    CHECK(areSameObject(t.j.right, RBNodeOPerations<int>::findPointerTo(t.rootptr, t.j.data + 1)));
}

// TODO: Tests for rotations

TEST_CASE("RBNodeOPerations::rotateLeft() correctly rotates left", "[RBTree][RBNodeOperations]")
{
    SampleRBTree t;

    RBNodeOPerations<int>::rotateLeft(&t.c);
    CHECK(areSameObject(*t.c.parent, t.g));
    CHECK(areSameObject(*t.c.left, t.f));
    CHECK(areSameObject(*t.c.right, t.i));
    CHECK(areSameObject(*t.g.parent, t.a));
    CHECK(areSameObject(*t.g.left, t.c));
    CHECK(areSameObject(*t.g.right, t.j));
}

TEST_CASE("RBNodeOPerations::rotateRight() correctly rotates left", "[RBTree][RBNodeOperations]")
{
    SampleRBTree t;

    RBNodeOPerations<int>::rotateRight(&t.b);
    CHECK(areSameObject(*t.b.parent, t.d));
    CHECK(areSameObject(*t.b.left, t.h));
    CHECK(areSameObject(*t.b.right, t.e));
    CHECK(areSameObject(*t.d.parent, t.a));
    CHECK(t.d.left == nullptr);
    CHECK(areSameObject(*t.d.right, t.b));
}

TEST_CASE("RBNodeOPerations::insert() correctly inserts into an empty tree",
          "[RBTree][RBNodeOperations]")
{
    RBNode<int> *rootptr = nullptr;
    RBNode<int> node;

    RBNodeOPerations<int>::insert(rootptr, node);

    REQUIRE(rootptr == &node);
}

TEST_CASE("RBNodeOPerations::insert() correctly inserts into a non-empty tree",
          "[RBTree][RBNodeOperations]")
{
    // TODO: checks for place, rotation and colour
}

TEST_CASE("RBNodeOPerations::release() does not throw on nullptr", "[RBTree][RBNodeOperations]")
{
    // TODO: add checks
}
