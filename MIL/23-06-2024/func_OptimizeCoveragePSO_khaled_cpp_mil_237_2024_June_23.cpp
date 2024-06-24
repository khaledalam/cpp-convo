/***


 khaled_cpp_mil_237_2024_June_23: 04d14875-9f90-4258-b6e8-0478da36d7d7

 func_OptimizeCoveragePSO_khaled_cpp_mil_237_2024_June_23






*/

/*

Design a C++ function called OptimizeCoveragePSO that takes an integer num_elements, an integer num_sets, a 2D vector of
integers const std::vector<std::vector<int>> representing the elements covered by each set, and an integer budget
representing the maximum number of sets that can be selected. The function should return a vector of integers
std::vector<int> representing the optimal set selection to maximize the number of covered elements using Particle Swarm
Optimization.


*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

struct Particle {
    std::vector<int> position;
    std::vector<int> best_position;
    int best_value;
};

int CalculateCoveredElements(const std::vector<int> &solution, const std::vector<std::vector<int>> &sets) {
    std::vector<int> covered_elements(sets[0].size(), 0);
    for (int i = 0; i < solution.size(); ++i) {
        if (solution[i] == 1) {
            for (int j = 0; j < sets[i].size(); ++j) {
                covered_elements[j] = std::max(covered_elements[j], sets[i][j]);
            }
        }
    }
    return std::accumulate(covered_elements.begin(), covered_elements.end(), 0);
}

std::vector<int> OptimizeCoveragePSO(int num_elements, int num_sets, const std::vector<std::vector<int>> &sets,
                                     int budget) {
    if (num_elements <= 0 || num_sets <= 0 || sets.size() != num_sets || sets[0].size() != num_elements) {
        throw std::invalid_argument("Invalid input values");
    }

    const int swarm_size = 50;
    const int iterations = 1000;
    const double inertia_weight = 0.729;
    const double cognitive_parameter = 1.49445;
    const double social_parameter = 1.49445;

    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<Particle> swarm(swarm_size);
    for (int i = 0; i < swarm_size; ++i) {
        swarm[i].position = std::vector<int>(num_sets, 0);
        for (int j = 0; j < budget; ++j) {
            swarm[i].position[std::uniform_int_distribution<>(0, num_sets - 1)(gen)] = 1;
        }
        swarm[i].best_position = swarm[i].position;
        swarm[i].best_value = CalculateCoveredElements(swarm[i].position, sets);
    }

    std::vector<int> global_best_position = swarm[0].best_position;
    int global_best_value = swarm[0].best_value;

    for (const Particle &particle : swarm) {
        if (particle.best_value > global_best_value) {
            global_best_value = particle.best_value;
            global_best_position = particle.best_position;
        }
    }

    for (int iteration = 0; iteration < iterations; ++iteration) {
        for (Particle &particle : swarm) {
            for (int j = 0; j < num_sets; ++j) {
                if (dis(gen) < inertia_weight) {
                    particle.position[j] = particle.best_position[j];
                }

                if (dis(gen) < cognitive_parameter) {
                    particle.position[j] = particle.best_position[j];
                }

                if (dis(gen) < social_parameter) {
                    particle.position[j] = global_best_position[j];
                }
            }

            int covered_elements = CalculateCoveredElements(particle.position, sets);
            if (covered_elements > particle.best_value) {
                particle.best_value = covered_elements;
                particle.best_position = particle.position;
            }

            if (covered_elements > global_best_value) {
                global_best_value = covered_elements;
                global_best_position = particle.position;
            }
        }
    }

    return global_best_position;
}

#include <cassert>
int main() {
    // TEST
    int num_elements1 = 5;
    int num_sets1 = 3;
    std::vector<std::vector<int>> sets1 = {{1, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 0, 1}};
    int budget1 = 2;

    std::vector<int> result1 = OptimizeCoveragePSO(num_elements1, num_sets1, sets1, budget1);
    assert(std::count(result1.begin(), result1.end(), 1) <= budget1);
    // TEST_END

    // TEST
    try {
        OptimizeCoveragePSO(-1, 3, sets1, 2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeCoveragePSO(5, -1, {{1, 0, 1, 0, 0}, {0, 1, 0, 1, 0}, {0, 0, 0, 0, 1}}, 2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
