#pragma once

#include <cstdint>
#include <array>

namespace Ad
{
    enum class LaneAssociationType
    {
        UNKNOWNLANE,
        LEFTLANE,
        CENTERLANE,
        RIGHTLANE,
    };

    struct VehicleType
    {
        int32_t Id;
        LaneAssociationType Lane;
        float Speed;
        float RelativeDistance;
    };

    struct NeighborVehiclesType
    {
        std::array<VehicleType, 2> ll = std::array<VehicleType, 2>{};
        std::array<VehicleType, 2> cl = std::array<VehicleType, 2>{};
        std::array<VehicleType, 2> rl = std::array<VehicleType, 2>{};
    };
}
