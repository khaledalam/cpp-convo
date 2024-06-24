/***


 khaled_cpp_208_2024_June_09: 5513c04e-09ae-45c9-8135-0b26d60b87e9

 func_OptimizeDeliveryRoutes_khaled_cpp_208_2024_June_09


*/

/*

Design a C++ function called OptimizeDeliveryRoutes that takes an integer num_locations, a vector of pairs of doubles const std::vector<std::pair<double, double>> representing the coordinates of each location, and a double max_route_distance. The function should return a vector of integers std::vector<int> representing the optimal sequence of locations to minimize the total travel distance using Simulated Annealing. Please don't forget to validate the inputs.


*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

double CalculateTravelDistance(const std::vector<int> &route,
                               const std::vector<std::pair<double, double>> &coordinates) {
    double total_distance = 0.0;
    for (int i = 0; i < route.size() - 1; ++i) {
        double dx = coordinates[route[i + 1]].first - coordinates[route[i]].first;
        double dy = coordinates[route[i + 1]].second - coordinates[route[i]].second;
        total_distance += std::sqrt(dx * dx + dy * dy);
    }
    return total_distance;
}

std::vector<int> OptimizeDeliveryRoutes(int num_locations, const std::vector<std::pair<double, double>> &coordinates,
                                        double max_route_distance) {
    if (num_locations <= 0 || coordinates.size() != num_locations) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<int> route(num_locations);
    std::iota(route.begin(), route.end(), 0);
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::shuffle(route.begin(), route.end(), gen);

    double temperature = 10000.0;
    const double cooling_rate = 0.995;
    std::uniform_real_distribution<> dis(0.0, 1.0);

    while (temperature > 1.0) {
        std::vector<int> new_route = route;
        std::swap(new_route[dis(gen) * num_locations], new_route[dis(gen) * num_locations]);

        double current_distance = CalculateTravelDistance(route, coordinates);
        double new_distance = CalculateTravelDistance(new_route, coordinates);

        if (new_distance < current_distance || std::exp((current_distance - new_distance) / temperature) > dis(gen)) {
            route = new_route;
        }

        temperature *= cooling_rate;
    }

    return route;
}

#include <cassert>
int main() {
    // TEST
    int num_locations1 = 4;
    std::vector<std::pair<double, double>> coordinates1 = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
    double max_route_distance1 = 10.0;
    std::vector<int> result1 = OptimizeDeliveryRoutes(num_locations1, coordinates1, max_route_distance1);
    assert(result1.size() == 4);
    // TEST_END

    // TEST
    try {
        OptimizeDeliveryRoutes(-1, coordinates1, max_route_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeDeliveryRoutes(num_locations1, {{0.0, 0.0}}, max_route_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
