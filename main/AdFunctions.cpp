#include <iostream>
#include <ctime>
#include <algorithm>

#include "AdFunctions.hpp"

float Ad::Utils::kph_to_mps(const float kph)
{
    return kph / 3.6F;
}

Ad::VehicleType Ad::Data::init_ego_vehicle()
{
    return VehicleType{.Id = 1, .Lane = LaneAssociationType::CENTERLANE, .Speed = 135, .RelativeDistance = 0};
}

void Ad::Visualize::print_vehicle(const VehicleType &vehicle)
{
    std::cout << "Vehicle Id: " << vehicle.Id << "\nVehicle speed: " 
        << vehicle.Speed << "\nVehicle distance: " 
        << vehicle.RelativeDistance << "\nVehicle lane: " 
        << static_cast<std::int32_t>(vehicle.Lane) << std::endl;
}

void Ad::Visualize::print_neighbor_vehicles(const NeighborVehiclesType &vehicles)
{
    auto iter_n_print = [](std::array<VehicleType, 2> l) {
        for (auto i = 0; i < l.size(); i++)
        {
            Ad::Visualize::print_vehicle(l.at(i));
        }
    };

    iter_n_print(vehicles.ll);
    std::cout << std::endl;
    iter_n_print(vehicles.cl);
    std::cout << std::endl;
    iter_n_print(vehicles.rl);
    std::cout << std::endl;
}

constexpr size_t len = 11;
constexpr auto d_a = std::array<float, len>{100, 80, 60, 40, 20, 0, -20, -40, -60, -80, -100};

Ad::NeighborVehiclesType Ad::Data::init_vehicles() {
    std::srand(std::time(nullptr));
    auto create_n_populate = [] (LaneAssociationType l_a_t, float speed) {
        static std::int32_t x = 2;
        auto v_a = std::array<VehicleType, 2>{};
        auto d1 = d_a[std::rand() % len];
        auto d2 = d_a[std::rand() % len];
        while (d1 == d2) {
            d2 = d_a[std::rand() % len];
        }
        v_a[0] = VehicleType{.Id = x, .Lane = l_a_t, .Speed = speed, .RelativeDistance = d1};
        ++x;
        v_a[1] = VehicleType{.Id = x, .Lane = l_a_t, .Speed = speed, .RelativeDistance = d2};
        ++x;
        return v_a;
    };

    NeighborVehiclesType i_nvt = NeighborVehiclesType{
        .ll = create_n_populate(LaneAssociationType::LEFTLANE, 30.0),
        .cl = create_n_populate(LaneAssociationType::CENTERLANE, 10.0),
        .rl = create_n_populate(LaneAssociationType::RIGHTLANE, 20.0)
    };
    return i_nvt;
}

void Ad::Visualize::print_scene(const VehicleType &ego_vehicle, const NeighborVehiclesType &vehicles) {
    std::array<std::array<char, 3>, len> scene_array{};

    for (auto& row : scene_array)
    {
        for (auto& ch : row)
        {
            ch = '.';
        }
    }

    auto mark_vehicle = [&](const std::array<VehicleType, 2>& lane_vehicles, size_t col) {
        for (const auto& v : lane_vehicles) {
            auto it = std::find(d_a.begin(), d_a.end(), v.RelativeDistance);
            if (it != d_a.end()) {
                size_t idx = std::distance(d_a.begin(), it);
                scene_array[idx][col] = 'X';  // Mark vehicle presence
            } else {
                std::cerr << "Warning: RelativeDistance " << v.RelativeDistance << " not found in d_a\n";
            }
        }
    };

    mark_vehicle(vehicles.ll, 0);
    mark_vehicle(vehicles.cl, 1);
    mark_vehicle(vehicles.rl, 2);

    auto ego_it = std::find(d_a.begin(), d_a.end(), ego_vehicle.RelativeDistance);
    if (ego_it != d_a.end()) {
        size_t ego_idx = std::distance(d_a.begin(), ego_it);
        scene_array[ego_idx][1] = 'E';
    }

    for (size_t i = 0; i < scene_array.size(); ++i) {
        // std::cout << "[" << d_a[i] << "] ";
        for (char ch : scene_array[i]) {
            std::cout << ch << ' ';
        }
        std::cout << '\n';
    }
}
