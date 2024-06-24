/***


 khaled_cpp_200_2024_June_09: 773f524c-f0b0-4716-aea3-a94b60a79ebe

 func_OptimizePowerDistribution_khaled_cpp_200_2024_June_09


*/

/*



Design me a C++ function called OptimizePowerDistribution that takes an integer num_stations, a vector of doubles const std::vector<double> representing the power outputs of each station, a vector of doubles const std::vector<double> representing the operational costs of each station, and a double total_budget. The function should return a vector of doubles std::vector<double> representing the optimal power distribution to maximize the total power output while staying within the total budget. Please don't forget to validate the inputs.



*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Distribution {
    double total_output;
    std::vector<double> distribution;

    bool operator<(const Distribution &other) const { return total_output > other.total_output; }
};

double CalculateTotalOutput(const std::vector<double> &distribution, const std::vector<double> &power_outputs) {
    double total_output = 0.0;
    int num_stations = distribution.size();
    for (int i = 0; i < num_stations; ++i) {
        total_output += distribution[i] * power_outputs[i];
    }
    return total_output;
}

std::vector<double> OptimizePowerDistribution(int num_stations, const std::vector<double> &power_outputs,
                                              const std::vector<double> &operational_costs, double total_budget) {
    if (num_stations <= 0) {
        throw std::invalid_argument("Number of stations must be positive");
    }
    if (power_outputs.size() != num_stations) {
        throw std::invalid_argument("Power outputs size mismatch");
    }
    if (operational_costs.size() != num_stations) {
        throw std::invalid_argument("Operational costs size mismatch");
    }

    std::vector<Distribution> distributions;
    int num_combinations = 1 << num_stations;

    for (int mask = 0; mask < num_combinations; ++mask) {
        std::vector<double> current_distribution(num_stations, 0.0);
        double used_budget = 0.0;

        for (int i = 0; i < num_stations; ++i) {
            if (mask & (1 << i)) {
                current_distribution[i] = operational_costs[i];
                used_budget += operational_costs[i];
            }
        }

        if (used_budget <= total_budget) {
            double total_output = CalculateTotalOutput(current_distribution, power_outputs);
            distributions.push_back({total_output, current_distribution});
        }
    }

    if (distributions.empty()) {
        throw std::runtime_error("No valid distributions found within the given total budget");
    }

    return std::max_element(distributions.begin(), distributions.end())->distribution;
}

int main() {
    // TEST
    int num_stations1 = 3;
    std::vector<double> power_outputs1 = {1.0, 2.0, 1.5};
    std::vector<double> operational_costs1 = {10.0, 15.0, 5.0};
    double total_budget1 = 30.0;
    std::vector<double> result1 =
        OptimizePowerDistribution(num_stations1, power_outputs1, operational_costs1, total_budget1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    int num_stations2 = 4;
    std::vector<double> power_outputs2 = {1.2, 1.8, 1.0, 1.5};
    std::vector<double> operational_costs2 = {5.0, 10.0, 5.0, 5.0};
    double total_budget2 = 20.0;
    std::vector<double> result2 =
        OptimizePowerDistribution(num_stations2, power_outputs2, operational_costs2, total_budget2);
    assert(result2.size() == 4);
    // TEST_END

    // TEST
    int num_stations3 = 2;
    std::vector<double> power_outputs3 = {1.0, 1.5};
    std::vector<double> operational_costs3 = {5.0, 10.0};
    double total_budget3 = 15.0;
    std::vector<double> result3 =
        OptimizePowerDistribution(num_stations3, power_outputs3, operational_costs3, total_budget3);
    assert(result3.size() == 2);
    // TEST_END

    // TEST
    int num_stations4 = 5;
    std::vector<double> power_outputs4 = {1.0, 1.2, 1.4, 1.6, 1.8};
    std::vector<double> operational_costs4 = {10.0, 10.0, 10.0, 10.0, 10.0};
    double total_budget4 = 40.0;
    std::vector<double> result4 =
        OptimizePowerDistribution(num_stations4, power_outputs4, operational_costs4, total_budget4);
    assert(result4.size() == 5);
    // TEST_END

    // TEST
    int num_stations5 = 3;
    std::vector<double> power_outputs5 = {1.5, 1.0, 1.8};
    std::vector<double> operational_costs5 = {5.0, 10.0, 5.0};
    double total_budget5 = 20.0;
    std::vector<double> result5 =
        OptimizePowerDistribution(num_stations5, power_outputs5, operational_costs5, total_budget5);
    assert(result5.size() == 3);
    // TEST_END

    // TEST
    try {
        OptimizePowerDistribution(-1, power_outputs1, operational_costs1, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizePowerDistribution(num_stations1, {1.0, 2.0}, operational_costs1, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizePowerDistribution(num_stations1, power_outputs1, {10.0, 15.0}, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
