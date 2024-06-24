/***


 khaled_cpp_199_2024_June_09: c2c2b86c-7db3-4253-aeab-f3dd0179c4eb


func_MaximizeProductionOutput_khaled_cpp_199_2024_June_09


*/

/*



Design a C++ function called MaximizeProductionOutput that takes an integer num_machines, a vector of doubles const std::vector<double> representing the production rates of each machine, a vector of doubles const std::vector<double> representing the operational costs of each machine, and a double total_budget. The function should return a vector of doubles std::vector<double> representing the optimal machine operation times to maximize the total production output while staying within the total budget. Please don't forget to validate the inputs.




*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Production {
    double total_output;
    std::vector<double> operation_times;

    bool operator<(const Production &other) const { return total_output > other.total_output; }
};

double CalculateTotalOutput(const std::vector<double> &operation_times, const std::vector<double> &production_rates) {
    double total_output = 0.0;
    int num_machines = operation_times.size();
    for (int iii = 0; iii < num_machines; ++iii) {
        total_output += operation_times[iii] * production_rates[iii];
    }
    return total_output;
}

std::vector<double> MaximizeProductionOutput(int num_machines, const std::vector<double> &production_rates,
                                             const std::vector<double> &operational_costs, double total_budget) {
    if (num_machines <= 0) {
        throw std::invalid_argument("Number of machines must be positive");
    }
    if (production_rates.size() != num_machines) {
        throw std::invalid_argument("Production rates size mismatch");
    }
    if (operational_costs.size() != num_machines) {
        throw std::invalid_argument("Operational costs size mismatch");
    }

    std::vector<Production> productions;
    int num_combinations = 1 << num_machines;

    for (int mask = 0; mask < num_combinations; ++mask) {
        std::vector<double> current_operation_times(num_machines, 0.0);
        double used_budget = 0.0;

        for (int iii = 0; iii < num_machines; ++iii) {
            if (mask & (1 << iii)) {
                current_operation_times[iii] = operational_costs[iii];
                used_budget += operational_costs[iii];
            }
        }

        if (used_budget <= total_budget) {
            double total_output = CalculateTotalOutput(current_operation_times, production_rates);
            productions.push_back({total_output, current_operation_times});
        }
    }

    if (productions.empty()) {
        throw std::runtime_error("No valid production plans found within the given total budget");
    }

    return std::max_element(productions.begin(), productions.end())->operation_times;
}


#include <cassert>
int main() {
    // TEST
    int num_machines1 = 3;
    std::vector<double> production_rates1 = {1.0, 2.0, 1.5};
    std::vector<double> operational_costs1 = {10.0, 15.0, 5.0};
    double total_budget1 = 30.0;
    std::vector<double> result1 =
        MaximizeProductionOutput(num_machines1, production_rates1, operational_costs1, total_budget1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    int num_machines2 = 4;
    std::vector<double> production_rates2 = {1.2, 1.8, 1.0, 1.5};
    std::vector<double> operational_costs2 = {5.0, 10.0, 5.0, 5.0};
    double total_budget2 = 20.0;
    std::vector<double> result2 =
        MaximizeProductionOutput(num_machines2, production_rates2, operational_costs2, total_budget2);
    assert(result2.size() == 4);
    // TEST_END

    // TEST
    int num_machines3 = 2;
    std::vector<double> production_rates3 = {1.0, 1.5};
    std::vector<double> operational_costs3 = {5.0, 10.0};
    double total_budget3 = 15.0;
    std::vector<double> result3 =
        MaximizeProductionOutput(num_machines3, production_rates3, operational_costs3, total_budget3);
    assert(result3.size() == 2);
    // TEST_END

    // TEST
    int num_machines4 = 5;
    std::vector<double> production_rates4 = {1.0, 1.2, 1.4, 1.6, 1.8};
    std::vector<double> operational_costs4 = {10.0, 10.0, 10.0, 10.0, 10.0};
    double total_budget4 = 40.0;
    std::vector<double> result4 =
        MaximizeProductionOutput(num_machines4, production_rates4, operational_costs4, total_budget4);
    assert(result4.size() == 5);
    // TEST_END

    // TEST
    int num_machines5 = 3;
    std::vector<double> production_rates5 = {1.5, 1.0, 1.8};
    std::vector<double> operational_costs5 = {5.0, 10.0, 5.0};
    double total_budget5 = 20.0;
    std::vector<double> result5 =
        MaximizeProductionOutput(num_machines5, production_rates5, operational_costs5, total_budget5);
    assert(result5.size() == 3);
    // TEST_END

    // TEST
    try {
        MaximizeProductionOutput(-1, production_rates1, operational_costs1, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeProductionOutput(num_machines1, {1.0, 2.0}, operational_costs1, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeProductionOutput(num_machines1, production_rates1, {10.0, 15.0}, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
