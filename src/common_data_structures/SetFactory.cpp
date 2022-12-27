#include "SetFactory.hpp"

common_data_structures::SetFactory &
common_data_structures::SetFactory::getSetFactory() {
    static SetFactory theFactory;
    return theFactory;
}
