#pragma once

#include <GalaxyIDSerialization.hxx>

#include <cereal/archives/binary.hpp>

#include <sstream>

namespace universelan::test {

template <typename T>
T serialize_round_trip(const T& source)
{
    std::stringstream stream;
    {
        cereal::BinaryOutputArchive archive(stream);
        archive(source);
    }

    T destination;
    cereal::BinaryInputArchive archive(stream);
    archive(destination);
    return destination;
}

} // namespace universelan::test
