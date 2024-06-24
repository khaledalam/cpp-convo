/***


 khaled_cpp_mil_235_2024_June_23: b917ba0f-d7cb-4643-a773-9d83e947cb6c

 func_OptimizeProjectSchedule_khaled_cpp_mil_235_2024_June_23





*/

/*

Design a C++ function called OptimizeProjectSchedule that takes an integer num_tasks, a vector of pairs of doubles const
std::vector<std::pair<double, double>> representing the start time and end time of each task, and a double min_gap. The
function should return a vector of integers std::vector<int> representing the optimal sequence of tasks to maximize the
total number of non-overlapping tasks using Particle Swarm Optimization.

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

double CalculatePortfolioReturn(const std::vector<double> &weights, const std::vector<double> &expected_returns) {
    double total_return = 0.0;
    for (size_t i = 0; i < weights.size(); ++i) {
        total_return += weights[i] * expected_returns[i];
    }
    return total_return;
}

double CalculatePortfolioRisk(const std::vector<double> &weights,
                              const std::vector<std::vector<double>> &covariance_matrix) {
    double total_risk = 0.0;
    for (size_t i = 0; i < weights.size(); ++i) {
        for (size_t j = 0; j < weights.size(); ++j) {
            total_risk += weights[i] * weights[j] * covariance_matrix[i][j];
        }
    }
    return std::sqrt(total_risk);
}

std::vector<double> OptimizePortfolioACO(int num_assets, const std::vector<double> &expected_returns,
                                         const std::vector<std::vector<double>> &covariance_matrix,
                                         double risk_tolerance) {
    if (num_assets <= 0 || expected_returns.size() != num_assets || covariance_matrix.size() != num_assets) {
        throw std::invalid_argument("Invalid input values");
    }

    const int num_ants = 100;
    const int iterations = 1000;
    const double alpha = 1.0;
    const double beta = 2.0;
    const double evaporation_rate = 0.5;
    const double initial_pheromone = 1.0;

    std::vector<std::vector<double>> pheromone(num_assets, std::vector<double>(num_assets, initial_pheromone));
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<double> best_weights(num_assets);
    double best_fitness = -std::numeric_limits<double>::max();

    for (int iteration = 0; iteration < iterations; ++iteration) {
        for (int ant = 0; ant < num_ants; ++ant) {
            std::vector<double> weights(num_assets);
            double total_weight = 0.0;

            for (int i = 0; i < num_assets; ++i) {
                weights[i] = dis(gen);
                total_weight += weights[i];
            }

            for (int i = 0; i < num_assets; ++i) {
                weights[i] /= total_weight;
            }

            double portfolio_return = CalculatePortfolioReturn(weights, expected_returns);
            double portfolio_risk = CalculatePortfolioRisk(weights, covariance_matrix);
            double fitness = portfolio_return - risk_tolerance * portfolio_risk;

            if (fitness > best_fitness) {
                best_fitness = fitness;
                best_weights = weights;
            }

            for (size_t i = 0; i < weights.size(); ++i) {
                for (size_t j = 0; j < weights.size(); ++j) {
                    pheromone[i][j] += fitness;
                }
            }
        }

        for (size_t i = 0; i < pheromone.size(); ++i) {
            for (size_t j = 0; j < pheromone[i].size(); ++j) {
                pheromone[i][j] *= (1.0 - evaporation_rate);
            }
        }
    }

    return best_weights;
}

#include <cassert>
int main() {
    // TEST
    int num_assets1 = 4;
    std::vector<double> expected_returns1 = {0.1, 0.15, 0.2, 0.12};
    std::vector<std::vector<double>> covariance_matrix1 = {{0.005, -0.010, 0.004, -0.002},
                                                           {-0.010, 0.040, -0.002, 0.004},
                                                           {0.004, -0.002, 0.023, 0.002},
                                                           {-0.002, 0.004, 0.002, 0.018}};
    double risk_tolerance1 = 0.1;

    std::vector<double> result1 =
        OptimizePortfolioACO(num_assets1, expected_returns1, covariance_matrix1, risk_tolerance1);
    double total_weight = std::accumulate(result1.begin(), result1.end(), 0.0);
    assert(std::abs(total_weight - 1.0) < 1e-6);
    // TEST_END

    // TEST
    try {
        std::vector<double> expected_returns2 = {0.1, 0.15, 0.2, 0.12};
        std::vector<std::vector<double>> covariance_matrix2 = {{0.005, -0.010, 0.004, -0.002},
                                                               {-0.010, 0.040, -0.002, 0.004},
                                                               {0.004, -0.002, 0.023, 0.002},
                                                               {-0.002, 0.004, 0.002, 0.018}};
        double risk_tolerance2 = 0.1;
        OptimizePortfolioACO(-1, expected_returns2, covariance_matrix2, risk_tolerance2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        int num_assets3 = 4;
        std::vector<std::vector<double>> covariance_matrix3 = {{0.005, -0.010, 0.004, -0.002},
                                                               {-0.010, 0.040, -0.002, 0.004},
                                                               {0.004, -0.002, 0.023, 0.002},
                                                               {-0.002, 0.004, 0.002, 0.018}};
        double risk_tolerance3 = 0.1;
        OptimizePortfolioACO(num_assets3, {0.1}, covariance_matrix3, risk_tolerance3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
