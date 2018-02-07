#include "buffer.h"

volt::memory::Buffer::Buffer(size_t capacity)
    : data_(new uint8_t[capacity])
    , capacity_(capacity)
    , size_(capacity)
{
}

volt::memory::View volt::memory::Buffer::view() const
{
    return View{ data_.get(), size_ };
}

uint8_t* volt::memory::Buffer::data() noexcept
{
    return data_.get();
}

const uint8_t* volt::memory::Buffer::data() const noexcept
{
    return data_.get();
}

void volt::memory::Buffer::resize(size_t newSize) noexcept
{
    assert(newSize <= capacity_);
    size_ = newSize;
}

size_t volt::memory::Buffer::size() const noexcept
{
    return size_;
}

size_t volt::memory::Buffer::capacity() const noexcept
{
    return capacity_;
}
