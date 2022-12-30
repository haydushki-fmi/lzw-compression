#include "catch2/catch_all.hpp"
#include "common_data_structures/SetFactory.hpp"
#include "common_data_structures/implementations/StdSetWrapper.hpp"

TEST_CASE("common_data_structures::SetFactory::createSet() throws when invalid set type is passed")
{
    common_data_structures::SetFactory &factory = common_data_structures::SetFactory::getSetFactory();
    CHECK_THROWS_AS(factory.createSet<int>("StdSetWrapper11"), std::invalid_argument);
}

TEST_CASE("common_data_structures::SetFactory::createSet() can create StdSetWrapper")
{
    common_data_structures::SetFactory &factory = common_data_structures::SetFactory::getSetFactory();
    common_data_structures::Set<int> *set = factory.createSet<int>("StdSetWrapper");
    common_data_structures_implementations::StdSetWrapper<int> *castedSet
        = dynamic_cast<common_data_structures_implementations::StdSetWrapper<int> *>(set);

    CHECK(castedSet != nullptr);
}
