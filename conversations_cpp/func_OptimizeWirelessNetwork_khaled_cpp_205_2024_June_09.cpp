/***


 khaled_cpp_205_2024_June_09: dc7d3b21-16f9-4877-a547-d5863528d324

 func_OptimizeWirelessNetwork_khaled_cpp_205_2024_June_09
 



*/


/*
Design a C++ function called OptimizeWirelessNetwork that takes an integer num_nodes, a vector of pairs of doubles const std::vector<std::pair<double, double>> representing the coordinates of the nodes, a vector of doubles const std::vector<double> representing the transmission power of each node, and a double max_distance. The function should return a vector of pairs std::vector<std::pair<int, int>> representing the optimal connections between nodes to maximize the network coverage using Simulated Annealing. Please don't forget to validate the inputs.
*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct Connection {
    int node1;
    int node2;
    double distance;

    bool operator<(const Connection &other) const { return distance < other.distance; }
};

double CalculateDistance(const std::pair<double, double> &a, const std::pair<double, double> &b) {
    return std::sqrt(std::pow(a.first - b.first, 2) + std::pow(a.second - b.second, 2));
}

std::vector<std::pair<int, int>> OptimizeWirelessNetwork(int num_nodes, const std::vector<std::pair<double, double>> &coordinates,
                                                         const std::vector<double> &transmission_power, double max_distance) {
    if (num_nodes <= 0 || coordinates.size() != num_nodes || transmission_power.size() != num_nodes) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Connection> connections;
    for (int iii = 0; iii < num_nodes; ++iii) {
        for (int jjj = iii + 1; jjj < num_nodes; ++jjj) {
            double distance = CalculateDistance(coordinates[iii], coordinates[jjj]);
            if (distance <= transmission_power[iii] && distance <= transmission_power[jjj]) {
                connections.push_back({iii, jjj, distance});
            }
        }
    }

    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<std::pair<int, int>> best_connections;
    double best_coverage = 0.0;

    double temperature = 1000.0;
    double cooling_rate = 0.99;

    while (temperature > 1.0) {
        std::vector<std::pair<int, int>> new_connections;
        double new_coverage = 0.0;

        for (const auto &connection : connections) {
            if (dis(gen) < 0.5) {
                new_connections.push_back({connection.node1, connection.node2});
                new_coverage += connection.distance;
            }
        }

        if (new_coverage > best_coverage || dis(gen) < std::exp((new_coverage - best_coverage) / temperature)) {
            best_connections = new_connections;
            best_coverage = new_coverage;
        }

        temperature *= cooling_rate;
    }

    return best_connections;
}

#include <cassert>
int main() {
    // TEST
    int num_nodes1 = 4;
    std::vector<std::pair<double, double>> coordinates1 = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
    std::vector<double> transmission_power1 = {1.5, 1.5, 1.5, 1.5};
    double max_distance1 = 2.0;
    std::vector<std::pair<int, int>> result1 = OptimizeWirelessNetwork(num_nodes1, coordinates1, transmission_power1, max_distance1);
    assert(result1.size() >= 1);
    // TEST_END

    // TEST
    try {
        OptimizeWirelessNetwork(-1, coordinates1, transmission_power1, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeWirelessNetwork(num_nodes1, {{0.0, 0.0}}, transmission_power1, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeWirelessNetwork(num_nodes1, coordinates1, {1.0}, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
