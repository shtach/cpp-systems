add_executable(netstack
    src/main.cpp
)

target_include_directories(netstack
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()