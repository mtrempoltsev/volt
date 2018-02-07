#pragma once

#include "view.h"

namespace volt
{
    namespace memory
    {
        class Buffer final
        {
        public:
            explicit Buffer(size_t capacity);
            ~Buffer() = default;

            Buffer(const Buffer&) = delete;
            Buffer& operator=(Buffer&) = delete;

            Buffer(Buffer&&) = default;
            Buffer& operator=(Buffer&&) = default;

            View view() const;

            uint8_t* data() noexcept;
            const uint8_t* data() const noexcept;

            void resize(size_t newSize) noexcept;
            size_t size() const noexcept;

            size_t capacity() const noexcept;

        private:
            std::unique_ptr<uint8_t[]> data_;
            size_t capacity_;
            size_t size_;
        };
    }
}
