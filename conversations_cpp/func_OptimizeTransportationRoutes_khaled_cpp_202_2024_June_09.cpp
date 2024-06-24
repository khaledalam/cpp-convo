/***


 khaled_cpp_202_2024_June_09: 87e63862-977b-4f7c-a29c-d0531f931b16
 

 func_OptimizeTransportationRoutes_khaled_cpp_202_2024_June_09


*/

/*




Design a C++ function called OptimizeTransportationRoutes that takes an integer num_cities, a vector of pairs of
integers const std::vector<std::pair<int, int>> representing the distances between cities, and a double max_distance.
The function should return a vector of integers std::vector<int> representing the optimal route to minimize the total
travel distance using Simulated Annealing. Please don't forget to validate the inputs.



*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct Route {
    std::vector<int> cities;
    double distance;

    bool operator<(const Route &other) const { return distance < other.distance; }
};

double CalculateTotalDistance(const std::vector<int> &cities, const std::vector<std::pair<int, int>> &distances) {
    double total_distance = 0.0;
    for (int iii = 0; iii < cities.size() - 1; ++iii) {
        total_distance += distances[cities[iii]].second;
    }
    return total_distance;
}

std::vector<int> OptimizeTransportationRoutes(int num_cities, const std::vector<std::pair<int, int>> &distances,
                                              double max_distance) {
    if (num_cities <= 0 || distances.size() != num_cities) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<int> best_route(num_cities);
    std::iota(best_route.begin(), best_route.end(), 0);
    double best_distance = CalculateTotalDistance(best_route, distances);

    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> city_dis(0, num_cities - 1);

    double temperature = 1000.0;
    double cooling_rate = 0.99;

    while (temperature > 1.0) {
        std::vector<int> new_route = best_route;
        int city1 = city_dis(gen);
        int city2 = city_dis(gen);
        std::swap(new_route[city1], new_route[city2]);

        double new_distance = CalculateTotalDistance(new_route, distances);

        if (new_distance < best_distance || dis(gen) < std::exp((best_distance - new_distance) / temperature)) {
            best_route = new_route;
            best_distance = new_distance;
        }

        temperature *= cooling_rate;
    }

    return best_route;
}

#include <cassert>
int main() {
    // TEST
    int num_cities1 = 4;
    std::vector<std::pair<int, int>> distances1 = {{0, 1}, {1, 2}, {2, 3}, {3, 4}};
    double max_distance1 = 3.0;
    std::vector<int> result1 = OptimizeTransportationRoutes(num_cities1, distances1, max_distance1);
    assert(result1.size() == 4);
    // TEST_END

    // TEST
    try {
        OptimizeTransportationRoutes(-1, distances1, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeTransportationRoutes(num_cities1, {{0, 1}}, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
