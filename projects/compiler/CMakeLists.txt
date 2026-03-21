# projects/compiler/CMakeLists.txt

# Create the executable
add_executable(compiler
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
)

# Include directories (private, since executable internals only)
target_include_directories(compiler
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link implementation libraries privately
target_link_libraries(compiler
    PRIVATE
        allocator
        containers
)

# Enable tests if requested
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()