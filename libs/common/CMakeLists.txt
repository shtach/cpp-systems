add_library(common STATIC
    src/log.cpp
)

target_compile_features(common PUBLIC cxx_std_23)

target_include_directories(common
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()