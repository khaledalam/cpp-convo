/***


 khaled_cpp_201_2024_June_09: c74456bc-064b-4f6a-ae18-b843cdf61847


func_MaximizeProjectReturns_khaled_cpp_201_2024_June_09

*/

/*



Design a C++ function called MaximizeProjectReturns that takes an integer num_projects, a vector of doubles const std::vector<double> representing the expected returns of each project, a vector of doubles const std::vector<double> representing the risks (standard deviations) of each project, and a double risk_tolerance. The function should return a vector of doubles std::vector<double> representing the optimal allocation of funding to the projects to maximize the return while minimizing the risk according to the given risk tolerance using a Genetic Algorithm. Please don't forget to validate the inputs.



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

struct Individual {
    std::vector<double> allocations;
    double fitness;

    bool operator<(const Individual &other) const { return fitness > other.fitness; }
};

double CalculatePortfolioRisk(const std::vector<double> &allocations, const std::vector<double> &risks) {
    double risk = 0.0;
    int num_projects = allocations.size();
    for (int i = 0; i < num_projects; ++i) {
        risk += allocations[i] * risks[i];
    }
    return risk;
}

double CalculateFitness(const std::vector<double> &allocations, const std::vector<double> &returns,
                        const std::vector<double> &risks, double risk_tolerance) {
    double total_return = 0.0;
    double risk = CalculatePortfolioRisk(allocations, risks);
    for (int i = 0; i < returns.size(); ++i) {
        total_return += allocations[i] * returns[i];
    }
    return (risk <= risk_tolerance) ? total_return / risk : 0.0;
}

std::vector<double> MaximizeProjectReturns(int num_projects, const std::vector<double> &returns,
                                           const std::vector<double> &risks, double risk_tolerance) {
    if (num_projects <= 0 || returns.size() != num_projects || risks.size() != num_projects) {
        throw std::invalid_argument("Invalid input values");
    }

    const int population_size = 100;
    const int num_generations = 1000;
    const double mutation_rate = 0.1;
    std::vector<Individual> population(population_size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int iii = 0; iii < population_size; ++iii) {
        population[iii].allocations.resize(num_projects);
        for (int jjj = 0; jjj < num_projects; ++jjj) {
            population[iii].allocations[jjj] = dis(gen);
        }
        population[iii].fitness = CalculateFitness(population[iii].allocations, returns, risks, risk_tolerance);
    }

    for (int generation = 0; generation < num_generations; ++generation) {
        std::sort(population.begin(), population.end());
        std::vector<Individual> new_population(population_size);

        for (int iii = 0; iii < population_size; ++iii) {
            std::uniform_int_distribution<> parent_dist(0, population_size / 2);
            Individual parent1 = population[parent_dist(gen)];
            Individual parent2 = population[parent_dist(gen)];
            new_population[iii].allocations.resize(num_projects);

            for (int jjj = 0; jjj < num_projects; ++jjj) {
                new_population[iii].allocations[jjj] = (dis(gen) < 0.5) ? parent1.allocations[jjj] : parent2.allocations[jjj];
                if (dis(gen) < mutation_rate) {
                    new_population[iii].allocations[jjj] = dis(gen);
                }
            }
            new_population[iii].fitness = CalculateFitness(new_population[iii].allocations, returns, risks, risk_tolerance);
        }

        population = new_population;
    }

    return std::max_element(population.begin(), population.end())->allocations;
}

int main() {
    // TEST
    int num_projects1 = 3;
    std::vector<double> returns1 = {0.1, 0.2, 0.15};
    std::vector<double> risks1 = {0.05, 0.1, 0.07};
    double risk_tolerance1 = 0.08;
    std::vector<double> result1 = MaximizeProjectReturns(num_projects1, returns1, risks1, risk_tolerance1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    int num_projects2 = 4;
    std::vector<double> returns2 = {0.12, 0.18, 0.1, 0.15};
    std::vector<double> risks2 = {0.06, 0.08, 0.05, 0.07};
    double risk_tolerance2 = 0.07;
    std::vector<double> result2 = MaximizeProjectReturns(num_projects2, returns2, risks2, risk_tolerance2);
    assert(result2.size() == 4);
    // TEST_END

    // TEST
    try {
        MaximizeProjectReturns(-1, returns1, risks1, risk_tolerance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeProjectReturns(num_projects1, {0.1, 0.2}, risks1, risk_tolerance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaximizeProjectReturns(num_projects1, returns1, {0.05, 0.1}, risk_tolerance1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
