#ifndef STDSETWRAPPER_HPP
#define STDSETWRAPPER_HPP

#include "common_data_structures/Set.hpp"
#include <set>
#include <stdexcept>

namespace common_data_structures_implementations {

/**
 * @brief Wrapper class for std::set.
 */
template<class T>
requires common_data_structures::Sortable<T> class StdSetWrapper
    : public common_data_structures::Set<T>
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

    // Set interface
public:
    void insert(const T &item) override
    {
        T *toAdd = new T(item);
        try {
            this->data.insert(toAdd);
        } catch (...) {
            delete toAdd;
        }
    }

    bool contains(const T &item) const override { return this->search(item) != nullptr; }

    void remove(const T &item) override
    {
        T *toDelete = this->search(item);
        if (toDelete) {
            delete toDelete;
            this->data.erase(toDelete);
        }
    }

    const T *search(const T &item) const override
    {
        for (auto i : this->data) {
            if (*i == item) {
                return i;
            }
        }
        return nullptr;
    }
    T *search(const T &item) override
    {
        for (auto i : this->data) {
            if (*i == item) {
                return i;
            }
        }
        return nullptr;
    }

    std::size_t size() const override { return this->data.size(); }

    const T &at(std::size_t index) const override
    {
        if (index >= this->size()) {
            throw std::invalid_argument("Index out of range!");
        }

        std::size_t i = 0;
        for (auto item : this->data) {
            if (i == index) {
                return *item;
            }
            i++;
        }
    }
    T &at(std::size_t index) override
    {
        if (index >= this->size()) {
            throw std::invalid_argument("Index out of range!");
        }

        std::size_t i = 0;
        for (auto item : this->data) {
            if (i == index) {
                return *item;
            }
            i++;
        }
    }

    auto begin() { return this->data.begin(); }
    auto end() { return this->data.end(); }
    auto begin() const { return this->data.cbegin(); }
    auto end() const { return this->data.cend(); }

private:
    std::set<T *> data;
};

} // namespace common_data_structures_implementations
#endif // STDSETWRAPPER_HPP
