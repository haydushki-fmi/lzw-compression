add_library(common_data_structures STATIC)

target_sources(
        common_data_structures
        PRIVATE
        Sortable.hpp
        implementations/BTreeNode.hpp
        implementations/StdSetWrapper.hpp
        implementations/RBNode.hpp
        implementations/RBNodeOperations.hpp
        unused.cpp
)
