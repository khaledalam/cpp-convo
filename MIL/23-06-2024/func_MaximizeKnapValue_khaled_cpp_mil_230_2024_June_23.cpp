/***


 khaled_cpp_mil_230_2024_June_23: 609fa70c-6b3b-4131-a3ca-eee93dc3a9a4

 func_MaximizeKnapValue_khaled_cpp_mil_230_2024_June_23



*/

/*


Design a C++ function called MaximizeKnapValue that takes an integer num_items, a vector of pairs of doubles const
std::vector<std::pair<double, double>> representing the weight and value of each item, and a double max_weight. The
function should return a vector of integers std::vector<int> representing the optimal set of items to maximize the total
value without exceeding the maximum weight using Simulated Annealing.


*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <tuple>
#include <vector>

struct Item {
    double weight;
    double value;
    int index;

    bool operator<(const Item &other) const { return value / weight > other.value / weight; }
};

std::vector<int> MaximizeKnapValue(int num_items, const std::vector<std::pair<double, double>> &item_info,
                                   double max_weight) {
    if (num_items <= 0 || item_info.size() != num_items) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Item> items;
    for (int i = 0; i < num_items; ++i) {
        items.push_back({item_info[i].first, item_info[i].second, i});
    }

    double temperature = 1000.0;
    double cooling_rate = 0.99;
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<int> best_solution;
    double best_value = 0.0;
    std::vector<int> current_solution;
    double current_value = 0.0;
    double current_weight = 0.0;

    while (temperature > 1.0) {
        int item_index = std::uniform_int_distribution<>(0, num_items - 1)(gen);
        const Item &item = items[item_index];

        if (std::find(current_solution.begin(), current_solution.end(), item.index) == current_solution.end()) {
            if (current_weight + item.weight <= max_weight) {
                current_solution.push_back(item.index);
                current_value += item.value;
                current_weight += item.weight;
            }
        } else {
            current_solution.erase(std::remove(current_solution.begin(), current_solution.end(), item.index),
                                   current_solution.end());
            current_value -= item.value;
            current_weight -= item.weight;
        }

        if (current_value > best_value) {
            best_solution = current_solution;
            best_value = current_value;
        } else if (std::exp((current_value - best_value) / temperature) > dis(gen)) {
            best_solution = current_solution;
            best_value = current_value;
        }

        temperature *= cooling_rate;
    }

    return best_solution;
}

#include <cassert>
int main() {
    int num_items1 = 5;
    std::vector<std::pair<double, double>> item_info1 = {
        {10.0, 60.0}, {20.0, 100.0}, {30.0, 120.0}, {15.0, 75.0}, {25.0, 90.0}};
    double max_weight1 = 50.0;
    std::vector<int> result1 = MaximizeKnapValue(num_items1, item_info1, max_weight1);
    double total_weight = 0.0, total_value = 0.0;
    for (int idx : result1) {
        total_weight += item_info1[idx].first;
        total_value += item_info1[idx].second;
    }
    assert(total_weight <= max_weight1);

    try {
        std::vector<std::pair<double, double>> item_info2 = {
            {10.0, 60.0}, {20.0, 100.0}, {30.0, 120.0}, {15.0, 75.0}, {25.0, 90.0}};
        double max_weight2 = 50.0;
        MaximizeKnapValue(-1, item_info2, max_weight2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }

    try {
        int num_items3 = 5;
        double max_weight3 = 50.0;
        MaximizeKnapValue(num_items3, {{10.0, 60.0}}, max_weight3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
}
