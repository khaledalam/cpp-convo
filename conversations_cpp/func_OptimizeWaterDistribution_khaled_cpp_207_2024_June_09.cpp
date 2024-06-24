/***


 khaled_cpp_207_2024_June_09: 16b57728-1d09-48cd-82cf-851e43874a05

func_OptimizeWaterDistribution_khaled_cpp_207_2024_June_09


*/


/*
Design a C++ function called OptimizeWaterDistribution that takes an integer num_houses, a vector of pairs of doubles const std::vector<std::pair<double, double>> representing the coordinates of the houses, and a double max_pipe_length. The function should return a vector of pairs std::vector<std::pair<int, int>> representing the optimal layout of pipes to minimize the total pipe length using Ant Colony Optimization. Please don't forget to validate the inputs.
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

struct Pipe {
    int house1;
    int house2;
    double length;

    bool operator<(const Pipe &other) const { return length < other.length; }
};

double CalculatePipeLength(const std::pair<double, double> &aaa, const std::pair<double, double> &bbb) {
    return std::sqrt(std::pow(aaa.first - bbb.first, 2) + std::pow(aaa.second - bbb.second, 2));
}

std::vector<std::pair<int, int>> OptimizeWaterDistribution(int num_houses,
                                                           const std::vector<std::pair<double, double>> &coordinates,
                                                           double max_pipe_length) {
    if (num_houses <= 0 || coordinates.size() != num_houses) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Pipe> pipes;
    for (int iii = 0; iii < num_houses; ++iii) {
        for (int jjj = iii + 1; jjj < num_houses; ++jjj) {
            double length = CalculatePipeLength(coordinates[iii], coordinates[jjj]);
            if (length <= max_pipe_length) {
                pipes.push_back({iii, jjj, length});
            }
        }
    }

    const int num_ants = 100;
    const int num_iterations = 1000;
    const double alpha = 1.0;
    const double beta = 2.0;
    const double evaporation_rate = 0.5;
    const double pheromone_initial = 1.0;

    std::vector<std::vector<double>> pheromones(num_houses, std::vector<double>(num_houses, pheromone_initial));
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<std::pair<int, int>> best_solution;
    double best_length = std::numeric_limits<double>::infinity();

    for (int iteration = 0; iteration < num_iterations; ++iteration) {
        std::vector<std::pair<int, int>> current_solution;
        double current_length = 0.0;

        for (int ant = 0; ant < num_ants; ++ant) {
            std::vector<int> visited(num_houses, 0);
            int current_house = dis(gen) * num_houses;
            visited[current_house] = 1;

            for (int step = 0; step < num_houses - 1; ++step) {
                std::vector<double> probabilities(num_houses, 0.0);
                double total_prob = 0.0;

                for (int next_house = 0; next_house < num_houses; ++next_house) {
                    if (!visited[next_house]) {
                        probabilities[next_house] =
                            std::pow(pheromones[current_house][next_house], alpha) *
                            std::pow(1.0 / CalculatePipeLength(coordinates[current_house], coordinates[next_house]),
                                     beta);
                        total_prob += probabilities[next_house];
                    }
                }

                double r = dis(gen) * total_prob;
                int selected_house = -1;
                for (int next_house = 0; next_house < num_houses; ++next_house) {
                    if (!visited[next_house]) {
                        r -= probabilities[next_house];
                        if (r <= 0.0) {
                            selected_house = next_house;
                            break;
                        }
                    }
                }

                current_solution.push_back({current_house, selected_house});
                current_length += CalculatePipeLength(coordinates[current_house], coordinates[selected_house]);
                visited[selected_house] = 1;
                current_house = selected_house;
            }

            if (current_length < best_length) {
                best_solution = current_solution;
                best_length = current_length;
            }
        }

        for (auto &row : pheromones) {
            for (auto &pheromone : row) {
                pheromone *= (1.0 - evaporation_rate);
            }
        }

        for (const auto &pipe : best_solution) {
            pheromones[pipe.first][pipe.second] += pheromone_initial / best_length;
            pheromones[pipe.second][pipe.first] += pheromone_initial / best_length;
        }
    }

    return best_solution;
}

#include <cassert>
int main() {
    // TEST
    int num_houses1 = 4;
    std::vector<std::pair<double, double>> coordinates1 = {{0.0, 0.0}, {1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
    double max_pipe_length1 = 3.0;
    std::vector<std::pair<int, int>> result1 = OptimizeWaterDistribution(num_houses1, coordinates1, max_pipe_length1);
    assert(result1.size() >= 1);
    // TEST_END

    // TEST
    try {
        OptimizeWaterDistribution(-1, coordinates1, max_pipe_length1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeWaterDistribution(num_houses1, {{0.0, 0.0}}, max_pipe_length1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
