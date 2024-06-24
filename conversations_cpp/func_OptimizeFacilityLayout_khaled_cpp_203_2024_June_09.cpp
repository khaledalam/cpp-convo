/***


 khaled_cpp_203_2024_June_09: 58164cec-ab84-4ab9-8a2f-33a2761f227e

 func_OptimizeFacilityLayout_khaled_cpp_203_2024_June_09



*/

/*




Write me a C++ function called OptimizeFacilityLayout that takes an integer num_facilities, a vector of doubles const std::vector<double> representing the distances between facilities, a vector of doubles const std::vector<double> representing the operational costs of each facility, and a double max_distance. The function should return a vector of integers std::vector<int> representing the optimal layout of facilities to minimize the total operational cost while staying within the maximum distance using Particle Swarm Optimization. Please don't forget to validate the inputs.


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

struct Particle {
    std::vector<int> position;
    std::vector<int> velocity;
    std::vector<int> best_position;
    double best_cost;

    bool operator<(const Particle &other) const { return best_cost < other.best_cost; }
};

double CalculateTotalCost(const std::vector<int> &position, const std::vector<double> &distances,
                          const std::vector<double> &costs, double max_distance) {
    double total_cost = 0.0;
    double current_distance = 0.0;
    int num_facilities = position.size();
    for (int iii = 0; iii < num_facilities - 1; ++iii) {
        current_distance += distances[position[iii] * num_facilities + position[iii + 1]];
        if (current_distance > max_distance) {
            return std::numeric_limits<double>::infinity();
        }
        total_cost += costs[position[iii]];
    }
    total_cost += costs[position.back()];
    return total_cost;
}

std::vector<int> OptimizeFacilityLayout(int num_facilities, const std::vector<double> &distances,
                                        const std::vector<double> &costs, double max_distance) {
    if (num_facilities <= 0 || distances.size() != num_facilities * num_facilities || costs.size() != num_facilities) {
        throw std::invalid_argument("Invalid input values");
    }

    const int swarm_size = 100;
    const int num_iterations = 1000;
    const double inertia = 0.5;
    const double cognitive_component = 1.0;
    const double social_component = 1.0;

    std::vector<Particle> swarm(swarm_size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int iii = 0; iii < swarm_size; ++iii) {
        swarm[iii].position.resize(num_facilities);
        std::iota(swarm[iii].position.begin(), swarm[iii].position.end(), 0);
        std::shuffle(swarm[iii].position.begin(), swarm[iii].position.end(), gen);
        swarm[iii].velocity.resize(num_facilities);
        std::generate(swarm[iii].velocity.begin(), swarm[iii].velocity.end(),
                      [&] { return static_cast<int>(dis(gen) * num_facilities); });
        swarm[iii].best_position = swarm[iii].position;
        swarm[iii].best_cost = CalculateTotalCost(swarm[iii].position, distances, costs, max_distance);
    }

    std::vector<int> global_best_position = swarm.front().best_position;
    double global_best_cost = swarm.front().best_cost;

    for (int iteration = 0; iteration < num_iterations; ++iteration) {
        for (auto &particle : swarm) {
            double cost = CalculateTotalCost(particle.position, distances, costs, max_distance);
            if (cost < particle.best_cost) {
                particle.best_position = particle.position;
                particle.best_cost = cost;
            }
            if (cost < global_best_cost) {
                global_best_position = particle.position;
                global_best_cost = cost;
            }
        }

        for (auto &particle : swarm) {
            for (int iii = 0; iii < num_facilities; ++iii) {
                particle.velocity[iii] =
                    inertia * particle.velocity[iii] +
                    cognitive_component * dis(gen) * (particle.best_position[iii] - particle.position[iii]) +
                    social_component * dis(gen) * (global_best_position[iii] - particle.position[iii]);
                particle.position[iii] = (particle.position[iii] + particle.velocity[iii] + num_facilities) % num_facilities;
            }
        }
    }

    return global_best_position;
}

int main() {
    // TEST
    int num_facilities1 = 4;
    std::vector<double> distances1 = {0.0, 1.0, 1.5, 2.0, 1.0, 0.0, 1.0, 1.5, 1.5, 1.0, 0.0, 1.0, 2.0, 1.5, 1.0, 0.0};
    std::vector<double> costs1 = {5.0, 10.0, 15.0, 20.0};
    double max_distance1 = 3.0;
    std::vector<int> result1 = OptimizeFacilityLayout(num_facilities1, distances1, costs1, max_distance1);
    assert(result1.size() == 4);
    // TEST_END

    // TEST
    int num_facilities2 = 5;
    std::vector<double> distances2 = {0.0, 1.0, 1.5, 2.0, 2.5, 1.0, 0.0, 1.0, 1.5, 2.0, 1.5, 1.0, 0.0,
                                      1.0, 1.5, 2.0, 1.5, 1.0, 0.0, 1.0, 2.5, 2.0, 1.5, 1.0, 0.0};
    std::vector<double> costs2 = {5.0, 10.0, 15.0, 20.0, 25.0};
    double max_distance2 = 4.0;
    std::vector<int> result2 = OptimizeFacilityLayout(num_facilities2, distances2, costs2, max_distance2);
    assert(result2.size() == 5);
    // TEST_END

    // TEST
    try {
        OptimizeFacilityLayout(-1, distances1, costs1, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeFacilityLayout(num_facilities1, {0.0, 1.0, 1.5, 2.0, 1.0, 0.0, 1.0, 1.5}, costs1, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeFacilityLayout(num_facilities1, distances1, {5.0, 10.0}, max_distance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
