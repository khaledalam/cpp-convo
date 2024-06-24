/***


 khaled_cpp_204_2024_June_09: f5ae9304-060f-4393-b416-40d0bdd9a2c4

 func_OptimizeStaffSchedule_khaled_cpp_204_2024_June_09



*/

/*




Design me a C++ function called OptimizeStaffSchedule that takes an integer num_employees, a vector of doubles const std::vector<double> representing the hourly wage of each employee, a 2D vector of doubles const std::vector<std::vector<double>> representing the availability matrix of each employee, and an integer num_hours. The function should return a vector of integers std::vector<int> representing the optimal schedule to minimize the total wage while satisfying the required hours using a Genetic Algorithm. Please don't forget to validate the inputs.


*/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct Schedule {
    std::vector<int> hours;
    double total_wage;

    bool operator<(const Schedule &other) const { return total_wage < other.total_wage; }
};

double CalculateTotalWage(const std::vector<int> &hours, const std::vector<double> &wages) {
    double total_wage = 0.0;
    for (int iii = 0; iii < hours.size(); ++iii) {
        total_wage += hours[iii] * wages[iii];
    }
    return total_wage;
}

std::vector<int> OptimizeStaffSchedule(int num_employees, const std::vector<double> &wages,
                                       const std::vector<std::vector<double>> &availability, int num_hours) {
    if (num_employees <= 0 || wages.size() != num_employees || availability.size() != num_employees ||
        availability[0].size() != num_hours) {
        throw std::invalid_argument("Invalid input values");
    }

    const int population_size = 100;
    const double mutation_rate = 0.1;
    std::vector<Schedule> population(population_size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, num_hours);

    for (int iii = 0; iii < population_size; ++iii) {
        population[iii].hours.resize(num_employees);
        for (int jjj = 0; jjj < num_employees; ++jjj) {
            population[iii].hours[jjj] = dis(gen);
        }
        population[iii].total_wage = CalculateTotalWage(population[iii].hours, wages);
    }

    for (int iteration = 0; iteration < 1000; ++iteration) {
        std::sort(population.begin(), population.end());
        std::vector<Schedule> new_population(population_size);

        for (int iii = 0; iii < population_size; ++iii) {
            std::uniform_int_distribution<> parent_dist(0, population_size / 2);
            Schedule parent1 = population[parent_dist(gen)];
            Schedule parent2 = population[parent_dist(gen)];
            new_population[iii].hours.resize(num_employees);

            for (int jjj = 0; jjj < num_employees; ++jjj) {
                new_population[iii].hours[jjj] = (dis(gen) < 5) ? parent1.hours[jjj] : parent2.hours[jjj];
                if (dis(gen) < mutation_rate * 10) {
                    new_population[iii].hours[jjj] = dis(gen);
                }
            }
            new_population[iii].total_wage = CalculateTotalWage(new_population[iii].hours, wages);
        }

        population = new_population;
    }

    return std::min_element(population.begin(), population.end())->hours;
}

#include <cassert>
int main() {
    // TEST
    int num_employees1 = 3;
    std::vector<double> wages1 = {20.0, 25.0, 30.0};
    std::vector<std::vector<double>> availability1 = {{1, 1, 1, 1}, {1, 1, 1, 1}, {1, 1, 1, 1}};
    int num_hours1 = 4;
    std::vector<int> result1 = OptimizeStaffSchedule(num_employees1, wages1, availability1, num_hours1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    int num_employees2 = 4;
    std::vector<double> wages2 = {22.0, 24.0, 26.0, 28.0};
    std::vector<std::vector<double>> availability2 = {
        {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1}};
    int num_hours2 = 5;
    std::vector<int> result2 = OptimizeStaffSchedule(num_employees2, wages2, availability2, num_hours2);
    assert(result2.size() == 4);
    // TEST_END

    // TEST
    try {
        OptimizeStaffSchedule(-1, wages1, availability1, num_hours1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeStaffSchedule(num_employees1, {20.0, 25.0}, availability1, num_hours1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeStaffSchedule(num_employees1, wages1, {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}, num_hours1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}