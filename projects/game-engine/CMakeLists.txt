add_executable(game-engine
    src/main.cpp
)

target_include_directories(game-engine
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (BUILD_TESTING)
    add_subdirectory(tests) 
endif()