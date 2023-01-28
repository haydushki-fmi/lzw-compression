add_executable(app)

target_link_libraries(
        app
        PRIVATE
            archiving
            common_data_structures
            compression
)

# Currently all .cpp files are listed here.
# You may want to switch to a more flexible configuration if you work with a large number of packages/files
target_sources(
        app
        PRIVATE
        Engine.hpp
        Engine.cpp
        main.cpp
)
