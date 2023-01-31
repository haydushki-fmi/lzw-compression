#ifndef STDSETWRAPPER_HPP
#define STDSETWRAPPER_HPP

#include "common_data_structures/Sortable.hpp"
#include <set>
#include <stdexcept>

namespace common_data_structures_implementations {

/**
 * @brief Wrapper class for std::set.
 */
template<class T>
requires common_data_structures::Sortable<T> class StdSetWrapper
{
public:
    StdSetWrapper() = default;
    StdSetWrapper(const StdSetWrapper &other) = delete;
    StdSetWrapper &operator=(const StdSetWrapper &other) = delete;
    ~StdSetWrapper()
    {
        for (auto item : this->data) {
            delete item;
        }
    }

public:
    /**
     * @brief Insert an item into the set.
     * @param item Item to be inserted.
     */
    void insert(const T &item)
    {
        T *toAdd = new T(item);
        try {
            this->data.insert(toAdd);
        } catch (...) {
            delete toAdd;
        }
    }

    /**
     * @brief Check if an item is present in the set.
     * @param item Item to check for.
     * @return True if item is present in the set.
     */
    bool contains(const T &item) const { return this->search(item) != nullptr; }

    /**
     * @brief Remove an item from the set.
     * @param item Item to be removed.
     */
    void remove(const T &item)
    {
        T *toDelete = this->search(item);
        if (toDelete) {
            delete toDelete;
            this->data.erase(toDelete);
        }
    }

    /**
     * @brief Search for an item in the set.
     * @param item Item to search for.
     * @return Pointer to the desired item. Nullptr if item doesn't exist.
     */
    const T *search(const T &item) const
    {
        for (auto i : this->data) {
            if (*i == item) {
                return i;
            }
        }
        return nullptr;
    }

    /**
     * @brief Search for an item in the set.
     * @param item Item to search for.
     * @return Pointer to the desired item. Nullptr if item doesn't exist.
     */
    T *search(const T &item)
    {
        for (auto i : this->data) {
            if (*i == item) {
                return i;
            }
        }
        return nullptr;
    }

    /**
     * @brief Get the number of items in the set.
     * @return Size of the set.
     */
    std::size_t size() const { return this->data.size(); }

    /**
     * @brief Iterator begin.
     */
    auto begin() { return this->data.begin(); }

    /**
     * @brief Iterator end.
     */
    auto end() { return this->data.end(); }

    /**
     * @brief Const iterator begin.
     */
    auto begin() const { return this->data.cbegin(); }

    /**
     * @brief Const iterator end.
     */
    auto end() const { return this->data.cend(); }

private:
    std::set<T *> data;
};

} // namespace common_data_structures_implementations
#endif // STDSETWRAPPER_HPP
