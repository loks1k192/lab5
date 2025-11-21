#include <stdexcept>
#include <cstddef>

#include "allocator.h"

Allocator::Allocator(std::size_t bytes) : buffer_size(bytes)
{
    if (bytes == 0)
        throw std::invalid_argument("Buffer size must be greater than zero");
    buffer = static_cast<char *>(::operator new(bytes));
    offset = 0;
}

Allocator::~Allocator() noexcept
{
    blocks.clear();
    ::operator delete(buffer);
}

void *Allocator::do_allocate(std::size_t bytes, std::size_t alignment)
{
    if (bytes == 0)
        return nullptr;

    std::size_t current = reinterpret_cast<std::size_t>(buffer + offset);
    std::size_t aligned = (current + alignment - 1) & ~(alignment - 1);
    std::size_t shift = aligned - current;

    if (offset + shift + bytes > buffer_size)
    {
        throw std::bad_alloc();
    }

    void *ptr = buffer + offset + shift;
    offset += shift + bytes;

    blocks.push_back({ptr, bytes});

    return ptr;
}

void Allocator::do_deallocate(void *p, std::size_t bytes, std::size_t alignment)
{
    if (!p)
        return;

    for (auto &b : blocks)
    {
        if (b.first == p)
        {
            b.second = 0;
            break;
        }
    }
}

bool Allocator::do_is_equal(const std::pmr::memory_resource &other) const noexcept
{
    return this == &other;
}