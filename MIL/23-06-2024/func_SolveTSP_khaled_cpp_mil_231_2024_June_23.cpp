/***


 khaled_cpp_mil_231_2024_June_23: 5ef2f254-57c3-422c-bc90-464183896baf

 func_SolveTSP_khaled_cpp_mil_231_2024_June_23

*/

/*

Design a C++ function called SolveTSP that takes an integer num_cities and a 2D vector of doubles const
std::vector<std::vector<double>> representing the distance matrix between the cities. The function should return a
vector of integers std::vector<int> representing the optimal sequence of cities to minimize the total travel distance
using a Genetic Algorithm.


*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

double CalculateDistance(const std::vector<int> &tour, const std::vector<std::vector<double>> &distance_matrix) {
    double total_distance = 0.0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        total_distance += distance_matrix[tour[i]][tour[i + 1]];
    }
    total_distance += distance_matrix[tour.back()][tour.front()];
    return total_distance;
}

std::vector<int> Crossover(const std::vector<int> &parent1, const std::vector<int> &parent2) {
    std::random_device rdd;
    std::mt19937 gen(rdd());
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

void Mutate(std::vector<int> &tour, double mutation_rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    if (dis(gen) < mutation_rate) {
        std::uniform_int_distribution<> index_dis(0, tour.size() - 1);
        int i = index_dis(gen);
        int j = index_dis(gen);
        std::swap(tour[i], tour[j]);
    }
}

std::vector<int> SolveTSP(int num_cities, const std::vector<std::vector<double>> &distance_matrix) {
    if (num_cities <= 0 || distance_matrix.size() != num_cities) {
        throw std::invalid_argument("Invalid input values");
    }

    const int population_size = 100;
    const int generations = 1000;
    const double mutation_rate = 0.05;
    const double crossover_rate = 0.9;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<std::vector<int>> population(population_size, std::vector<int>(num_cities));
    for (int i = 0; i < population_size; ++i) {
        for (int j = 0; j < num_cities; ++j) {
            population[i][j] = j;
        }
        std::shuffle(population[i].begin(), population[i].end(), gen);
    }

    std::vector<int> best_tour = population[0];
    double best_distance = CalculateDistance(best_tour, distance_matrix);

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

            double current_distance = CalculateDistance(child, distance_matrix);
            if (current_distance < best_distance) {
                best_distance = current_distance;
                best_tour = child;
            }
        }

        population = new_population;
    }

    return best_tour;
}

#include <cassert>
int main() {
    int num_cities1 = 5;
    std::vector<std::vector<double>> distance_matrix1 = {
        {0, 10, 15, 20, 25}, {10, 0, 35, 25, 30}, {15, 35, 0, 30, 20}, {20, 25, 30, 0, 15}, {25, 30, 20, 15, 0}};

    std::vector<int> result1 = SolveTSP(num_cities1, distance_matrix1);
    double total_distance = CalculateDistance(result1, distance_matrix1);
    assert(total_distance > 0);

    try {
        std::vector<std::vector<double>> distance_matrix2 = {
        {0, 10, 15, 20, 25}, {10, 0, 35, 25, 30}, {15, 35, 0, 30, 20}, {20, 25, 30, 0, 15}, {25, 30, 20, 15, 0}};
        SolveTSP(-1, distance_matrix2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }

    try {
        int num_cities3 = 5;
        SolveTSP(num_cities3, {{0}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
}
