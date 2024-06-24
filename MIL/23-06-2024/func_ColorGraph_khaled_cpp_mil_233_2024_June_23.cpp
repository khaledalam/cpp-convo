/***


 khaled_cpp_mil_233_2024_June_23: 22d76db6-36a2-4f2a-98f7-361cea4a03a7

 func_ColorGraph_khaled_cpp_mil_233_2024_June_23


*/

/*

Design a C++ function called ColorGraph that takes an integer num_vertices, a 2D vector of integers const
std::vector<std::vector<int>> representing the adjacency matrix of the graph, and an integer num_colors. The function
should return a vector of integers std::vector<int> representing the color of each vertex such that no two adjacent
vertices have the same color using Ant Colony Optimization.

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

struct Ant {
    std::vector<int> solution;
    double fitness;
};

double CalculateFitness(const std::vector<int> &solution, const std::vector<std::vector<int>> &adj_matrix,
                        int num_colors) {
    double fitness = 0.0;
    for (size_t i = 0; i < solution.size(); ++i) {
        for (size_t j = 0; j < adj_matrix[i].size(); ++j) {
            if (adj_matrix[i][j] == 1 && solution[i] == solution[j]) {
                fitness += 1.0;
            }
        }
    }
    return 1.0 / (1.0 + fitness);
}

std::vector<int> ColorGraph(int num_vertices, const std::vector<std::vector<int>> &adj_matrix, int num_colors) {
    if (num_vertices <= 0 || adj_matrix.size() != num_vertices || num_colors <= 0) {
        throw std::invalid_argument("Invalid input values");
    }

    const int num_ants = 100;
    const int iterations = 1000;
    const double alpha = 1.0;
    const double beta = 2.0;
    const double evaporation_rate = 0.5;
    const double initial_pheromone = 1.0;

    std::vector<std::vector<double>> pheromone(num_vertices, std::vector<double>(num_colors, initial_pheromone));
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> color_dis(0, num_colors - 1);

    std::vector<int> best_solution(num_vertices);
    double best_fitness = 0.0;

    for (int iteration = 0; iteration < iterations; ++iteration) {
        std::vector<Ant> ants(num_ants);
        for (Ant &ant : ants) {
            ant.solution = std::vector<int>(num_vertices);
            for (int i = 0; i < num_vertices; ++i) {
                std::vector<double> probabilities(num_colors);
                double sum_probabilities = 0.0;
                for (int color = 0; color < num_colors; ++color) {
                    probabilities[color] = std::pow(pheromone[i][color], alpha) * std::pow(1.0 / (1.0 + color), beta);
                    sum_probabilities += probabilities[color];
                }
                double random_value = dis(gen) * sum_probabilities;
                double cumulative_probability = 0.0;
                for (int color = 0; color < num_colors; ++color) {
                    cumulative_probability += probabilities[color];
                    if (cumulative_probability >= random_value) {
                        ant.solution[i] = color;
                        break;
                    }
                }
            }
            ant.fitness = CalculateFitness(ant.solution, adj_matrix, num_colors);
            if (ant.fitness > best_fitness) {
                best_fitness = ant.fitness;
                best_solution = ant.solution;
            }
        }

        for (int i = 0; i < num_vertices; ++i) {
            for (int color = 0; color < num_colors; ++color) {
                pheromone[i][color] *= (1.0 - evaporation_rate);
            }
        }

        for (const Ant &ant : ants) {
            for (int i = 0; i < num_vertices; ++i) {
                pheromone[i][ant.solution[i]] += ant.fitness;
            }
        }
    }

    return best_solution;
}

#include <cassert>
int main() {
    int num_vertices1 = 5;
    std::vector<std::vector<int>> adj_matrix1 = {
        {0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}};
    int num_colors1 = 3;
    std::vector<int> result1 = ColorGraph(num_vertices1, adj_matrix1, num_colors1);
    for (size_t i = 0; i < result1.size(); ++i) {
        for (size_t j = 0; j < adj_matrix1[i].size(); ++j) {
            if (adj_matrix1[i][j] == 1) {
                assert(result1[i] != result1[j]);
            }
        }
    }

    try {
        std::vector<std::vector<int>> adj_matrix2 = {
            {0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}, {1, 0, 1, 0, 1}, {0, 1, 0, 1, 0}};
        int num_colors2 = 3;
        ColorGraph(-1, adj_matrix2, num_colors2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }

    try {
        int num_vertices3 = 5;
        int num_colors3 = 3;
        ColorGraph(num_vertices3, {{0}}, num_colors3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
}
