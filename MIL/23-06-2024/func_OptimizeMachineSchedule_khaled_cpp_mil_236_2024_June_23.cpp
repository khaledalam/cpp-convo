/***


 khaled_cpp_mil_236_2024_June_23: 0cf3f497-f8eb-4aa1-a849-ef768daf558e

 func_OptimizeMachineSchedule_khaled_cpp_mil_236_2024_June_23


 



*/

/*

Design a C++ function called OptimizeMachineSchedule that takes an integer num_jobs, an integer num_machines, a 2D
vector of doubles const std::vector<std::vector<double>> representing the processing times of each job on each machine.
The function should return a vector of integers std::vector<int> representing the optimal sequence of jobs on each
machine to minimize the total completion time using Simulated Annealing.

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

double CalculateCompletionTime(const std::vector<int> &schedule,
                               const std::vector<std::vector<double>> &processing_times) {
    int num_jobs = schedule.size();
    int num_machines = processing_times[0].size();
    std::vector<double> machine_completion_time(num_machines, 0);
    std::vector<double> job_completion_time(num_jobs, 0);

    for (int job : schedule) {
        double start_time = job_completion_time[job];
        for (int machine = 0; machine < num_machines; ++machine) {
            start_time = std::max(start_time, machine_completion_time[machine]);
            machine_completion_time[machine] = start_time + processing_times[job][machine];
            start_time = machine_completion_time[machine];
        }
        job_completion_time[job] = start_time;
    }

    return *std::max_element(machine_completion_time.begin(), machine_completion_time.end());
}

std::vector<int> GenerateNeighbor(const std::vector<int> &current_schedule) {
    std::vector<int> neighbor_schedule = current_schedule;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, current_schedule.size() - 1);
    int idx1 = dis(gen);
    int idx2 = dis(gen);
    std::swap(neighbor_schedule[idx1], neighbor_schedule[idx2]);
    return neighbor_schedule;
}

std::vector<int> OptimizeMachineSchedule(int num_jobs, int num_machines,
                                         const std::vector<std::vector<double>> &processing_times) {
    if (num_jobs <= 0 || num_machines <= 0 || processing_times.size() != num_jobs ||
        processing_times[0].size() != num_machines) {
        throw std::invalid_argument("Invalid input values");
    }

    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<int> current_schedule(num_jobs);
    std::iota(current_schedule.begin(), current_schedule.end(), 0);
    std::shuffle(current_schedule.begin(), current_schedule.end(), gen);
    double current_completion_time = CalculateCompletionTime(current_schedule, processing_times);

    std::vector<int> best_schedule = current_schedule;
    double best_completion_time = current_completion_time;

    double temperature = 1000.0;
    double cooling_rate = 0.99;

    while (temperature > 1.0) {
        std::vector<int> neighbor_schedule = GenerateNeighbor(current_schedule);
        double neighbor_completion_time = CalculateCompletionTime(neighbor_schedule, processing_times);

        if (neighbor_completion_time < current_completion_time ||
            std::exp((current_completion_time - neighbor_completion_time) / temperature) > dis(gen)) {
            current_schedule = neighbor_schedule;
            current_completion_time = neighbor_completion_time;
        }

        if (current_completion_time < best_completion_time) {
            best_schedule = current_schedule;
            best_completion_time = current_completion_time;
        }

        temperature *= cooling_rate;
    }

    return best_schedule;
}

#include <cassert>
int main() {
    // TEST
    int num_jobs1 = 4;
    int num_machines1 = 3;
    std::vector<std::vector<double>> processing_times1 = {
        {2.0, 3.0, 2.5}, {1.5, 2.0, 3.5}, {3.0, 1.5, 2.0}, {2.5, 2.5, 1.5}};

    std::vector<int> result1 = OptimizeMachineSchedule(num_jobs1, num_machines1, processing_times1);
    assert(result1.size() == num_jobs1);
    // TEST_END

    // TEST
    try {
        OptimizeMachineSchedule(-1, num_machines1, processing_times1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeMachineSchedule(num_jobs1, -1, processing_times1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
