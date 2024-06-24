/***


 khaled_cpp_mil_229_2024_June_23: 5c845a25-73e4-48b5-a926-66a6f552fcab

 func_MaximizeMeetingSchedule_khaled_cpp_mil_229_2024_June_23


*/

/*


Design me a C++ function called MaximizeMeetingSchedule that takes an integer num_meetings, a vector of tuples of
doubles const std::vector<std::tuple<double, double, double>> representing the start time, end time, and importance of
each meeting, and a double min_time_gap. The function should return a vector of integers std::vector<int> representing
the optimal sequence of meetings to maximize the total importance of non-overlapping meetings using a Genetic Algorithm.



*/

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <tuple>
#include <vector>

struct Meeting {
    double start;
    double end;
    double importance;
    int index;

    bool operator<(const Meeting &other) const { return end < other.end; }
};

std::vector<int> GenerateIndividual(const std::vector<Meeting> &meetings, std::mt19937 &gen,
                                     std::uniform_real_distribution<> &dis, double min_time_gap) {
    std::vector<int> individual;
    double last_end_time = -min_time_gap;
    for (const Meeting &meeting : meetings) {
        if (dis(gen) > 0.5 && meeting.start >= last_end_time + min_time_gap) {
            individual.push_back(meeting.index);
            last_end_time = meeting.end;
        }
    }
    return individual;
}

double Fitness(const std::vector<int> &individual,
               const std::vector<std::tuple<double, double, double>> &meeting_info) {
    double total_importance = 0.0;
    for (int idx : individual) {
        total_importance += std::get<2>(meeting_info[idx]);
    }
    return total_importance;
}

std::vector<int> Crossover(const std::vector<int> &parent1, const std::vector<int> &parent2,
                           const std::vector<Meeting> &meetings, std::mt19937 &gen,
                           std::uniform_real_distribution<> &dis, double min_time_gap, double crossover_rate) {
    std::vector<int> offspring;
    double last_end_time = -min_time_gap;
    for (size_t i = 0; i < parent1.size() && i < parent2.size(); ++i) {
        if (dis(gen) < crossover_rate) {
            int idx = parent1[i];
            if (meetings[idx].start >= last_end_time + min_time_gap) {
                offspring.push_back(idx);
                last_end_time = meetings[idx].end;
            }
        } else {
            int idx = parent2[i];
            if (meetings[idx].start >= last_end_time + min_time_gap) {
                offspring.push_back(idx);
                last_end_time = meetings[idx].end;
            }
        }
    }
    return offspring;
}

void mutate(std::vector<int> &individual, const std::vector<Meeting> &meetings, std::mt19937 &gen,
            std::uniform_real_distribution<> &dis, std::uniform_int_distribution<> &index_dis, double min_time_gap,
            double mutation_rate) {
    if (dis(gen) < mutation_rate) {
        int idx = index_dis(gen);
        if (std::find(individual.begin(), individual.end(), idx) == individual.end()) {
            double last_end_time = (individual.empty() ? -min_time_gap : meetings[individual.back()].end);
            if (meetings[idx].start >= last_end_time + min_time_gap) {
                individual.push_back(idx);
            }
        }
    }
}

std::vector<int> MaximizeMeetingSchedule(int num_meetings,
                                         const std::vector<std::tuple<double, double, double>> &meeting_info,
                                         double min_time_gap) {
    if (num_meetings <= 0 || meeting_info.size() != num_meetings) {
        throw std::invalid_argument("Invalid input values");
    }

    std::vector<Meeting> meetings;
    for (int i = 0; i < num_meetings; ++i) {
        meetings.push_back(
            {std::get<0>(meeting_info[i]), std::get<1>(meeting_info[i]), std::get<2>(meeting_info[i]), i});
    }
    std::sort(meetings.begin(), meetings.end());

    const int population_size = 50;
    const int generations = 1000;
    const double mutation_rate = 0.1;
    const double crossover_rate = 0.8;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> index_dis(0, num_meetings - 1);

    std::vector<std::vector<int>> population(population_size);
    for (int i = 0; i < population_size; ++i) {
        population[i] = GenerateIndividual(meetings, gen, dis, min_time_gap);
    }

    std::vector<int> best_individual = population[0];
    double best_fitness = Fitness(best_individual, meeting_info);

    for (int generation = 0; generation < generations; ++generation) {
        std::vector<std::vector<int>> new_population;
        for (int i = 0; i < population_size; ++i) {
            std::vector<int> parent1 = population[index_dis(gen)];
            std::vector<int> parent2 = population[index_dis(gen)];
            std::vector<int> offspring = Crossover(parent1, parent2, meetings, gen, dis, min_time_gap, crossover_rate);
            mutate(offspring, meetings, gen, dis, index_dis, min_time_gap, mutation_rate);
            new_population.push_back(offspring);

            double current_fitness = Fitness(offspring, meeting_info);
            if (current_fitness > best_fitness) {
                best_fitness = current_fitness;
                best_individual = offspring;
            }
        }
        population = new_population;
    }

    return best_individual;
}

#include <cassert>
int main() {
    // TEST
    int num_meetings1 = 5;
    std::vector<std::tuple<double, double, double>> meeting_info1 = {
        {0.0, 1.0, 10.0}, {1.5, 2.5, 20.0}, {3.0, 4.0, 30.0}, {2.0, 3.5, 15.0}, {4.5, 5.5, 25.0}};
    double min_time_gap1 = 0.5;
    std::vector<int> result1 = MaximizeMeetingSchedule(num_meetings1, meeting_info1, min_time_gap1);
    for (size_t i = 1; i < result1.size(); ++i) {
        assert(std::get<1>(meeting_info1[result1[i - 1]]) + min_time_gap1 <= std::get<0>(meeting_info1[result1[i]]));
    }
    // TEST_END

    // TEST
    try {
        MaximizeMeetingSchedule(-1, meeting_info1, min_time_gap1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeMeetingSchedule(num_meetings1, {{0.0, 1.0, 10.0}}, min_time_gap1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
