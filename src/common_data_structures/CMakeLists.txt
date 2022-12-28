add_library(common_data_structures STATIC)

target_sources(
        common_data_structures
        PRIVATE
        Sortable.hpp
        Set.hpp
        SetFactory.hpp
        SetFactory.cpp
        implementations/BTreeNode.hpp
)
