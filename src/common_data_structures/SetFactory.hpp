#ifndef SETFACTORY_HPP
#define SETFACTORY_HPP

#include "common_data_structures/Set.hpp"
#include "common_data_structures/implementations/StdSetWrapper.hpp"
#include <string>

namespace common_data_structures {

/**
 * @brief Singleton factory class for creating sets.
 */
class SetFactory
{
private:
    SetFactory() = default;

public:
    /**
     * @brief Returns the instance of the factory.
     * @return Instance of the factory.
     */
    static SetFactory &getSetFactory()
    {
        static SetFactory theFactory;
        return theFactory;
    }

    /**
     * @brief Creates a Set of a given type.
     * @param type Type of the set.
     * @return Created set.
     * @throws std::invalid_argument when set type is invalid.
     */
    template<class T>
    requires Sortable<T> Set<T> *createSet(std::string type)
    {
        if (type == "StdSetWrapper") {
            return new common_data_structures_implementations::StdSetWrapper<T>();
        }
        throw std::invalid_argument("Invalid set type!");
    }
};
} // namespace common_data_structures

#endif // SETFACTORY_HPP
