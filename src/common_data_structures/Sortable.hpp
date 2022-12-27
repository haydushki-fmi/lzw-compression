#ifndef SORTABLE_HPP
#define SORTABLE_HPP

#include <concepts>

namespace common_data_structures {

/**
 * @brief Represents a requirement for a sortable item to be used in Set.
 */
template<class T>
concept Sortable = requires(T a, T b)
{
    {
        a == b
        } -> std::same_as<bool>; // TODO: Why doesn't boolean-testable work?
    {
        a < b
        } -> std::same_as<bool>;
};

} // namespace common_data_structures

#endif // SORTABLE_HPP
