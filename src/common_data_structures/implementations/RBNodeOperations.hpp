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

    static RBNode<T> *const &findPointerTo(RBNode<T> *const &startFrom, const T &value)
    {
        if (startFrom == nullptr || startFrom->data == value) {
            return startFrom;
        }
        return findPointerTo(startFrom->whichSuccessorWouldStore(value), value);
    }

    /**
     * @brief Returns a reference to the pointer to which a given value is or would be attached and finds the parent node.
     * @param startFrom Pointer to the root element of the tree
     * @param value
     * @param parent Pointer to the parent node will be written onto it.
     * @return Reference to a pointer of a node where the value is present or a pointer where it should be added
     */
    static RBNode<T> *&findPointerToWithParent(RBNode<T> *&startFrom,
                                               const T &value,
                                               RBNode<T> *&parent)
    {
        RBNode<T> **result = &startFrom;
        RBNode<T> **previousResult = nullptr;

        while (*result != nullptr && (*result)->data != value) {
            previousResult = result;
            result = &(*result)->whichSuccessorWouldStore(value);
        }

        parent = previousResult ? *previousResult : nullptr;
        return *result;
    }

    /**
     * @brief Rotate left around a node.
     * @param rootptr Pointer to the root of the (sub)tree
     * @param nodeAround Node to rotate around
     */
    static void rotateLeft(RBNode<T> *&rootptr, RBNode<T> *nodeAround)
    {
        RBNode<T> *y = nodeAround->right;
        nodeAround->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = nodeAround;
        }
        y->parent = nodeAround->parent;
        if (nodeAround->parent == nullptr) {
            rootptr = y;
        } else if (nodeAround == nodeAround->parent->left) {
            nodeAround->parent->left = y;
        } else {
            nodeAround->parent->right = y;
        }
        y->left = nodeAround;
        nodeAround->parent = y;
    }

    /**
     * @brief Rotate right around a node.
     * @param rootptr Pointer to the root of the (sub)tree
     * @param nodeAround Node to rotate around
     */
    static void rotateRight(RBNode<T> *&rootptr, RBNode<T> *nodeAround)
    {
        RBNode<T> *y = nodeAround->left;
        nodeAround->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = nodeAround;
        }
        y->parent = nodeAround->parent;
        if (nodeAround->parent == nullptr) {
            rootptr = y;
        } else if (nodeAround == nodeAround->parent->right) {
            nodeAround->parent->right = y;
        } else {
            nodeAround->parent->left = y;
        }
        y->right = nodeAround;
        nodeAround->parent = y;
    }

    /**
     * @brief Inserts a given node in the tree pointed by rootptr. Node itself will be inserted without copying.
     * @param rootptr Pointer to the tree to insert into
     * @param node Node to insert
     */
    static void insert(RBNode<T> *&rootptr, RBNode<T> &node)
    {
        RBNode<T> *parentPointer = nullptr;
        findPointerToWithParent(rootptr, node.data, parentPointer) = &node;
        node.parent = parentPointer;

        if (parentPointer == nullptr) {
            node.colour = 0;
            return; // New node is the new root of the tree
        }

        if (!node.getGrandparent()) {
            return;
        }

        RBNode<T> *currentNode = &node;
        RBNode<T> *uncle;

        while (currentNode && currentNode->parent && currentNode->parent->isRed()) {
            if (currentNode->parent == currentNode->getGrandparent()->right) {
                uncle = currentNode->getGrandparent()->left;
                if (uncle && uncle->isRed()) {
                    uncle->colour = 0;
                    currentNode->parent->colour = 0;
                    currentNode->getGrandparent()->colour = 1;
                    currentNode = currentNode->getGrandparent();
                } else {
                    if (currentNode == currentNode->parent->left) {
                        currentNode = currentNode->parent;
                        rotateRight(rootptr, currentNode);
                    }
                    currentNode->parent->colour = 0;
                    currentNode->parent->parent->colour = 1;
                    rotateLeft(rootptr, currentNode->getGrandparent());
                }
            } else {
                uncle = currentNode->getGrandparent()->right;

                if (uncle && uncle->isRed()) {
                    uncle->colour = 0;
                    currentNode->parent->colour = 0;
                    currentNode->getGrandparent()->colour = 1;
                    currentNode = currentNode->getGrandparent();
                } else {
                    if (currentNode == currentNode->parent->right) {
                        currentNode = currentNode->parent;
                        rotateLeft(rootptr, currentNode);
                    }
                    currentNode->parent->colour = 0;
                    currentNode->getGrandparent()->colour = 1;
                    rotateRight(rootptr, currentNode->getGrandparent());
                }
            }
            if (currentNode == rootptr) {
                break;
            }
        }
        rootptr->colour = 0;
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
