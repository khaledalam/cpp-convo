/***


 khaled_cpp_mil_221_2024_June_16: d29b226e-8a10-4337-8085-5c52a672d288
 
 func_ImproveJobAssignment_khaled_cpp_mil_221_2024_June_16
 


*/

/*




Design a C++ function called ImproveJobAssignment that takes an integer num_workers, a vector of doubles const
std::vector<double> representing the cost of each job for each worker, a vector of doubles const std::vector<double>
representing the benefits of assigning each job to each worker, a 2D vector of doubles const
std::vector<std::vector<double>> representing the synergy benefits between job-worker pairs, and a double max_cost. The
function should return a vector of doubles std::vector<double> representing the optimal job assignment to maximize the
total benefit while staying within the max cost.




*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Assignment {
    double total_benefit;
    std::vector<double> assignment;

    bool operator<(const Assignment &other) const { return total_benefit > other.total_benefit; }
};

double CalculateTotalBenefit(const std::vector<double> &assignment, const std::vector<double> &benefits,
                             const std::vector<std::vector<double>> &synergy_benefits) {
    double total_benefit = 0.0;
    int num_workers = assignment.size();
    for (int iii = 0; iii < num_workers; ++iii) {
        total_benefit += assignment[iii] * benefits[iii];
        for (int jjj = 0; jjj < num_workers; ++jjj) {
            total_benefit += assignment[iii] * assignment[jjj] * synergy_benefits[iii][jjj];
        }
    }
    return total_benefit;
}

std::vector<double> OptimizeJobAssignment(int num_workers, const std::vector<double> &costs,
                                          const std::vector<double> &benefits,
                                          const std::vector<std::vector<double>> &synergy_benefits, double max_cost) {
    if (num_workers <= 0) {
        throw std::invalid_argument("Number of workers must be positive");
    }
    if (costs.size() != num_workers) {
        throw std::invalid_argument("Costs size mismatch");
    }
    if (benefits.size() != num_workers) {
        throw std::invalid_argument("Benefits size mismatch");
    }
    if (synergy_benefits.size() != num_workers || synergy_benefits[0].size() != num_workers) {
        throw std::invalid_argument("Synergy benefits matrix size mismatch");
    }

    std::vector<Assignment> assignments;
    int num_combinations = 1 << num_workers;

    for (int mask = 0; mask < num_combinations; ++mask) {
        std::vector<double> current_assignment(num_workers, 0.0);
        double used_cost = 0.0;

        for (int iii = 0; iii < num_workers; ++iii) {
            if (mask & (1 << iii)) {
                current_assignment[iii] = costs[iii];
                used_cost += costs[iii];
            }
        }

        if (used_cost <= max_cost) {
            double total_benefit = CalculateTotalBenefit(current_assignment, benefits, synergy_benefits);
            assignments.push_back({total_benefit, current_assignment});
        }
    }

    if (assignments.empty()) {
        throw std::runtime_error("No valid assignments found within the given max cost");
    }

    return std::max_element(assignments.begin(), assignments.end())->assignment;
}


#include <cassert>
int main() {
    // TEST
    int num_workers1 = 3;
    std::vector<double> costs1 = {1.0, 2.0, 1.5};
    std::vector<double> benefits1 = {10.0, 15.0, 5.0};
    std::vector<std::vector<double>> synergy_benefits1 = {{0.5, 0.2, 0.3}, {0.2, 0.5, 0.4}, {0.3, 0.4, 0.5}};
    double max_cost1 = 4.0;
    std::vector<double> result1 = OptimizeJobAssignment(num_workers1, costs1, benefits1, synergy_benefits1, max_cost1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    int num_workers2 = 4;
    std::vector<double> costs2 = {1.2, 1.8, 1.0, 1.5};
    std::vector<double> benefits2 = {5.0, 10.0, 5.0, 5.0};
    std::vector<std::vector<double>> synergy_benefits2 = {
        {0.3, 0.4, 0.2, 0.5}, {0.4, 0.3, 0.5, 0.2}, {0.2, 0.5, 0.3, 0.4}, {0.5, 0.2, 0.4, 0.3}};
    double max_cost2 = 5.0;
    std::vector<double> result2 = OptimizeJobAssignment(num_workers2, costs2, benefits2, synergy_benefits2, max_cost2);
    assert(result2.size() == 4);
    // TEST_END

    // TEST
    int num_workers3 = 2;
    std::vector<double> costs3 = {1.0, 1.5};
    std::vector<double> benefits3 = {5.0, 10.0};
    std::vector<std::vector<double>> synergy_benefits3 = {{0.4, 0.2}, {0.2, 0.4}};
    double max_cost3 = 2.5;
    std::vector<double> result3 = OptimizeJobAssignment(num_workers3, costs3, benefits3, synergy_benefits3, max_cost3);
    assert(result3.size() == 2);
    // TEST_END

    // TEST
    int num_workers4 = 5;
    std::vector<double> costs4 = {1.0, 1.2, 1.4, 1.6, 1.8};
    std::vector<double> benefits4 = {10.0, 10.0, 10.0, 10.0, 10.0};
    std::vector<std::vector<double>> synergy_benefits4 = {{0.3, 0.4, 0.5, 0.6, 0.7},
                                                          {0.4, 0.3, 0.6, 0.5, 0.8},
                                                          {0.5, 0.6, 0.3, 0.4, 0.9},
                                                          {0.6, 0.5, 0.4, 0.3, 1.0},
                                                          {0.7, 0.8, 0.9, 1.0, 0.3}};
    double max_cost4 = 6.0;
    std::vector<double> result4 = OptimizeJobAssignment(num_workers4, costs4, benefits4, synergy_benefits4, max_cost4);
    assert(result4.size() == 5);
    // TEST_END

    // TEST
    int num_workers5 = 3;
    std::vector<double> costs5 = {1.5, 1.0, 1.8};
    std::vector<double> benefits5 = {5.0, 10.0, 5.0};
    std::vector<std::vector<double>> synergy_benefits5 = {{0.4, 0.3, 0.5}, {0.3, 0.4, 0.2}, {0.5, 0.2, 0.4}};
    double max_cost5 = 4.0;
    std::vector<double> result5 = OptimizeJobAssignment(num_workers5, costs5, benefits5, synergy_benefits5, max_cost5);
    assert(result5.size() == 3);
    // TEST_END

    // TEST
    try {
        OptimizeJobAssignment(-1, costs1, benefits1, synergy_benefits1, max_cost1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeJobAssignment(num_workers1, {1.0, 2.0}, benefits1, synergy_benefits1, max_cost1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeJobAssignment(num_workers1, costs1, {10.0, 15.0}, synergy_benefits1, max_cost1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeJobAssignment(num_workers1, costs1, benefits1, {{0.5, 0.2}, {0.2, 0.5}}, max_cost1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
