# libs/common/tests/CMakeLists.txt

add_executable(allocator_test
    allocator_test.cpp
)

target_link_libraries(allocator_test
    PRIVATE
        allocator              # links the library
        GTest::gtest_main      # links gtest
)

# Register with CTest
include(GoogleTest)
gtest_discover_tests(allocator_test)