/***


 khaled_cpp_mil_238_2024_June_23: 0c358a76-4331-4536-bc37-fcaeaafc451d

 func_OptimizeTeamFormationGA_khaled_cpp_mil_238_2024_June_23







*/

/*

Design a C++ function called OptimizeTeamFormationGA that takes an integer num_members, an integer num_teams, a 2D
vector of doubles const std::vector<std::vector<double>> representing the compatibility score between team members, and
an integer team_size representing the size of each team. The function should return a vector of vectors of integers
std::vector<std::vector<int>> representing the optimal team formation to maximize the overall compatibility score using
Genetic Algorithm.


*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <stdexcept>
#include <vector>

struct Individual {
    std::vector<std::vector<int>> teams;
    double fitness;
};

double CalculateCompatibility(const std::vector<std::vector<int>> &teams,
                              const std::vector<std::vector<double>> &compatibility_matrix) {
    double total_compatibility = 0.0;
    for (const auto &team : teams) {
        for (size_t i = 0; i < team.size(); ++i) {
            for (size_t j = i + 1; j < team.size(); ++j) {
                total_compatibility += compatibility_matrix[team[i]][team[j]];
            }
        }
    }
    return total_compatibility;
}

std::vector<std::vector<int>> OptimizeTeamFormationGA(int num_members, int num_teams,
                                                      const std::vector<std::vector<double>> &compatibility_matrix,
                                                      int team_size) {
    if (num_members <= 0 || num_teams <= 0 || compatibility_matrix.size() != num_members || team_size <= 0) {
        throw std::invalid_argument("Invalid input values");
    }

    const int population_size = 100;
    const int generations = 1000;
    const double mutation_rate = 0.05;
    const double crossover_rate = 0.9;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_int_distribution<> member_dis(0, num_members - 1);

    auto generate_random_teams = [&]() {
        std::vector<int> members(num_members);
        std::iota(members.begin(), members.end(), 0);
        std::shuffle(members.begin(), members.end(), gen);
        std::vector<std::vector<int>> teams(num_teams, std::vector<int>(team_size));
        for (int i = 0; i < num_teams; ++i) {
            for (int j = 0; j < team_size; ++j) {
                teams[i][j] = members[i * team_size + j];
            }
        }
        return teams;
    };

    std::vector<Individual> population(population_size);
    for (int i = 0; i < population_size; ++i) {
        population[i].teams = generate_random_teams();
        population[i].fitness = CalculateCompatibility(population[i].teams, compatibility_matrix);
    }

    auto crossover = [&](const std::vector<std::vector<int>> &parent1, const std::vector<std::vector<int>> &parent2) {
        std::vector<std::vector<int>> child(num_teams, std::vector<int>(team_size));
        for (int i = 0; i < num_teams; ++i) {
            for (int j = 0; j < team_size; ++j) {
                if (dis(gen) < crossover_rate) {
                    child[i][j] = parent1[i][j];
                } else {
                    child[i][j] = parent2[i][j];
                }
            }
        }
        return child;
    };

    auto mutate = [&](std::vector<std::vector<int>> &teams) {
        if (dis(gen) < mutation_rate) {
            int team_idx1 = std::uniform_int_distribution<>(0, num_teams - 1)(gen);
            int team_idx2 = std::uniform_int_distribution<>(0, num_teams - 1)(gen);
            int member_idx1 = std::uniform_int_distribution<>(0, team_size - 1)(gen);
            int member_idx2 = std::uniform_int_distribution<>(0, team_size - 1)(gen);
            std::swap(teams[team_idx1][member_idx1], teams[team_idx2][member_idx2]);
        }
    };

    for (int generation = 0; generation < generations; ++generation) {
        std::vector<Individual> new_population;
        for (int i = 0; i < population_size; ++i) {
            const Individual &parent1 = population[std::uniform_int_distribution<>(0, population_size - 1)(gen)];
            const Individual &parent2 = population[std::uniform_int_distribution<>(0, population_size - 1)(gen)];
            Individual child;
            child.teams = crossover(parent1.teams, parent2.teams);
            mutate(child.teams);
            child.fitness = CalculateCompatibility(child.teams, compatibility_matrix);
            new_population.push_back(child);
        }
        population = new_population;
    }

    return std::max_element(population.begin(), population.end(),
                            [](const Individual &a, const Individual &b) { return a.fitness < b.fitness; })
        ->teams;
}

#include <cassert>
int main() {
    // TEST
    int num_members1 = 6;
    int num_teams1 = 2;
    int team_size1 = 3;
    std::vector<std::vector<double>> compatibility_matrix1 = {{0, 1, 2, 1, 0, 1}, {1, 0, 1, 2, 1, 0},
                                                              {2, 1, 0, 1, 2, 1}, {1, 2, 1, 0, 1, 2},
                                                              {0, 1, 2, 1, 0, 1}, {1, 0, 1, 2, 1, 0}};

    std::vector<std::vector<int>> result1 =
        OptimizeTeamFormationGA(num_members1, num_teams1, compatibility_matrix1, team_size1);
    assert(result1.size() == num_teams1);
    for (const auto &team : result1) {
        assert(team.size() == team_size1);
    }
    // TEST_END

    // TEST
    try {
        OptimizeTeamFormationGA(-1, 2,
                                {{0, 1, 2, 1, 0, 1},
                                 {1, 0, 1, 2, 1, 0},
                                 {2, 1, 0, 1, 2, 1},
                                 {1, 2, 1, 0, 1, 2},
                                 {0, 1, 2, 1, 0, 1},
                                 {1, 0, 1, 2, 1, 0}},
                                3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        OptimizeTeamFormationGA(6, -1,
                                {{0, 1, 2, 1, 0, 1},
                                 {1, 0, 1, 2, 1, 0},
                                 {2, 1, 0, 1, 2, 1},
                                 {1, 2, 1, 0, 1, 2},
                                 {0, 1, 2, 1, 0, 1},
                                 {1, 0, 1, 2, 1, 0}},
                                3);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
