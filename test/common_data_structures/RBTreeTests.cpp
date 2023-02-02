#include "catch2/catch_all.hpp"
#include "common_data_structures/implementations/RBTree.hpp"

class CustomTestClass
{
private:
    int data;

public:
    CustomTestClass(int data)
        : data(data)
    {}

    int getData() const { return this->data; }
    bool operator==(const CustomTestClass &other) const { return this->data == other.data; }
    bool operator<(const CustomTestClass &other) const { return this->data < other.data; }
};

TEST_CASE("common_data_structures_implementations::RBTree::RBTree() constructs right tree",
          "[RBTree]")
{
    RBTree<CustomTestClass> set;
    CHECK(set.size() == 0);
}

TEST_CASE("common_data_structures_implementations::RBTree::size() returns correct size", "[RBTree]")
{
    RBTree<CustomTestClass> set;
    CHECK(set.size() == 0);

    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    CHECK(set.size() == 2);
}

TEST_CASE("common_data_structures_implementations::RBTree can be inserted into", "[RBTree]")
{
    RBTree<CustomTestClass> set;
    CHECK(set.size() == 0);

    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    CHECK(set.size() == 2);
}

TEST_CASE("common_data_structures_implementations::RBTree::remove() removes items as it should",
          "[RBTree]")
{
    // TODO: Add test
}

TEST_CASE("common_data_structures_implementations::RBTree::search() searches correctly", "[RBTree]")
{
    RBTree<CustomTestClass> set;
    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    SECTION("Item exists")
    {
        CustomTestClass *result = set.search(CustomTestClass(2));
        CHECK(result != nullptr);
    }
    SECTION("Item doesn't exist")
    {
        CustomTestClass *result = set.search(CustomTestClass(5));
        CHECK(result == nullptr);
    }
}

TEST_CASE("common_data_structures_implementations::RBTree items can be modified through search()",
          "[RBTree]")
{
    RBTree<CustomTestClass> set;
    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    CustomTestClass *result = set.search(CustomTestClass(2));
    *result = 3;
    CustomTestClass *result2 = set.search(CustomTestClass(3));
    CHECK(result != nullptr);
}

class SampleRBTreeForTest
{
public:
    std::vector<int> values{10, 20, 30, 40, 50};
    RBTree<int> tree;

    SampleRBTreeForTest()
    {
        for (std::size_t i = 0; i < values.size(); ++i)
            tree.insert(values[i]);
    }
};

TEST_CASE("common_data_structures_implementations::RBTree::contains() returns propper value",
          "[RBTree]")
{
    SampleRBTreeForTest sample;

    SECTION("Item exists")
    {
        CHECK(sample.tree.contains(20));
    }
    SECTION("Item doesn't exist")
    {
        CHECK_FALSE(sample.tree.contains(100));
    }
}

TEST_CASE("BinarySearchTree::Iterator can be used to iterate all values stored in a tree",
          "[RBTree]")
{
    SampleRBTreeForTest sample;
    auto valueIterator = sample.values.begin();

    for (auto it = sample.tree.begin(); it != sample.tree.end(); ++it) {
        CHECK(**it == *valueIterator);
        ++valueIterator;
    }

    CHECK(valueIterator == sample.values.end()); // Ensure there are no more values in the tree
}
