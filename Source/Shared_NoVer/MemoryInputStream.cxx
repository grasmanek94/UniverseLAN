#include "MemoryInputStream.hxx"

#include <cstddef>  
#include <istream>  
#include <span>     
#include <streambuf>

namespace universelan
{
    MemoryInputStream::MemoryInputStream(
        const void* data,
        std::size_t size) noexcept
        : MemoryInputStream(
            std::span<const std::byte>{
        static_cast<const std::byte*>(data),
            size
    })
    {
    }

    MemoryInputStream::MemoryInputStream(
        std::span<const std::byte> contents) noexcept
        : buffer_(contents),
        stream_(&buffer_)
    {
    }

    [[nodiscard]]
    std::istream& MemoryInputStream::stream() noexcept
    {
        return stream_;
    }
}
