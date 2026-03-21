cmake_minimum_required(VERSION 3.25)
project(cpp_systems VERSION 0.1.0 LANGUAGES C CXX)

# ── Standards ──────────────────────────────────────────────────────────────────
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Warnings ───────────────────────────────────────────────────────────────────
#add_compile_options(
  #  $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic;-Wconversion;-Wshadow>
   # $<$<CXX_COMPILER_ID:MSVC>:/W4>
#)

# ── Testing ───────────────────────────────────────────────────────────────────
include(CTest)
enable_testing()

# ── Google Test ───────────────────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ── Sanitizers ───────────────────────────────────────────────────────────────────
if (ENABLE_ASAN) 
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()

if (ENABLE_UBSAN)
    add_compile_options(-fsanitize=undefined)
    add_link_options(-fsanitize=undefined)
endif()

# ── clang-tidy ───────────────────────────────────────────────────────────────────
if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy REQUIRED)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
endif()

# ── Warnings ───────────────────────────────────────────────────────────────────
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion -Wshadow)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4)
endif()

# ── Subdirectories ───────────────────────────────────────────────────────────────
add_subdirectory(libs/common)
add_subdirectory(libs/allocator)
add_subdirectory(libs/containers)

add_subdirectory(projects/compiler)
add_subdirectory(projects/netstack)
add_subdirectory(projects/game-engine)

add_subdirectory(exercises)