#ifndef RBNODE_HPP
#define RBNODE_HPP

#include "common_data_structures/Sortable.hpp"

/**
 * @brief Represents a node in a Red-Black tree.
 */
template<typename T>
requires common_data_structures::Sortable<T> class RBNode
{
public:
    /**
     * @brief Data which the node holds.
     */
    T data = T();

    /**
     * @brief Pointer to the left child of the node.
     */
    RBNode *left = nullptr;

    /**
     * @brief Pointer to the right child of the node.
     */
    RBNode *right = nullptr;

    /**
     * @brief True for red, false for black.
     */
    bool colour = 1;

public:
    /**
     * @brief Constructs a RBNode with default data.
     */
    RBNode() {}

    /**
     * @brief Constructs a RBNode with specified data.
     * @param data Data for the node to hold
     */
    RBNode(const T &data)
        : data(data)
    {
        this->setColour();
    }

    /**
     * @brief Constructs a RBNode with specified data and children.
     * @param data Data for the node to hold
     * @param left Left child of the node
     * @param right Right child of the node
     */
    RBNode(const T &data, RBNode *left, RBNode *right)
        : data(data)
        , left(left)
        , right(right)
    {
        this->setColour();
    }

    /**
     * @brief Automatically sets the node colour based upon it's children.
     */
    void setColour()
    {
        // Every laef node is red.
        if (this->isLeaf()) {
            this->colour = 1;
            return;
        }

        // If there are children, check their colours.
        if (this->hasLeftSuccessor() && this->hasRightSuccessor()) {
            this->colour = this->left->isBlack() && this->right->isBlack();
            return;
        }

        // If there's only one children
        this->colour = 0;
    }

    /**
     * @brief Returns if the node has red colour.
     * @return True if node is red.
     */
    bool isRed() { return this->colour; }

    /**
     * @brief Returns if the node has black colour.
     * @return True if node is black.
     */
    bool isBlack() { return !this->colour; }

    /**
     * @brief Returns whether the node is a leaf.
     * @return True if the node has no children (is a leaf).
     */
    bool isLeaf() const noexcept { return left == nullptr && right == nullptr; }

    /**
     * @brief Returns whether the node has a left child.
     * @return True if the node has a left child.
     */
    bool hasLeftSuccessor() const noexcept { return left != nullptr; }

    /**
     * @brief Returns whether the node has a right child.
     * @return True if the node has a right child.
     */
    bool hasRightSuccessor() const noexcept { return right != nullptr; }

    /**
     * @brief Returns a reference to the successor pointer to which value belongs.
     * @param value
     * @return Reference to left if value is less than data in this node. Otherwise to the right.
     */
    RBNode *&whichSuccessorWouldStore(const T &value) { return (value < data) ? left : right; }

    /**
     * @brief Sets both child pointers to nullptr making the node into a leaf.
     */
    void detachSuccessors()
    {
        left = nullptr;
        right = nullptr;
    }
};

#endif // RBNODE_HPP
