#ifndef RBNODEITERATOR_HPP
#define RBNODEITERATOR_HPP

#include "common_data_structures/implementations/RBNode.hpp"
#include <cassert>
#include <stack>
#include <stdexcept>
#include <vector>

/**
 * @brief Iterator class for RBNodes.
 */
template<typename T>
class RBNodeIterator
{
public:
    using NodeType = RBNode<T>;

private:
    /**
     * @brief Used for backtracking.
     */
    std::stack<NodeType *> st;

private:
    void pushAllTheWayToTheLeft(NodeType *startFrom)
    {
        for (; startFrom; startFrom = startFrom->left)
            this->st.push(startFrom);
    }

public:
    /**
     * @brief Constructs a new iterator.
     * @param startFrom Pointer to the node to start from
     */
    RBNodeIterator(NodeType *startFrom) { pushAllTheWayToTheLeft(startFrom); }

    /**
     * @brief Returns whether iterator has reached the end.
     * @return True if iterator is at the end
     */
    bool atEnd() const { return st.empty(); }

    /**
     * @brief Element access.
     * @return
     */
    NodeType &operator*()
    {
        if (this->atEnd()) {
            throw std::runtime_error("Error iterating RB tree!");
        }

        return *this->st.top();
    }

    /**
     * @brief Element access.
     * @return
     */
    NodeType *operator->()
    {
        if (this->atEnd()) {
            throw std::runtime_error("Error iterating RB tree!");
        }

        return this->st.top();
    }

    /**
     * @brief Moves iterator forward.
     */
    void operator++()
    {
        if (this->atEnd()) {
            throw std::runtime_error("Error iterating RB tree!");
        }

        NodeType *p = this->st.top();
        this->st.pop();
        this->pushAllTheWayToTheLeft(p->right);
    }

    /**
     * @brief Compares two iterators.
     * @param other Iterator to compare to
     * @return True if itertors point at the same node or at the end
     */
    bool operator==(const RBNodeIterator &other) const
    {
        if (this->atEnd() || other.atEnd())
            return this->atEnd() == other.atEnd();

        return this->st.top() == other.st.top();
    }

    /**
     * @brief Compares two iterators.
     * @param other Iterator to compare to
     * @return True if itertors DO NOT point at the same node or one is at the end while the other isn't
     */
    bool operator!=(const RBNodeIterator &other) const { return !this->operator==(other); }
};

#endif // RBNODEITERATOR_HPP
