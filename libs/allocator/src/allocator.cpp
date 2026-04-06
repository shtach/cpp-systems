#include "allocator/allocator.h"

#include <cstddef>
#include <cstdint>

allocator::BumpAllocator::BumpAllocator(std::size_t size) 
    : buffer_  { new std::byte[size] }
    , current_ { buffer_ } // init order has matter
    , size_    { size }
{}

allocator::BumpAllocator::~BumpAllocator() {
    delete [] buffer_;
}

void allocator::BumpAllocator::reset() {
    current_ = buffer_;
}

void* allocator::BumpAllocator::allocate(std::size_t size, std::size_t align) {
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    auto address = reinterpret_cast<std::uintptr_t>(current_);
    std::uintptr_t remainder     = address % align;
    std::uintptr_t padding       = (remainder == 0) ? 0 : (align - remainder);
    std::byte* aligned           = current_ + padding;

    std::size_t remaining = static_cast<std::size_t>((buffer_ + size_) - aligned);

    if (remaining < size)
        return nullptr;

    current_ = aligned + size;

    return aligned;
}