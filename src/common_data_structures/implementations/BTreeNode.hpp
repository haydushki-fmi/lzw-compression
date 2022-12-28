#ifndef BTREENODE_HPP
#define BTREENODE_HPP

#include "common_data_structures/Sortable.hpp"
#include <vector>

/**
 * @brief Represents a node in the B-Tree. Template class must be Sortable.
 */
template<class T>
requires common_data_structures::Sortable<T> class BTreeNode
{
public:
    /**
     * @brief Creates an empty node.
     * @param degree Degree of the node.
     * @param isLeaf Whether the node has children.
     */
    BTreeNode(std::size_t degree, bool isLeaf)
        : degree(degree)
        , isLeaf(isLeaf)
        , keyCount(0)
        , keys(nullptr)
        , children(nullptr)
    {
        this->keys = new T[this->getMaximumKeyCount()];
        try {
            if (!this->isLeaf) {
                this->initChildren();
            }
        } catch (...) {
            // If memory allocation for children fails delete keys memory.
            this->deleteKeys();
            throw;
        }
    }

    BTreeNode(const BTreeNode<T> &other) = delete;
    BTreeNode<T> &operator=(const BTreeNode<T> &other) = delete;

    ~BTreeNode()
    {
        if (!this->isLeaf) {
            this->deleteChildren();
        }
        this->deleteKeys();
    }

    /**
     * @brief Traverses all nodes in the subtree of this. For debug purposes.
     * @param result Vector to write into the traversed nodes' keys.
     */
    void traverse(std::vector<T> &result)
    {
        std::size_t i;
        for (i = 0; i < this->keyCount; ++i) {
            if (!this->isLeaf) {
                this->children[i]->traverse(result);
            }
            result.push_back(this->keys[i]);
        }

        if (!this->isLeaf) {
            this->children[i]->traverse(result);
        }
    }

    /**
     * @brief Search for a node with a specific key in the subtree of this.
     * @param key Key to search for.
     * @return Pointer to found node. nullptr if not found.
     */
    BTreeNode<T> *search(const T &key); // TODO: implement

    /**
     * @brief Array of the node keys.
     */
    T *keys;

    /**
     * @brief Maximum degree of the node. Defines the range for number of keys.
     */
    std::size_t degree;

    /**
     * @brief Number of keys currently present in the node.
     */
    std::size_t keyCount;

    /**
     * @brief True if the node is a leaf.
     */
    bool isLeaf;

    /**
     * @brief Array of pointers to child nodes.
     */
    BTreeNode<T> **children;

private:
    std::size_t getMaximumKeyCount() { return this->degree * 2 - 1; }
    std::size_t getMaximumChildCount() { return this->degree * 2; }

    void initChildren()
    {
        this->children = new BTreeNode<T> *[this->getMaximumChildCount()];
        for (std::size_t i = 0; i < this->getMaximumChildCount(); ++i) {
            this->children[i] = nullptr;
        }
    }

    void deleteKeys() { delete[] this->keys; }
    void deleteChildren()
    {
        for (std::size_t i = 0; i < this->getMaximumChildCount(); ++i) {
            delete this->children[i];
        }
        delete[] this->children;
    }
};

#endif // BTREENODE_HPP
