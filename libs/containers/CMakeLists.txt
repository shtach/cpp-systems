add_library(containers INTERFACE)

target_include_directories(containers
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
              $<INSTALL_INTERFACE:include>
)

target_link_libraries(containers
    INTERFACE common
)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
