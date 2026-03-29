# libs/common/tests/CMakeLists.txt

add_executable(console_logger_test
    console_logger_test.cpp
)

target_link_libraries(console_logger_test
    PRIVATE
        common                 # links the library
        GTest::gtest_main      # links gtest
)

# Register with CTest
include(GoogleTest)
gtest_discover_tests(console_logger_test)