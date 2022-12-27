#ifndef SET_HPP
#define SET_HPP

#include "common_data_structures/Sortable.hpp"
namespace common_data_structures {

/**
 * @brief Represents a Set interface.
 */
template<class T>
requires Sortable<T> // TODO: Use std::totally_ordered?
    class Set
{
public:
    /**
   * @brief Insert an item into the set.
   * @param item Item to be inserted.
   */
    virtual void insert(const T &item) = 0;

    /**
    * @brief Check if an item is present in the set.
    * @param item Item to check for.
    * @return True if item is present in the set.
    */
    virtual bool contains(const T &item) = 0;

    /**
    * @brief Remove an item from the set.
    * @param item Item to be removed.
    */
    virtual void remove(const T &item) = 0;

    /**
    * @brief Search for an item in the set
    * @param item Item to search for.
    * @return Reference to the desired item. Nullptr if item doesn't exist.
    */
    virtual const T &search(const T &item) const = 0;

    /**
    * @brief Search for an item in the set
    * @param item Item to search for.
    * @return Reference to the desired item. Nullptr if item doesn't exist.
    */
    virtual T &search(const T &item) = 0;

    // TODO: Add iterator stuff
};
} // namespace common_data_structures

#endif // SET_HPP
