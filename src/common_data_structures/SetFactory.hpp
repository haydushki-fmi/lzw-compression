#ifndef SETFACTORY_HPP
#define SETFACTORY_HPP

#include "common_data_structures/Set.hpp"
#include <string>

namespace common_data_structures {

// TODO: Add docs
class SetFactory
{
private:
    SetFactory() = default;

public:
    static SetFactory &getSetFactory();

    template<class T>
    requires Sortable<T> static Set<T> &createSet(std::string type)
    {
        // TODO: Implement
    }
};
} // namespace common_data_structures

#endif // SETFACTORY_HPP
