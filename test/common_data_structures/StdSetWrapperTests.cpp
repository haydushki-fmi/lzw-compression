#include "catch2/catch_all.hpp"
#include "common_data_structures/implementations/StdSetWrapper.hpp"

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

TEST_CASE("common_data_structures_implementations::StdSetWrapper::size() returns correct size")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    CHECK(set.size() == 0);

    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    CHECK(set.size() == 2);
}

TEST_CASE("common_data_structures_implementations::StdSetWrapper can be inserted into")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    CHECK(set.size() == 0);

    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    CHECK(set.size() == 2);
}

TEST_CASE(
    "common_data_structures_implementations::StdSetWrapper::remove() removes items as it should")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    set.remove(CustomTestClass(2));

    CHECK(set.size() == 1);
}

TEST_CASE("common_data_structures_implementations::StdSetWrapper::search() searches correctly")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
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

TEST_CASE(
    "common_data_structures_implementations::StdSetWrapper items can be modified through search()")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    CustomTestClass *result = set.search(CustomTestClass(2));
    *result = 3;
    CustomTestClass *result2 = set.search(CustomTestClass(3));
    CHECK(result != nullptr);
}

TEST_CASE("common_data_structures_implementations::StdSetWrapper::contains() returns propper value")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    SECTION("Item exists")
    {
        bool result = set.contains(CustomTestClass(2));
        CHECK(result);
    }
    SECTION("Item doesn't exist")
    {
        bool result = set.contains(CustomTestClass(5));
        CHECK_FALSE(result);
    }
}

TEST_CASE("common_data_structures_implementations::StdSetWrapper::at() gives access to item with a "
          "valid index")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    CHECK(set.at(0).getData() == 1);
    CHECK(set.at(1).getData() == 2);
}

TEST_CASE(
    "common_data_structures_implementations::StdSetWrapper::at() throws when index is invalid")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;

    CHECK_THROWS_AS(set.at(0), std::invalid_argument);

    set.insert(CustomTestClass(1));

    CHECK_THROWS_AS(set.at(1), std::invalid_argument);
}

TEST_CASE(
    "common_data_structures_implementations::StdSetWrapper items can be modified through at()")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    set.insert(CustomTestClass(1));
    set.insert(CustomTestClass(2));

    set.at(1) = 3;
    CHECK(set.at(1).getData() == 3);
}

TEST_CASE(
    "common_data_structures_implementations::StdSetWrapper can be accessed through Set interface")
{
    common_data_structures_implementations::StdSetWrapper<CustomTestClass> set;
    common_data_structures::Set<CustomTestClass> &interface = set;
    interface.insert(CustomTestClass(1));
    interface.insert(CustomTestClass(2));

    CHECK(interface.size() == 2);
}
