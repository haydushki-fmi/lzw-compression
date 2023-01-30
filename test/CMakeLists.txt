# Add a target for the unit tests
add_executable(test_target)

target_link_libraries(
        test_target
        PRIVATE
                Catch2::Catch2WithMain
                compression
                archiving
)

# Currently all .cpp files are listed here.
# You may want to switch to a more flexible configuration if you work with a large number of packages/files
target_sources(
        test_target
        PRIVATE
        common_data_structures/SetFactoryTests.cpp
        common_data_structures/BTreeNodeTests.cpp
        common_data_structures/StdSetWrapperTests.cpp
)


target_include_directories(
        test_target
        PRIVATE
                ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(compression)
add_subdirectory(archiving)

# Automatically register all tests
catch_discover_tests(test_target)

# add_test(test_all test_target)
