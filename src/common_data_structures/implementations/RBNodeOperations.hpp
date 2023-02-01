#ifndef RBNODEOPERATIONS_HPP
#define RBNODEOPERATIONS_HPP

#include "common_data_structures/Sortable.hpp"
#include "common_data_structures/implementations/RBNode.hpp"

/**
 * @brief Holds operations for RBNodes.
 */
template<typename T>
requires common_data_structures::Sortable<T> class RBNodeOPerations
{
public:
    /**
     * @brief Checks if two trees have the same values.
     * @param a
     * @param b
     * @return True if trees are the same
     */
    static bool sameTrees(const RBNode<T> *a, const RBNode<T> *b)
    {
        if (a == nullptr || b == nullptr)
            return a == b;

        return a->data == b->data && sameTrees(a->left, b->left) && sameTrees(a->right, b->right);
    }

    /**
     * @brief Returns a reference to the pointer to which a given value is or would be attached.
     * @param startFrom Pointer to the root element of the tree
     * @param value
     * @return Reference to a pointer of a node where the value is present or a pointer where it should be added
     */
    static RBNode<T> *&findPointerTo(RBNode<T> *&startFrom, const T &value)
    {
        if (startFrom == nullptr || startFrom->data == value) {
            return startFrom;
        }
        return findPointerTo(startFrom->whichSuccessorWouldStore(value), value);
    }

    /**
     * @brief Rotate left around a node.
     * @param nodeAround Node to rotate around
     */
    static void rotateLeft(RBNode<T> *nodeAround)
    {
        // TODO: implement
    }

    /**
     * @brief Rotate right around a node.
     * @param nodeAround Node to rotate around
     */
    static void rotateRight(RBNode<T> *nodeAround)
    {
        // TODO: implement
    }

    /**
     * @brief Inserts a given node in the tree pointed by rootptr. Node itself will be inserted without copying.
     * @param rootptr Pointer to the tree to insert into
     * @param node Node to insert
     */
    static void insert(RBNode<T> *&rootptr, RBNode<T> &node)
    {
        findPointerTo(rootptr, node.data) = &node;
        // TODO: rebalance
    }

    /**
     * @brief Release the memory allocated for a tree pointed by rootptr.
     * @param rootptr Pointer to the tree root
     */
    static void release(RBNode<T> *rootptr)
    {
        if (rootptr) {
            release(rootptr->left);
            release(rootptr->right);
            delete rootptr;
        }
    }
};

#endif // RBNODEOPERATIONS_HPP
