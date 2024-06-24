/***


 khaled_cpp_mil_214_2024_June_16: 157f5cbb-7271-45c0-a67a-63ecb7020c68
 
 func_MaxProductionOutput_khaled_cpp_mil_214_2024_June_16

*/


/*



Design a C++ function called MaxProductionOutput that takes an integer num_machines, a vector of doubles const std::vector<double> representing the production rates of each machine, a vector of doubles const std::vector<double> representing the operational costs of each machine, and a double total_budget. The function should return a vector of doubles std::vector<double> representing the optimal machine operation times to maximize the total production output while staying within the total budget. Please don't forget to validate the inputs.




*/

// #include <algorithm>
// #include <cassert>
#include <iostream>
// #include <stdexcept>

#include <vector>
#include <algorithm>
#include <stdexcept>

std::vector<double> MaxProductionOutput(int num_machines, const std::vector<double>& production_rates, const std::vector<double>& operational_costs, double total_budget) {
    // Validate inputs
    if (num_machines <= 0) {
        throw std::invalid_argument("Number of machines must be positive.");
    }
    if (production_rates.size() != num_machines || operational_costs.size() != num_machines) {
        throw std::invalid_argument("Size of production rates and operational costs vectors must equal the number of machines.");
    }
    for (int i = 0; i < num_machines; ++i) {
        if (production_rates[i] <= 0 || operational_costs[i] <= 0) {
            throw std::invalid_argument("Production rates and operational costs must be positive.");
        }
    }
    if (total_budget <= 0) {
        throw std::invalid_argument("Total budget must be positive.");
    }

    // Initialize variables
    std::vector<double> operation_times(num_machines, 0.0);
    double total_cost = 0.0;
    double total_production = 0.0;

    // Calculate optimal operation times
    for (int iii = 0; iii < num_machines; ++iii) {
        if (total_cost + operational_costs[iii] <= total_budget) {
            double time = (total_budget - total_cost) / operational_costs[iii];
            operation_times[iii] = time;
            total_cost += time * operational_costs[iii];
            total_production += time * production_rates[iii];
        }
    }

    // Handle remaining budget optimally
    if (total_cost < total_budget) {
        double remaining_budget = total_budget - total_cost;
        std::vector<double> remaining_production_rates(num_machines);
        for (int i = 0; i < num_machines; ++i) {
            if (operational_costs[i] <= remaining_budget) {
                remaining_production_rates[i] = production_rates[i];
            }
        }
        if (!remaining_production_rates.empty()) {
            int max_prod_index = std::max_element(remaining_production_rates.begin(), remaining_production_rates.end()) - remaining_production_rates.begin();
            operation_times[max_prod_index] += remaining_budget / operational_costs[max_prod_index];
        }
    }

    return operation_times;
}


#include <cassert>
int main() {
    // TEST
    int num_machines1 = 3;
    std::vector<double> production_rates1 = {1.0, 2.0, 1.5};
    std::vector<double> operational_costs1 = {10.0, 15.0, 5.0};
    double total_budget1 = 30.0;
    std::vector<double> result1 =
        MaxProductionOutput(num_machines1, production_rates1, operational_costs1, total_budget1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    int num_machines2 = 4;
    std::vector<double> production_rates2 = {1.2, 1.8, 1.0, 1.5};
    std::vector<double> operational_costs2 = {5.0, 10.0, 5.0, 5.0};
    double total_budget2 = 20.0;
    std::vector<double> result2 =
        MaxProductionOutput(num_machines2, production_rates2, operational_costs2, total_budget2);
    assert(result2.size() == 4);
    // TEST_END

    // TEST
    int num_machines3 = 2;
    std::vector<double> production_rates3 = {1.0, 1.5};
    std::vector<double> operational_costs3 = {5.0, 10.0};
    double total_budget3 = 15.0;
    std::vector<double> result3 =
        MaxProductionOutput(num_machines3, production_rates3, operational_costs3, total_budget3);
    assert(result3.size() == 2);
    // TEST_END

    // TEST
    int num_machines4 = 5;
    std::vector<double> production_rates4 = {1.0, 1.2, 1.4, 1.6, 1.8};
    std::vector<double> operational_costs4 = {10.0, 10.0, 10.0, 10.0, 10.0};
    double total_budget4 = 40.0;
    std::vector<double> result4 =
        MaxProductionOutput(num_machines4, production_rates4, operational_costs4, total_budget4);
    assert(result4.size() == 5);
    // TEST_END

    // TEST
    int num_machines5 = 3;
    std::vector<double> production_rates5 = {1.5, 1.0, 1.8};
    std::vector<double> operational_costs5 = {5.0, 10.0, 5.0};
    double total_budget5 = 20.0;
    std::vector<double> result5 =
        MaxProductionOutput(num_machines5, production_rates5, operational_costs5, total_budget5);
    assert(result5.size() == 3);
    // TEST_END

    // TEST
    try {
        MaxProductionOutput(-1, production_rates1, operational_costs1, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxProductionOutput(num_machines1, {1.0, 2.0}, operational_costs1, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxProductionOutput(num_machines1, production_rates1, {10.0, 15.0}, total_budget1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}