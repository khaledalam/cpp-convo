/***


 khaled_cpp_mil_234_2024_June_23: 26d547ac-bf01-41fc-8bfa-4acd00cec013

 func_OptimizeVehicleRoutes_khaled_cpp_mil_234_2024_June_23



*/

/*

Design a C++ function called OptimizeVehicleRoutes that takes an integer num_vehicles, an integer num_locations, a 2D
vector of doubles const std::vector<std::vector<double>> representing the distance matrix between the locations, and a
vector of doubles const std::vector<double> representing the demands at each location. The function should return a
vector of vectors of integers std::vector<std::vector<int>> representing the optimal routes for each vehicle to minimize
the total travel distance using a Genetic Algorithm.

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

struct Route {
    std::vector<int> path;
    double distance;
};

double CalculateRouteDistance(const std::vector<int> &route, const std::vector<std::vector<double>> &distance_matrix) {
    double total_distance = 0.0;
    for (size_t i = 0; i < route.size() - 1; ++i) {
        total_distance += distance_matrix[route[i]][route[i + 1]];
    }
    total_distance += distance_matrix[route.back()][route.front()];
    return total_distance;
}

std::vector<int> Crossover(const std::vector<int> &parent1, const std::vector<int> &parent2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, parent1.size() - 1);
    int start = dis(gen);
    int end = dis(gen);

    if (start > end) {
        std::swap(start, end);
    }

    std::vector<int> child(parent1.size(), -1);
    for (int i = start; i <= end; ++i) {
        child[i] = parent1[i];
    }

    size_t current_pos = (end + 1) % parent2.size();
    for (size_t i = 0; i < parent2.size(); ++i) {
        if (std::find(child.begin(), child.end(), parent2[current_pos]) == child.end()) {
            for (size_t j = 0; j < child.size(); ++j) {
                if (child[j] == -1) {
                    child[j] = parent2[current_pos];
                    break;
                }
            }
        }
        current_pos = (current_pos + 1) % parent2.size();
    }

    return child;
}

void Mutate(std::vector<int> &route, double mutation_rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    if (dis(gen) < mutation_rate) {
        std::uniform_int_distribution<> index_dis(0, route.size() - 1);
        int i = index_dis(gen);
        int j = index_dis(gen);
        std::swap(route[i], route[j]);
    }
}

std::vector<std::vector<int>> OptimizeVehicleRoutes(int num_vehicles, int num_locations,
                                                    const std::vector<std::vector<double>> &distance_matrix,
                                                    const std::vector<double> &demands, double vehicle_capacity) {
    if (num_vehicles <= 0 || num_locations <= 0 || distance_matrix.size() != num_locations ||
        demands.size() != num_locations) {
        throw std::invalid_argument("Invalid input values");
    }

    const int population_size = 100;
    const int generations = 1000;
    const double mutation_rate = 0.05;
    const double crossover_rate = 0.9;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<std::vector<int>> population(population_size, std::vector<int>(num_locations - 1));
    for (int i = 0; i < population_size; ++i) {
        std::iota(population[i].begin(), population[i].end(), 1);
        std::shuffle(population[i].begin(), population[i].end(), gen);
    }

    std::vector<int> best_route = population[0];
    double best_distance = CalculateRouteDistance(best_route, distance_matrix);

    for (int generation = 0; generation < generations; ++generation) {
        std::vector<std::vector<int>> new_population;

        for (int i = 0; i < population_size; ++i) {
            std::vector<int> parent1 = population[std::uniform_int_distribution<>(0, population_size - 1)(gen)];
            std::vector<int> parent2 = population[std::uniform_int_distribution<>(0, population_size - 1)(gen)];

            std::vector<int> child;
            if (dis(gen) < crossover_rate) {
                child = Crossover(parent1, parent2);
            } else {
                child = parent1;
            }

            Mutate(child, mutation_rate);

            new_population.push_back(child);

            double current_distance = CalculateRouteDistance(child, distance_matrix);
            if (current_distance < best_distance) {
                best_distance = current_distance;
                best_route = child;
            }
        }

        population = new_population;
    }

    std::vector<std::vector<int>> routes(num_vehicles);
    for (int i = 0; i < num_vehicles; ++i) {
        routes[i].push_back(0);
    }

    std::vector<double> vehicle_load(num_vehicles, 0.0);
    for (int loc : best_route) {
        for (int i = 0; i < num_vehicles; ++i) {
            if (vehicle_load[i] + demands[loc] <= vehicle_capacity) {
                routes[i].push_back(loc);
                vehicle_load[i] += demands[loc];
                break;
            }
        }
    }

    for (int i = 0; i < num_vehicles; ++i) {
        routes[i].push_back(0);
    }

    return routes;
}

#include <cassert>
int main() {
    int num_vehicles1 = 2;
    int num_locations1 = 5;
    std::vector<std::vector<double>> distance_matrix1 = {
        {0, 2, 9, 10, 7},
        {2, 0, 6, 4, 3},
        {9, 6, 0, 8, 5},
        {10, 4, 8, 0, 6},
        {7, 3, 5, 6, 0}
    };
    std::vector<double> demands1 = {0, 3, 4, 2, 5};
    double vehicle_capacity1 = 7.0;

    std::vector<std::vector<int>> result1 = OptimizeVehicleRoutes(num_vehicles1, num_locations1, distance_matrix1, demands1, vehicle_capacity1);
    for (const auto& route : result1) {
        double total_demand = 0.0;
        for (int loc : route) {
            total_demand += demands1[loc];
        }
        assert(total_demand <= vehicle_capacity1);
    }

    try {
        OptimizeVehicleRoutes(-1, num_locations1, distance_matrix1, demands1, vehicle_capacity1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }

    try {
        OptimizeVehicleRoutes(num_vehicles1, -1, distance_matrix1, demands1, vehicle_capacity1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
}
