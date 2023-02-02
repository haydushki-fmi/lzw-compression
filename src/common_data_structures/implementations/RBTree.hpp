#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "common_data_structures/implementations/RBNode.hpp"
#include "common_data_structures/implementations/RBNodeIterator.hpp"
#include "common_data_structures/implementations/RBNodeOperations.hpp"

/**
 * @brief Implementation of a Red-Black tree.
 */
template<typename T>
class RBTree
{
    using NodeType = RBNode<T>;

    NodeType *rootptr = nullptr;
    std::size_t elementsCount = 0;

public:
    class Iterator
    {
        RBNodeIterator<T> it;

    public:
        Iterator(NodeType *startFrom)
            : it(startFrom)
        {}

        T &operator*() { return it->data; }

        T *operator->() { return &it->data; }

        void operator++() { ++it; }

        bool operator==(const Iterator &other) { return it == other.it; }

        bool operator!=(const Iterator &other) { return it != other.it; }
    };

public:
    RBTree() = default;
    RBTree(const RBTree &other) = delete;
    RBTree &operator=(const RBTree &other) = delete;

    ~RBTree() { this->clear(); }

    /**
     * @brief Insert an item into the set.
     * @param item Item to be inserted.
     */
    void insert(const T &item)
    {
        NodeType *toAdd = new NodeType(item);
        try {
            RBNodeOPerations<T>::insert(this->rootptr, *toAdd);
        } catch (...) {
            delete toAdd;
        }
        this->elementsCount++;
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
        // TODO: implement
        throw;
    }

    /**
     * @brief Search for an item in the set.
     * @param item Item to search for.
     * @return Pointer to the desired item. Nullptr if item doesn't exist.
     */
    const T *search(const T &item) const
    {
        const T *res = &(RBNodeOPerations<T>::findPointerTo(this->rootptr, item)->data);
        return res;
    }

    /**
     * @brief Search for an item in the set.
     * @param item Item to search for.
     * @return Pointer to the desired item. Nullptr if item doesn't exist.
     */
    T *search(const T &item)
    {
        return &(RBNodeOPerations<T>::findPointerTo(this->rootptr, item)->data);
    }

    /**
     * @brief Get the number of items in the set.
     * @return Size of the set.
     */
    std::size_t size() const { return this->elementsCount; }

    /**
     * @brief Iterator begin.
     */
    auto begin() { return Iterator(this->rootptr); }

    /**
     * @brief Iterator end.
     */
    auto end() { return Iterator(nullptr); }

    /**
     * @brief Const iterator begin.
     */
    auto begin() const { return Iterator(this->rootptr); }

    /**
     * @brief Const iterator end.
     */
    auto end() const { return Iterator(nullptr); }

private:
    void clear()
    {
        RBNodeOPerations<T>::release(rootptr);
        this->rootptr = nullptr;
        this->elementsCount = 0;
    }
};

#endif // RBTREE_HPP
