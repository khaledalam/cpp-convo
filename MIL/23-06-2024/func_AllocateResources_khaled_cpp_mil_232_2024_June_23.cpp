/***


 khaled_cpp_mil_232_2024_June_23: cee0a4a4-05d1-480a-93fc-74f4b3410aed

 func_AllocateResources_khaled_cpp_mil_232_2024_June_23


*/

/*

Design a C++ function called AllocateResources that takes an integer num_tasks, a vector of doubles const
std::vector<double> representing the resource requirement for each task, and a double max_resources. The function should
return a vector of integers std::vector<int> representing the optimal set of tasks to maximize the total resource usage
without exceeding the maximum resources using Hill Climbing.


*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

std::vector<int> AllocateResources(int num_tasks, const std::vector<double> &task_resources, double max_resources) {
    if (num_tasks <= 0 || task_resources.size() != num_tasks) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<int> current_solution;
    double current_resource_usage = 0.0;

    for (int i = 0; i < num_tasks; ++i) {
        if (current_resource_usage + task_resources[i] <= max_resources) {
            current_solution.push_back(i);
            current_resource_usage += task_resources[i];
        }
    }

    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < num_tasks; ++i) {
            if (std::find(current_solution.begin(), current_solution.end(), i) == current_solution.end()) {
                if (current_resource_usage + task_resources[i] <= max_resources) {
                    current_solution.push_back(i);
                    current_resource_usage += task_resources[i];
                    improved = true;
                    break;
                }
            }
        }
    }

    return current_solution;
}

#include <cassert>
int main() {
    int num_tasks1 = 5;
    std::vector<double> task_resources1 = {10.0, 20.0, 30.0, 15.0, 25.0};
    double max_resources1 = 50.0;
    std::vector<int> result1 = AllocateResources(num_tasks1, task_resources1, max_resources1);
    double total_resources = 0.0;
    for (int idx : result1) {
        total_resources += task_resources1[idx];
    }
    assert(total_resources <= max_resources1);

    try {
        std::vector<double> task_resources2 = {10.0, 20.0, 30.0, 15.0, 25.0};
        double max_resources2 = 50.0;
        AllocateResources(-1, task_resources2, max_resources2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }

    try {
        int num_tasks3 = 5;
        double max_resources3 = 50.0;
        AllocateResources(num_tasks3, {10.0}, max_resources3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
}
