#pragma once

#include <cstddef>  
#include <istream>  
#include <span>     

#include "MemoryInputBuffer.hxx"

namespace universelan
{
    class MemoryInputStream final
    {
    public:
        MemoryInputStream(
            const void* data,
            std::size_t size) noexcept;

        explicit MemoryInputStream(
            std::span<const std::byte> contents) noexcept;

        [[nodiscard]]
        std::istream& stream() noexcept;

    private:
        MemoryInputBuffer buffer_;
        std::istream stream_;
    };
}