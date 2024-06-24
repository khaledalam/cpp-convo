/***


 khaled_cpp_mil_227_2024_June_23: 0560a0ce-2284-4eb8-8236-abe220e538ae

 func_OptimizeTaskSelection_khaled_cpp_mil_227_2024_June_23


*/

/*

Design me a C++ function called OptimizeTaskSelection that takes an integer num_tasks, a vector of tuples of doubles
const std::vector<std::tuple<double, double, double>> representing the start time, end time, and profit of each task,
and a double min_time_gap. The function should return a vector of integers std::vector<int> representing the optimal
sequence of tasks to maximize the total profit of non-overlapping tasks using Tabu Search.



*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

struct Task {
    double start;
    double end;
    double profit;
    int index;

    bool operator<(const Task &other) const { return end < other.end; }
};

std::vector<int> OptimizeTaskSelection(int num_tasks, const std::vector<std::tuple<double, double, double>> &task_info,
                                       double min_time_gap) {
    if (num_tasks <= 0 || task_info.size() != num_tasks) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Task> tasks;
    for (int iii = 0; iii < num_tasks; ++iii) {
        tasks.push_back({std::get<0>(task_info[iii]), std::get<1>(task_info[iii]), std::get<2>(task_info[iii]), iii});
    }
    std::sort(tasks.begin(), tasks.end());

    std::vector<int> best_sequence;
    double best_total_profit = 0.0;

    const int tabu_tenure = 5;
    std::unordered_set<int> tabu_list;
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_int_distribution<> dis(0, num_tasks - 1);

    for (int iteration = 0; iteration < 1000; ++iteration) {
        std::vector<int> current_sequence;
        double current_total_profit = 0.0;
        double last_end_time = -min_time_gap;

        for (const Task &task : tasks) {
            if (task.start >= last_end_time + min_time_gap && tabu_list.find(task.index) == tabu_list.end()) {
                current_sequence.push_back(task.index);
                current_total_profit += task.profit;
                last_end_time = task.end;
            }
        }

        if (current_total_profit > best_total_profit) {
            best_sequence = current_sequence;
            best_total_profit = current_total_profit;
        }

        if (tabu_list.size() >= tabu_tenure) {
            tabu_list.erase(tabu_list.begin());
        }
        tabu_list.insert(dis(gen));
    }

    return best_sequence;
}

#include <cassert>
int main() {
    // TEST
    int num_tasks1 = 4;
    std::vector<std::tuple<double, double, double>> task_info1 = {
        {0.0, 1.0, 10.0}, {1.5, 2.5, 20.0}, {3.0, 4.0, 15.0}, {2.0, 3.5, 25.0}};
    double min_time_gap1 = 0.5;
    std::vector<int> result1 = OptimizeTaskSelection(num_tasks1, task_info1, min_time_gap1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    try {
        std::vector<std::tuple<double, double, double>> task_info2 = {
            {0.0, 1.0, 10.0}, {1.5, 2.5, 20.0}, {3.0, 4.0, 15.0}, {2.0, 3.5, 25.0}};
        double min_time_gap2 = 0.5;
        OptimizeTaskSelection(-1, task_info2, min_time_gap2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        int num_tasks3 = 4;
        double min_time_gap3 = 0.5;
        OptimizeTaskSelection(num_tasks3, {{0.0, 1.0, 10.0}}, min_time_gap3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
