#pragma once

#include <cstddef>
namespace allocator {
    class BumpAllocator {
    public:
        explicit BumpAllocator(std::size_t size);
        ~BumpAllocator();

        BumpAllocator(const BumpAllocator&)            = delete;
        BumpAllocator& operator=(const BumpAllocator&) = delete;
        BumpAllocator(BumpAllocator&&)                 = delete;
        BumpAllocator& operator=(BumpAllocator&&)      = delete;

        void* allocate(std::size_t size, std::size_t align = alignof(std::max_align_t));
        void  reset();
        
    private:
        std::byte* buffer_;
        std::byte* current_;
        std::size_t size_;
    };
}