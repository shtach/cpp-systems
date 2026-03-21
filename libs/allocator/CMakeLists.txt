add_library(allocator STATIC
    src/allocator.cpp
)

target_compile_features(allocator PUBLIC cxx_std_23)

target_include_directories(allocator
    PUBLIC  
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    PRIVATE 
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(allocator
    PUBLIC common
)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()


