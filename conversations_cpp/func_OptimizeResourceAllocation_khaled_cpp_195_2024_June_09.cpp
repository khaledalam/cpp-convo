/***


 khaled_cpp_195_2024_June_09: d5ad993c-a0a4-4138-82ec-65ba2f64c71d

 func_OptimizeResourceAllocation_khaled_cpp_195_2024_June_09

*/

/*
Design me a C++ function called OptimizeResourceAllocation that takes an integer num_resources, a vector of doubles
const std::vector<double> representing the expected profits of each resource, a vector of doubles const
std::vector<double> representing the risks (standard deviations) of each resource, a 2D vector of doubles const
std::vector<std::vector<double>> representing the correlation matrix between the resources, and a double risk_tolerance.
The function should return a vector of doubles std::vector<double> representing the optimal weights of the resources in
the allocation to maximize the profit while minimizing the risk according to the given risk tolerance. Please don't
forget to validate the inputs.


*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Allocation {
    double profit;
    double risk;
    std::vector<double> weights;

    bool operator<(const Allocation &other) const { return profit / risk > other.profit / other.risk; }
};

double CalculateAllocationRisk(const std::vector<double> &weights, const std::vector<double> &risks,
                               const std::vector<std::vector<double>> &correlation_matrix) {
    double risk = 0.0;
    int num_resources = weights.size();
    for (int idx = 0; idx < num_resources; ++idx) {
        for (int jdx = 0; jdx < num_resources; ++jdx) {
            risk += weights[idx] * weights[jdx] * risks[idx] * risks[jdx] * correlation_matrix[idx][jdx];
        }
    }
    return std::sqrt(risk);
}

std::vector<double> OptimizeResourceAllocation(int num_resources, const std::vector<double> &profits,
                                               const std::vector<double> &risks,
                                               const std::vector<std::vector<double>> &correlation_matrix,
                                               double risk_tolerance) {
    if (num_resources <= 0 || profits.size() != num_resources || risks.size() != num_resources ||
        correlation_matrix.size() != num_resources || correlation_matrix[0].size() != num_resources) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Allocation> allocations;
    int num_combinations = 1 << num_resources;

    for (int mask = 0; mask < num_combinations; ++mask) {
        std::vector<double> weights(num_resources, 0.0);
        double total_profit = 0.0;
        double total_weight = 0.0;

        for (int idx = 0; idx < num_resources; ++idx) {
            if (mask & (1 << idx)) {
                weights[idx] = 1.0 / risks[idx];
                total_weight += weights[idx];
                total_profit += profits[idx] * weights[idx];
            }
        }

        for (int idx = 0; idx < num_resources; ++idx) {
            weights[idx] /= total_weight;
        }

        double allocation_risk = CalculateAllocationRisk(weights, risks, correlation_matrix);

        if (allocation_risk <= risk_tolerance) {
            allocations.push_back({total_profit, allocation_risk, weights});
        }
    }

    if (allocations.empty()) {
        throw std::runtime_error("No valid allocations found within the given risk tolerance");
    }

    return std::max_element(allocations.begin(), allocations.end())->weights;
}

#include <cassert>
int main() {
    // TEST
    int num_resources1 = 3;
    std::vector<double> profits1 = {0.1, 0.2, 0.15};
    std::vector<double> risks1 = {0.05, 0.1, 0.07};
    std::vector<std::vector<double>> correlation_matrix1 = {{1.0, 0.2, 0.4}, {0.2, 1.0, 0.5}, {0.4, 0.5, 1.0}};
    double risk_tolerance1 = 0.08;
    std::vector<double> result1 =
        OptimizeResourceAllocation(num_resources1, profits1, risks1, correlation_matrix1, risk_tolerance1);
    assert(result1.size() == 3);
    assert(std::abs(result1[0] + result1[1] + result1[2] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_resources2 = 4;
    std::vector<double> profits2 = {0.12, 0.18, 0.1, 0.15};
    std::vector<double> risks2 = {0.06, 0.08, 0.05, 0.07};
    std::vector<std::vector<double>> correlation_matrix2 = {
        {1.0, 0.3, 0.2, 0.4}, {0.3, 1.0, 0.4, 0.2}, {0.2, 0.4, 1.0, 0.3}, {0.4, 0.2, 0.3, 1.0}};
    double risk_tolerance2 = 0.07;
    std::vector<double> result2 =
        OptimizeResourceAllocation(num_resources2, profits2, risks2, correlation_matrix2, risk_tolerance2);
    assert(result2.size() == 4);
    assert(std::abs(result2[0] + result2[1] + result2[2] + result2[3] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_resources3 = 3;
    std::vector<double> profits3 = {0.15, 0.22, 0.18};
    std::vector<double> risks3 = {0.07, 0.09, 0.08};
    std::vector<std::vector<double>> correlation_matrix3 = {{1.0, 0.25, 0.3}, {0.25, 1.0, 0.35}, {0.3, 0.35, 1.0}};
    double risk_tolerance3 = 0.075;
    std::vector<double> result3 =
        OptimizeResourceAllocation(num_resources3, profits3, risks3, correlation_matrix3, risk_tolerance3);
    assert(result3.size() == 3);
    assert(std::abs(result3[0] + result3[1] + result3[2] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_resources4 = 5;
    std::vector<double> profits4 = {0.1, 0.12, 0.15, 0.18, 0.2};
    std::vector<double> risks4 = {0.04, 0.05, 0.06, 0.07, 0.08};
    std::vector<std::vector<double>> correlation_matrix4 = {{1.0, 0.1, 0.2, 0.3, 0.4},
                                                            {0.1, 1.0, 0.2, 0.3, 0.4},
                                                            {0.2, 0.2, 1.0, 0.3, 0.4},
                                                            {0.3, 0.3, 0.3, 1.0, 0.4},
                                                            {0.4, 0.4, 0.4, 0.4, 1.0}};
    double risk_tolerance4 = 0.065;
    std::vector<double> result4 =
        OptimizeResourceAllocation(num_resources4, profits4, risks4, correlation_matrix4, risk_tolerance4);
    assert(result4.size() == 5);
    assert(std::abs(result4[0] + result4[1] + result4[2] + result4[3] + result4[4] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    int num_resources5 = 2;
    std::vector<double> profits5 = {0.1, 0.2};
    std::vector<double> risks5 = {0.05, 0.1};
    std::vector<std::vector<double>> correlation_matrix5 = {{1.0, 0.5}, {0.5, 1.0}};
    double risk_tolerance5 = 0.075;
    std::vector<double> result5 =
        OptimizeResourceAllocation(num_resources5, profits5, risks5, correlation_matrix5, risk_tolerance5);
    assert(result5.size() == 2);
    assert(std::abs(result5[0] + result5[1] - 1.0) < 1e-9);
    // TEST_END

    // TEST
    try {
        OptimizeResourceAllocation(-1, {0.1}, {0.1}, {{1.0, 0.5}}, 0.075);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
