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
    // Use this so that std::vector can be easily replaced with a custom class.
    template<class U>
    using dynamicArrayType = std::vector<U>;

public:
    /**
     * @brief Creates an empty node.
     * @param degree Degree of the node.
     * @param isLeaf Whether the node has children.
     */
    BTreeNode(std::size_t degree, bool isLeaf)
        : degree(degree)
        , isLeaf(isLeaf)
    {
        this->keys.reserve(this->getMaximumKeyCount());
        if (!this->isLeaf) {
            this->initChildren();
        }
    }

    // TODO: implement
    BTreeNode(const BTreeNode<T> &other) = delete;
    BTreeNode<T> &operator=(const BTreeNode<T> &other) = delete;

    ~BTreeNode() { this->deleteChildren(); }

    /**
     * @brief Traverses all nodes in the subtree of this. For debug purposes.
     * @param result Vector to write into the traversed nodes' keys.
     */
    void traverse(std::vector<T> &result)
    {
        std::size_t i;
        for (i = 0; i < this->keys.size(); ++i) {
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
    dynamicArrayType<T> keys;

    /**
     * @brief Maximum degree of the node. Defines the range for number of keys.
     */
    std::size_t degree;

    /**
     * @brief Array of pointers to child nodes.
     */
    dynamicArrayType<BTreeNode<T> *> children;

    /**
     * @brief True if the node is a leaf.
     */
    bool isLeaf;

private:
    std::size_t getMaximumKeyCount() const { return this->degree * 2 - 1; }
    std::size_t getMaximumChildCount() const { return this->degree * 2; }

    void initChildren() { this->children.reserve(this->getMaximumChildCount()); }

    void deleteChildren()
    {
        for (std::size_t i = 0; i < this->children.size(); ++i) {
            delete this->children[i];
        }
    }
};

#endif // BTREENODE_HPP
