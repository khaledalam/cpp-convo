/***


 khaled_cpp_mil_239_2024_June_23: 6c74ec5b-febd-4106-bc16-7e8fa94aca46

 func_OptimizeSchoolTimetableSA_khaled_cpp_mil_239_2024_June_23








*/

/*



Design a C++ function called OptimizeSchoolTimetableSA that takes an integer num_classes, a 2D vector of doubles const
std::vector<std::vector<double>> representing the preferences of each class for each timeslot, and an integer
num_timeslots. The function should return a vector of integers std::vector<int> representing the optimal timeslot for
each class to maximize the total preference score using Simulated Annealing.



*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

double CalculateTotalPreference(const std::vector<int> &timeslot_assignment,
                                const std::vector<std::vector<double>> &preferences) {
    double total_preference = 0.0;
    for (size_t i = 0; i < timeslot_assignment.size(); ++i) {
        total_preference += preferences[i][timeslot_assignment[i]];
    }
    return total_preference;
}

std::vector<int> GenerateNeighbor(const std::vector<int> &current_assignment, int num_timeslots) {
    std::vector<int> neighbor = current_assignment;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, current_assignment.size() - 1);
    int idx = dis(gen);
    neighbor[idx] = std::uniform_int_distribution<>(0, num_timeslots - 1)(gen);
    return neighbor;
}

std::vector<int> OptimizeSchoolTimetableSA(int num_classes, const std::vector<std::vector<double>> &preferences,
                                           int num_timeslots) {
    if (num_classes <= 0 || preferences.size() != num_classes || num_timeslots <= 0) {
        throw std::invalid_argument("Invalid input values");
    }

    std::random_device rdd;
    std::mt19937 gen(rdd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    std::vector<int> current_assignment(num_classes);
    for (int i = 0; i < num_classes; ++i) {
        current_assignment[i] = std::uniform_int_distribution<>(0, num_timeslots - 1)(gen);
    }
    double current_preference = CalculateTotalPreference(current_assignment, preferences);

    std::vector<int> best_assignment = current_assignment;
    double best_preference = current_preference;

    double temperature = 1000.0;
    double cooling_rate = 0.99;

    while (temperature > 1.0) {
        std::vector<int> neighbor_assignment = GenerateNeighbor(current_assignment, num_timeslots);
        double neighbor_preference = CalculateTotalPreference(neighbor_assignment, preferences);

        if (neighbor_preference > current_preference ||
            std::exp((current_preference - neighbor_preference) / temperature) > dis(gen)) {
            current_assignment = neighbor_assignment;
            current_preference = neighbor_preference;
        }

        if (current_preference > best_preference) {
            best_assignment = current_assignment;
            best_preference = current_preference;
        }

        temperature *= cooling_rate;
    }

    return best_assignment;
}

#include <cassert>
int main() {
    // TEST
    int num_classes1 = 4;
    int num_timeslots1 = 3;
    std::vector<std::vector<double>> preferences1 = {
        {1.0, 2.0, 3.0}, {2.0, 3.0, 1.0}, {3.0, 1.0, 2.0}, {1.0, 3.0, 2.0}};

    std::vector<int> result1 = OptimizeSchoolTimetableSA(num_classes1, preferences1, num_timeslots1);
    assert(result1.size() == num_classes1);
    for (int timeslot : result1) {
        assert(timeslot >= 0 && timeslot < num_timeslots1);
    }
    // TEST_END

    // TEST
    try {
        OptimizeSchoolTimetableSA(-1, {{1.0, 2.0, 3.0}, {2.0, 3.0, 1.0}, {3.0, 1.0, 2.0}, {1.0, 3.0, 2.0}}, 3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeSchoolTimetableSA(4, {{1.0}}, 3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
