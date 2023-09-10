#pragma once

#include <GalaxyID.h>
#include <cstdint>

namespace galaxy {
    namespace api {
        template <class Archive>
        uint64_t save_minimal(
            Archive const&,
            galaxy::api::GalaxyID const& md)
        {
            return md.ToUint64();
        }

        template <class Archive>
        void load_minimal(Archive const&,
            galaxy::api::GalaxyID& md,
            uint64_t const& value)
        {
            md = galaxy::api::GalaxyID(value);
        }
    }
}
