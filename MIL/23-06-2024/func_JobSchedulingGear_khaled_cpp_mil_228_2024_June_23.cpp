/***


 khaled_cpp_mil_228_2024_June_23: c33606fa-e07e-4472-bc62-4e2c8c6ed4d8

 func_JobSchedulingGear_khaled_cpp_mil_228_2024_June_23
 

*/

/*

Design a C++ function called JobSchedulingGear that takes an integer num_jobs, a vector of tuples of doubles const
std::vector<std::tuple<double, double, double>> representing the start time, end time, and profit of each job, and a
double min_time_gap. The function should return a vector of integers std::vector<int> representing the optimal sequence
of jobs to maximize the total profit of non-overlapping jobs using Tabu Search.



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

struct Job {
    double start;
    double end;
    double profit;
    int index;

    bool operator<(const Job &other) const { return end < other.end; }
};

std::vector<int> JobSchedulingGear(int num_jobs, const std::vector<std::tuple<double, double, double>> &job_info,
                                       double min_time_gap) {
    if (num_jobs <= 0 || job_info.size() != num_jobs) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Job> jobs;
    for (int iii = 0; iii < num_jobs; ++iii) {
        jobs.push_back({std::get<0>(job_info[iii]), std::get<1>(job_info[iii]), std::get<2>(job_info[iii]), iii});
    }
    std::sort(jobs.begin(), jobs.end());

    std::vector<int> best_sequence;
    double best_total_profit = 0.0;

    const int tabu_tenure = 5;
    std::unordered_set<int> tabu_list;
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_int_distribution<> dis(0, num_jobs - 1);

    for (int iteration = 0; iteration < 1000; ++iteration) {
        std::vector<int> current_sequence;
        double current_total_profit = 0.0;
        double last_end_time = -min_time_gap;

        for (const Job &job : jobs) {
            if (job.start >= last_end_time + min_time_gap && tabu_list.find(job.index) == tabu_list.end()) {
                current_sequence.push_back(job.index);
                current_total_profit += job.profit;
                last_end_time = job.end;
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
    int num_jobs1 = 5;
    std::vector<std::tuple<double, double, double>> job_info1 = {
        {0.0, 2.0, 50.0}, {2.5, 4.0, 60.0}, {5.0, 6.0, 70.0}, {3.0, 5.0, 30.0}, {1.0, 3.5, 40.0}};
    double min_time_gap1 = 1.0;
    std::vector<int> result1 = JobSchedulingGear(num_jobs1, job_info1, min_time_gap1);
    for (size_t i = 1; i < result1.size(); ++i) {
        assert(std::get<1>(job_info1[result1[i - 1]]) + min_time_gap1 <= std::get<0>(job_info1[result1[i]]));
    }
    // TEST_END

    // TEST
    try {
        JobSchedulingGear(-1, job_info1, min_time_gap1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        JobSchedulingGear(num_jobs1, {{0.0, 2.0, 50.0}}, min_time_gap1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
