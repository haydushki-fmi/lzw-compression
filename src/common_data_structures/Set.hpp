#ifndef SET_HPP
#define SET_HPP

#include "common_data_structures/Sortable.hpp"

namespace common_data_structures {

/**
 * @brief Represents a Set interface.
 */
template<class T> // TODO: Use std::totally_ordered?
requires Sortable<T> class Set
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
    virtual bool contains(const T &item) const = 0;

    /**
    * @brief Remove an item from the set.
    * @param item Item to be removed.
    */
    virtual void remove(const T &item) = 0;

    /**
    * @brief Search for an item in the set.
    * @param item Item to search for.
    * @return Pointer to the desired item. Nullptr if item doesn't exist.
    */
    virtual const T *search(const T &item) const = 0;

    /**
    * @brief Search for an item in the set.
    * @param item Item to search for.
    * @return Pointer to the desired item. Nullptr if item doesn't exist.
    */
    virtual T *search(const T &item) = 0;

    /**
     * @brief Get the number of items in the st.
     * @return Size of the set.
     */
    virtual std::size_t size() const = 0;

    /**
     * @brief Get item at index.
     * @param index Index to get item at.
     * @return Reference to the desired item.
     * @throws std::invalid_argument when index is invalid.
     */
    virtual const T &at(std::size_t index) const = 0;

    /**
     * @brief Get item at index.
     * @param index Index to get item at.
     * @return Reference to the desired item.
     * @throws std::invalid_argument when index is invalid.
     */
    virtual T &at(std::size_t index) = 0;
};
} // namespace common_data_structures

#endif // SET_HPP
