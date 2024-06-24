/***


 khaled_cpp_196_2024_June_09: c6cedc62-bd50-4896-80ba-5f4c6d3aab56


func_OptimizeDroneDeliveryPath_khaled_cpp_196_2024_June_09

*/

/*


Create me a C++ function called OptimizeDroneDeliveryPath that takes an integer num_locations, a vector of tuples const
std::vector<std::tuple<int, int, double>> representing the paths between locations where each tuple contains two
integers (locations) and a double (distance), an integer start_location, and an integer end_location. The function
should return a double representing the shortest path distance from the start_location to the end_location using dynamic
programming. Please don't forget to validate the inputs.



*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

struct Path {
    int location;
    double distance;

    bool operator>(const Path &other) const { return distance > other.distance; }
};

double OptimizeDroneDeliveryPath(int num_locations, const std::vector<std::tuple<int, int, double>> &paths,
                                 int start_location, int end_location) {
    if (num_locations <= 0) {
        throw std::invalid_argument("num_locations should be positive");
    }

    if (paths.empty()) {
        throw std::invalid_argument("paths can't be empty");
    }

    if (start_location < 0 || start_location >= num_locations) {
        throw std::invalid_argument("start_location should be between 0 and num_locations");
    }

    if (end_location < 0 || end_location >= num_locations) {
        throw std::invalid_argument("end_location should be between 0 and num_locations");
    }

    std::vector<std::vector<Path>> graph(num_locations);
    for (const auto &path : paths) {
        int from, to;
        double distance;
        std::tie(from, to, distance) = path;
        graph[from].push_back({to, distance});
        graph[to].push_back({from, distance});
    }

    std::vector<double> min_distance(num_locations, std::numeric_limits<double>::infinity());
    min_distance[start_location] = 0;
    std::priority_queue<Path, std::vector<Path>, std::greater<Path>> pqq;
    pqq.push({start_location, 0});

    while (!pqq.empty()) {
        int current_location = pqq.top().location;
        double current_distance = pqq.top().distance;
        pqq.pop();

        if (current_distance > min_distance[current_location])
            continue;

        for (const auto &neighbor : graph[current_location]) {
            double distance = current_distance + neighbor.distance;
            if (distance < min_distance[neighbor.location]) {
                min_distance[neighbor.location] = distance;
                pqq.push({neighbor.location, distance});
            }
        }
    }

    return min_distance[end_location];
}

int main() {
    // TEST
    int num_locations1 = 5;
    std::vector<std::tuple<int, int, double>> paths1 = {
        {0, 1, 2.0}, {1, 2, 2.5}, {2, 3, 1.0}, {3, 4, 2.0}, {0, 4, 10.0}};
    int start_location1 = 0;
    int end_location1 = 4;
    double result1 = OptimizeDroneDeliveryPath(num_locations1, paths1, start_location1, end_location1);
    assert(std::abs(result1 - 7.5) < 1e-9);
    // TEST_END

    // TEST
    int num_locations2 = 6;
    std::vector<std::tuple<int, int, double>> paths2 = {{0, 1, 1.0}, {1, 2, 1.0}, {2, 3, 1.0},
                                                        {3, 4, 1.0}, {4, 5, 1.0}, {0, 5, 10.0}};
    int start_location2 = 0;
    int end_location2 = 5;
    double result2 = OptimizeDroneDeliveryPath(num_locations2, paths2, start_location2, end_location2);
    assert(std::abs(result2 - 5.0) < 1e-9);
    // TEST_END

    // TEST
    int num_locations3 = 4;
    std::vector<std::tuple<int, int, double>> paths3 = {{0, 1, 3.0}, {1, 2, 1.0}, {2, 3, 2.0}, {0, 3, 4.0}};
    int start_location3 = 0;
    int end_location3 = 3;
    double result3 = OptimizeDroneDeliveryPath(num_locations3, paths3, start_location3, end_location3);
    assert(std::abs(result3 - 4.0) < 1e-9);
    // TEST_END

    // TEST
    int num_locations4 = 5;
    std::vector<std::tuple<int, int, double>> paths4 = {{0, 1, 1.0}, {1, 2, 1.0}, {2, 3, 1.0},
                                                        {3, 4, 1.0}, {0, 2, 2.0}, {2, 4, 2.0}};
    int start_location4 = 0;
    int end_location4 = 4;
    double result4 = OptimizeDroneDeliveryPath(num_locations4, paths4, start_location4, end_location4);
    assert(std::abs(result4 - 4.0) < 1e-9);
    // TEST_END

    // TEST
    int num_locations5 = 3;
    std::vector<std::tuple<int, int, double>> paths5 = {{0, 1, 2.0}, {1, 2, 3.0}, {0, 2, 5.0}};
    int start_location5 = 0;
    int end_location5 = 2;
    double result5 = OptimizeDroneDeliveryPath(num_locations5, paths5, start_location5, end_location5);
    assert(std::abs(result5 - 5.0) < 1e-9);
    // TEST_END

    // TEST
    try {
        OptimizeDroneDeliveryPath(-1, {{0, 1, 2.0}, {1, 2, 3.0}, {0, 2, 5.0}}, 0, 2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeDroneDeliveryPath(4, {}, 0, 2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeDroneDeliveryPath(4, {{0, 1, 2.0}, {1, 2, 3.0}, {0, 2, 5.0}}, -3, 2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeDroneDeliveryPath(4, {{0, 1, 2.0}, {1, 2, 3.0}, {0, 2, 5.0}}, 3, -2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
