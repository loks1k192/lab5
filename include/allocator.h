#pragma once
#include <memory_resource>
#include <vector>
#include <cstddef>
#include <stdexcept>

class Allocator : public std::pmr::memory_resource
{
private:
    void *do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void *p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const std::pmr::memory_resource &other) const noexcept override;
    char *buffer = nullptr;
    std::size_t buffer_size = 0;
    std::size_t offset = 0;

    std::vector<std::pair<void *, size_t>> blocks;

public:
    explicit Allocator(std::size_t bytes);
    ~Allocator() noexcept;
    Allocator(const Allocator &) = delete;
    Allocator &operator=(const Allocator &) = delete;
    Allocator(Allocator &&) = delete;
    Allocator &operator=(Allocator &&) = delete;
};