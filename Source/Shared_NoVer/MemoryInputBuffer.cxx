#include "MemoryInputBuffer.hxx"

#include <cstddef>
#include <span>
#include <streambuf>

namespace universelan
{
    MemoryInputBuffer::MemoryInputBuffer(std::span<const std::byte> contents) noexcept
    {
        // std::streambuf's interface requires char*, even for input-only data.
        auto* begin = reinterpret_cast<char*>(
            const_cast<std::byte*>(contents.data()));

        setg(begin, begin, begin + contents.size());
    }
}