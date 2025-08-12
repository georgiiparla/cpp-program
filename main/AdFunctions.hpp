#pragma once

#include "AdTypes.hpp"

namespace Ad
{
    namespace Utils
    {
        float kph_to_mps(const float kph);
    }

    namespace Data
    {
        VehicleType init_ego_vehicle();
        NeighborVehiclesType init_vehicles();
    }

    namespace Visualize
    {
        void print_vehicle(const VehicleType &vehicle);
        void print_neighbor_vehicles(const NeighborVehiclesType &vehicles);
        void print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles);
    }
}
