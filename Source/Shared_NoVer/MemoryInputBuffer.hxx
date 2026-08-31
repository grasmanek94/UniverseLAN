#pragma once

#include <cstddef>
#include <span>
#include <streambuf>

namespace universelan
{
    class MemoryInputBuffer final : public std::streambuf
    {
    public:
        explicit MemoryInputBuffer(std::span<const std::byte> contents) noexcept;
    };
}