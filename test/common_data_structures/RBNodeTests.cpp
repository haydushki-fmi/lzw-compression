#include "catch2/catch_all.hpp"
#include "common_data_structures/implementations/RBNode.hpp"

const int RANDOM_VALUE = 666;
class CustomTestClass
{
private:
    int data;

public:
    CustomTestClass()
        : data(RANDOM_VALUE)
    {}
    CustomTestClass(int data)
        : data(data)
    {}

    int getData() const { return this->data; }
    bool operator==(const CustomTestClass &other) const { return this->data == other.data; }
    bool operator<(const CustomTestClass &other) const { return this->data < other.data; }
};

TEMPLATE_TEST_CASE("RBNode::RBNode() constructs a leaf node with a default data",
                   "[RBTreeNode]",
                   int,
                   CustomTestClass)
{
    RBNode<TestType> n;

    REQUIRE(n.data == TestType());
    REQUIRE(n.left == nullptr);
    REQUIRE(n.right == nullptr);
    REQUIRE(n.isLeaf());
    REQUIRE(n.colour);
}

TEST_CASE("RBNode::RBNode(T, RBNode*, RBNode*) constructs a node with correct values",
          "[RBTreeNode]")
{
    const int someRandomValue = 123;
    RBNode<int> left, right;

    RBNode<int> n(someRandomValue, &left, &right);

    REQUIRE(n.data == someRandomValue);
    REQUIRE(n.left == &left);
    REQUIRE(n.right == &right);
    REQUIRE_FALSE(n.colour);
}

TEST_CASE("RBNode::isLeaf() returns true for leaf nodes", "[RBTreeNode]")
{
    RBNode<int> n;
    REQUIRE(n.isLeaf());
}

TEST_CASE("RBNode::isLeaf() returns false for non-leaf nodes", "[RBTreeNode]")
{
    RBNode<int> left, right;

    SECTION("RBNode with a single successor on the left")
    {
        REQUIRE_FALSE(RBNode<int>(RANDOM_VALUE, &left, nullptr).isLeaf());
    }
    SECTION("RBNode with a single successor on the right")
    {
        REQUIRE_FALSE(RBNode<int>(RANDOM_VALUE, nullptr, &right).isLeaf());
    }
    SECTION("RBNode with two successors")
    {
        REQUIRE_FALSE(RBNode<int>(RANDOM_VALUE, &left, &right).isLeaf());
    }
}

TEST_CASE("RBNode::hasLeftSuccessor() return true when a node has a left successor", "[RBTreeNode]")
{
    RBNode<int> left;
    RBNode<int> node(RANDOM_VALUE, &left, nullptr);

    SECTION("For nodes with only a left successor")
    {
        REQUIRE(node.hasLeftSuccessor());
    }
    SECTION("For nodes with both successors")
    {
        RBNode<int> right;
        node.right = &right;
        REQUIRE(node.hasLeftSuccessor());
    }
}

TEST_CASE("RBNode::hasLeftSuccessor() return false when a node DOES NOT have a left successor",
          "[RBTreeNode]")
{
    RBNode<int> node;

    SECTION("For leaf nodes")
    {
        REQUIRE_FALSE(node.hasLeftSuccessor());
    }
    SECTION("For nodes with only a right successor")
    {
        RBNode<int> right;
        node.right = &right;
        REQUIRE_FALSE(node.hasLeftSuccessor());
    }
}

TEST_CASE("RBNode::hasRightSuccessor() return true when a node has a right successor",
          "[RBTreeNode]")
{
    RBNode<int> right;
    RBNode<int> node(RANDOM_VALUE, nullptr, &right);

    SECTION("For nodes with only a right successor")
    {
        REQUIRE(node.hasRightSuccessor());
    }
    SECTION("For nodes with both successors")
    {
        RBNode<int> left;
        node.left = &left;
        REQUIRE(node.hasRightSuccessor());
    }
}

TEST_CASE("RBNode::hasRightSuccessor() return false when a node DOES NOT have a right successor",
          "[RBTreeNode]")
{
    RBNode<int> node;

    SECTION("For leaf nodes")
    {
        REQUIRE_FALSE(node.hasRightSuccessor());
    }
    SECTION("For nodes with only a left successor")
    {
        RBNode<int> left;
        node.left = &left;
        REQUIRE_FALSE(node.hasRightSuccessor());
    }
}

TEST_CASE("RBNode::setColour() sets the right node colour", "[RBTreeNode]")
{
    SECTION("Leaf node")
    {
        RBNode<CustomTestClass> node;
        node.setColour();
        CHECK(node.colour);
    }

    SECTION("Node after adding a left successor")
    {
        RBNode<CustomTestClass> left;
        RBNode<CustomTestClass> node;
        CHECK(node.colour);

        node.left = &left;
        node.setColour();

        CHECK_FALSE(node.colour);
    }

    SECTION("Node after adding a right successor")
    {
        RBNode<CustomTestClass> right;
        RBNode<CustomTestClass> node;
        CHECK(node.colour);

        node.left = &right;
        node.setColour();

        CHECK_FALSE(node.colour);
    }

    SECTION("Node after changing child's colour")
    {
        RBNode<CustomTestClass> left;
        RBNode<CustomTestClass> right;
        RBNode<CustomTestClass> node(RANDOM_VALUE, &left, &right);

        left.colour = 1;
        node.setColour();

        CHECK_FALSE(node.colour);
    }
}

TEST_CASE("RBNode::isRed() returns the correct value", "[RBTreeNode]")
{
    RBNode<CustomTestClass> node;

    SECTION("Red node")
    {
        CHECK(node.isRed());
    }

    SECTION("Black node")
    {
        node.colour = 0;
        CHECK_FALSE(node.isRed());
    }
}
TEST_CASE("RBNode::isBlack() returns the correct value", "[RBTreeNode]")
{
    RBNode<CustomTestClass> node;

    SECTION("Red node")
    {
        CHECK_FALSE(node.isBlack());
    }

    SECTION("Black node")
    {
        node.colour = 0;
        CHECK(node.isBlack());
    }
}

TEST_CASE("RBNode::whichSuccessorWouldStore() returns the correct successor", "[RBTreeNode]")
{
    int rootValue = 5;

    RBNode<int> left(rootValue - 10);
    RBNode<int> right(rootValue + 10);
    RBNode<int> root(rootValue, &left, &right);

    CHECK(root.whichSuccessorWouldStore(rootValue - 1) == &left);
    CHECK(root.whichSuccessorWouldStore(rootValue) == &right);
    CHECK(root.whichSuccessorWouldStore(rootValue + 1) == &right);
}

TEST_CASE("RBNode::detachSuccessors() sets both successor pointers to null", "[RBTreeNode]")
{
    RBNode<int> left;
    RBNode<int> right;
    RBNode<int> node(RANDOM_VALUE, &left, &right);

    node.detachSuccessors();

    CHECK(node.left == nullptr);
    CHECK(node.right == nullptr);
}
