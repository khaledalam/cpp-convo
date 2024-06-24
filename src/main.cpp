/***


 khaled_cpp_mil_240_2024_June_23:











*/

/*





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
    std::vector<std::vector<double>> position;
    std::vector<std::vector<double>> velocity;
    std::vector<std::vector<double>> best_position;
    double best_value;
};

double EvaluateFitness(const std::vector<std::vector<double>> &position,
                       const std::vector<std::vector<double>> &matrix) {
    double error = 0.0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            double value = 0.0;
            for (size_t k = 0; k < matrix.size(); ++k) {
                value += matrix[i][k] * position[k][j];
            }
            error += std::pow((i == j ? 1.0 : 0.0) - value, 2);
        }
    }
    return error;
}

std::vector<std::vector<double>> SolveMatrixInversionPSO(const std::vector<std::vector<double>> &matrix) {
    const int num_particles = 50;
    const int iterations = 1000;
    const double inertia_weight = 0.729;
    const double cognitive_parameter = 1.49445;
    const double social_parameter = 1.49445;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    std::uniform_real_distribution<> velocity_dis(-0.1, 0.1);

    size_t dimensions = matrix.size();
    std::vector<Particle> swarm(num_particles);
    for (int i = 0; i < num_particles; ++i) {
        swarm[i].position = std::vector<std::vector<double>>(dimensions, std::vector<double>(dimensions));
        swarm[i].velocity = std::vector<std::vector<double>>(dimensions, std::vector<double>(dimensions));
        for (size_t j = 0; j < dimensions; ++j) {
            for (size_t k = 0; k < dimensions; ++k) {
                swarm[i].position[j][k] = dis(gen);
                swarm[i].velocity[j][k] = velocity_dis(gen);
            }
        }
        swarm[i].best_position = swarm[i].position;
        swarm[i].best_value = EvaluateFitness(swarm[i].position, matrix);
    }

    std::vector<std::vector<double>> global_best_position = swarm[0].best_position;
    double global_best_value = swarm[0].best_value;

    for (const Particle &particle : swarm) {
        if (particle.best_value < global_best_value) {
            global_best_value = particle.best_value;
            global_best_position = particle.best_position;
        }
    }

    for (int iteration = 0; iteration < iterations; ++iteration) {
        for (Particle &particle : swarm) {
            for (size_t j = 0; j < dimensions; ++j) {
                for (size_t k = 0; k < dimensions; ++k) {
                    particle.velocity[j][k] = inertia_weight * particle.velocity[j][k] +
                                              cognitive_parameter * ((double)rand() / RAND_MAX) *
                                                  (particle.best_position[j][k] - particle.position[j][k]) +
                                              social_parameter * ((double)rand() / RAND_MAX) *
                                                  (global_best_position[j][k] - particle.position[j][k]);
                    particle.position[j][k] += particle.velocity[j][k];
                }
            }

            double fitness = EvaluateFitness(particle.position, matrix);
            if (fitness < particle.best_value) {
                particle.best_value = fitness;
                particle.best_position = particle.position;
            }

            if (fitness < global_best_value) {
                global_best_value = fitness;
                global_best_position = particle.position;
            }
        }
    }

    return global_best_position;
}

#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

int main() {
    // TEST
    std::vector<std::vector<double>> matrix1 = {{1, 2}, {3, 4}};

    auto result1 = SolveMatrixInversionPSO(matrix1);
    assert(result1.size() == matrix1.size());
    for (size_t i = 0; i < result1.size(); ++i) {
        for (size_t j = 0; j < result1[0].size(); ++j) {
            assert(std::abs(result1[i][j] - ((i == j) ? 1 : 0)) < 0.1);
        }
    }
    // TEST_END

    // TEST
    std::vector<std::vector<double>> matrix2 = {{2, 0, 1}, {1, 3, 2}, {3, 2, 1}};

    auto result2 = SolveMatrixInversionPSO(matrix2);
    assert(result2.size() == matrix2.size());
    for (size_t i = 0; i < result2.size(); ++i) {
        for (size_t j = 0; j < result2[0].size(); ++j) {
            assert(std::abs(result2[i][j] - ((i == j) ? 1 : 0)) < 0.1);
        }
    }
    // TEST_END

    // TEST
    try {
        SolveMatrixInversionPSO({});
        assert(false);
    } catch (...) {
        assert(true);
    }
    // TEST_END

    std::cout << "All tests passed!" << std::endl;
}
