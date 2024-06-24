/***


 khaled_cpp_206_2024_June_09: 24fcec11-8a3c-4fc0-85eb-3666078b10f1

 func_OptimizeFlightSchedules_khaled_cpp_206_2024_June_09



*/

/*

Design a C++ function called OptimizeFlightSchedules that takes an integer num_flights, a vector of pairs of doubles const std::vector<std::pair<double, double>> representing the start and end times of each flight, and a double min_time_gap. The function should return a vector of integers std::vector<int> representing the optimal sequence of flights to maximize the total number of non-overlapping flights using Tabu Search. Please don't forget to validate the inputs.

*/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

struct Flight {
    double start;
    double end;
    int index;

    bool operator<(const Flight &other) const { return end < other.end; }
};

std::vector<int> OptimizeFlightSchedules(int num_flights, const std::vector<std::pair<double, double>> &flight_times,
                                         double min_time_gap) {
    if (num_flights <= 0 || flight_times.size() != num_flights) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Flight> flights;
    for (int iii = 0; iii < num_flights; ++iii) {
        flights.push_back({flight_times[iii].first, flight_times[iii].second, iii});
    }
    std::sort(flights.begin(), flights.end());

    std::vector<int> best_sequence;
    double best_total_time = 0.0;

    const int tabu_tenure = 5;
    std::unordered_set<int> tabu_list;
    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_int_distribution<> dis(0, num_flights - 1);

    for (int iteration = 0; iteration < 1000; ++iteration) {
        std::vector<int> current_sequence;
        double current_total_time = 0.0;
        double last_end_time = -min_time_gap;

        for (const auto &flight : flights) {
            if (flight.start >= last_end_time + min_time_gap && tabu_list.find(flight.index) == tabu_list.end()) {
                current_sequence.push_back(flight.index);
                current_total_time += flight.end - flight.start;
                last_end_time = flight.end;
            }
        }

        if (current_total_time > best_total_time) {
            best_sequence = current_sequence;
            best_total_time = current_total_time;
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
    int num_flights1 = 4;
    std::vector<std::pair<double, double>> flight_times1 = {{0.0, 1.0}, {1.5, 2.5}, {3.0, 4.0}, {2.0, 3.5}};
    double min_time_gap1 = 0.5;
    std::vector<int> result1 = OptimizeFlightSchedules(num_flights1, flight_times1, min_time_gap1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    try {
        OptimizeFlightSchedules(-1, flight_times1, min_time_gap1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeFlightSchedules(num_flights1, {{0.0, 1.0}}, min_time_gap1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
