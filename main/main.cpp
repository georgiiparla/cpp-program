#include <cstring>
#include <iostream>
// #include <numeric>

#include "AdFunctions.hpp"
#include "AdTypes.hpp"

int main()
{
    auto ego_vehicle = Ad::Data::init_ego_vehicle();
    Ad::Visualize::print_vehicle(ego_vehicle);
    std::cout << std::endl;

    auto vehicles = Ad::Data::init_vehicles();
    Ad::Visualize::print_neighbor_vehicles(vehicles);

    std::cout << std::endl;
    Ad::Visualize::print_scene(ego_vehicle, vehicles);
    return 0;
}
