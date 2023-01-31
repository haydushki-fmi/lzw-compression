# Add a target for the unit tests
add_executable(test_target)

target_link_libraries(
        test_target
        PRIVATE
                Catch2::Catch2WithMain
                compression
                archiving
)

target_include_directories(
        test_target
        PRIVATE
                ${CMAKE_SOURCE_DIR}/src
)

add_subdirectory(compression)
add_subdirectory(archiving)
add_subdirectory(common_data_structures)

# Automatically register all tests
catch_discover_tests(test_target)

# add_test(test_all test_target)
