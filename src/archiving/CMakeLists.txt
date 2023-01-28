add_library(archiving STATIC)

target_sources(
        archiving
        PRIVATE
        ArchiveItem.hpp
        ArchiveItem.cpp
        FileSystem.hpp
)

