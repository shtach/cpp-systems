#include "allocator/allocator.h"

#include <gtest/gtest.h>
#include <cstdint>

using namespace allocator;

TEST(Allocator, NoneNullAllocation) {
    BumpAllocator alloc { 1024 };
    void* ptr = alloc.allocate(64);
    EXPECT_NE(ptr, nullptr);
}

TEST(Allocator, AligmentRespected) {
    BumpAllocator alloc { 1024 };
    void* ptr = alloc.allocate(32, 16);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    EXPECT_EQ(reinterpret_cast<std::uintptr_t>(ptr) % 16, 0);
}

TEST(Allocator, AllocationOverflow) {
    BumpAllocator alloc { 64 };
    void* ptr = alloc.allocate(65);
    EXPECT_EQ(ptr, nullptr);
}

TEST(Allocator, ResetWorks) {
    BumpAllocator alloc { 128 };
    void* ptr_1 = alloc.allocate(64);

    alloc.reset();

    void* ptr_2 = alloc.allocate(64);

    EXPECT_NE(ptr_2, nullptr);
    EXPECT_EQ(ptr_2, ptr_1);
}