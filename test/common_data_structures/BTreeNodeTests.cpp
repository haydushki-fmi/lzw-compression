#include "SampleBTree.hpp"
#include "catch2/catch_all.hpp"

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
    SampleBTree st;
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
