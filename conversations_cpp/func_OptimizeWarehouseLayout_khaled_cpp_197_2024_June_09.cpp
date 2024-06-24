/***


 khaled_cpp_197_2024_June_09: 50a9ab26-8b82-4f0d-985d-0328a8cf90b4


func_OptimizeWarehouseLayout_khaled_cpp_197_2024_June_09


*/

/*


Design me a C++ function called OptimizeWarehouseLayout that takes an integer num_sections, a vector of doubles const
std::vector<double> representing the space requirements of each section, a vector of doubles const std::vector<double>
representing the adjacency benefits between pairs of sections, and a double total_space. The function should return a
vector of doubles std::vector<double> representing the optimal layout to maximize the adjacency benefits while fitting
within the total space. Please don't forget to validate the inputs.




*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Layout {
    double total_benefit;
    std::vector<double> layout;

    bool operator<(const Layout &other) const { return total_benefit > other.total_benefit; }
};

double CalculateTotalBenefit(const std::vector<double> &layout, const std::vector<double> &space_requirements,
                             const std::vector<std::vector<double>> &adjacency_benefits) {
    double total_benefit = 0.0;
    int num_sections = layout.size();
    for (int i = 0; i < num_sections; ++i) {
        total_benefit += layout[i] * space_requirements[i];
        for (int j = 0; j < num_sections; ++j) {
            total_benefit += layout[i] * layout[j] * adjacency_benefits[i][j];
        }
    }
    return total_benefit;
}

std::vector<double> OptimizeWarehouseLayout(int num_sections, const std::vector<double> &space_requirements,
                                            const std::vector<std::vector<double>> &adjacency_benefits,
                                            double total_space) {
    if (num_sections <= 0) {
        throw std::invalid_argument("Number of sections must be positive");
    }
    if (space_requirements.size() != num_sections) {
        throw std::invalid_argument("Space requirements size mismatch");
    }
    if (adjacency_benefits.size() != num_sections || adjacency_benefits[0].size() != num_sections) {
        throw std::invalid_argument("Adjacency benefits matrix size mismatch");
    }

    std::vector<Layout> layouts;
    int num_combinations = 1 << num_sections;

    for (int mask = 0; mask < num_combinations; ++mask) {
        std::vector<double> current_layout(num_sections, 0.0);
        double used_space = 0.0;

        for (int i = 0; i < num_sections; ++i) {
            if (mask & (1 << i)) {
                current_layout[i] = space_requirements[i];
                used_space += space_requirements[i];
            }
        }

        if (used_space <= total_space) {
            double total_benefit = CalculateTotalBenefit(current_layout, space_requirements, adjacency_benefits);
            layouts.push_back({total_benefit, current_layout});
        }
    }

    if (layouts.empty()) {
        throw std::runtime_error("No valid layouts found within the given total space");
    }

    return std::max_element(layouts.begin(), layouts.end())->layout;
}

int main() {
    // TEST
    int num_sections1 = 3;
    std::vector<double> space_requirements1 = {1.0, 2.0, 1.5};
    std::vector<std::vector<double>> adjacency_benefits1 = {{0.5, 0.2, 0.3}, {0.2, 0.5, 0.4}, {0.3, 0.4, 0.5}};
    double total_space1 = 4.0;
    std::vector<double> result1 =
        OptimizeWarehouseLayout(num_sections1, space_requirements1, adjacency_benefits1, total_space1);
    assert(result1.size() == 3);
    // TEST_END

    // TEST
    int num_sections2 = 4;
    std::vector<double> space_requirements2 = {1.2, 1.8, 1.0, 1.5};
    std::vector<std::vector<double>> adjacency_benefits2 = {
        {0.3, 0.4, 0.2, 0.5}, {0.4, 0.3, 0.5, 0.2}, {0.2, 0.5, 0.3, 0.4}, {0.5, 0.2, 0.4, 0.3}};
    double total_space2 = 5.0;
    std::vector<double> result2 =
        OptimizeWarehouseLayout(num_sections2, space_requirements2, adjacency_benefits2, total_space2);
    assert(result2.size() == 4);
    // TEST_END

    // TEST
    int num_sections3 = 2;
    std::vector<double> space_requirements3 = {1.0, 1.5};
    std::vector<std::vector<double>> adjacency_benefits3 = {{0.4, 0.2}, {0.2, 0.4}};
    double total_space3 = 2.5;
    std::vector<double> result3 =
        OptimizeWarehouseLayout(num_sections3, space_requirements3, adjacency_benefits3, total_space3);
    assert(result3.size() == 2);
    // TEST_END

    // TEST
    int num_sections4 = 5;
    std::vector<double> space_requirements4 = {1.0, 1.2, 1.4, 1.6, 1.8};
    std::vector<std::vector<double>> adjacency_benefits4 = {{0.3, 0.4, 0.5, 0.6, 0.7},
                                                            {0.4, 0.3, 0.6, 0.5, 0.8},
                                                            {0.5, 0.6, 0.3, 0.4, 0.9},
                                                            {0.6, 0.5, 0.4, 0.3, 1.0},
                                                            {0.7, 0.8, 0.9, 1.0, 0.3}};
    double total_space4 = 6.0;
    std::vector<double> result4 =
        OptimizeWarehouseLayout(num_sections4, space_requirements4, adjacency_benefits4, total_space4);
    assert(result4.size() == 5);
    // TEST_END

    // TEST
    int num_sections5 = 3;
    std::vector<double> space_requirements5 = {1.5, 1.0, 1.8};
    std::vector<std::vector<double>> adjacency_benefits5 = {{0.4, 0.3, 0.5}, {0.3, 0.4, 0.2}, {0.5, 0.2, 0.4}};
    double total_space5 = 4.0;
    std::vector<double> result5 =
        OptimizeWarehouseLayout(num_sections5, space_requirements5, adjacency_benefits5, total_space5);
    assert(result5.size() == 3);
    // TEST_END

    // Invalid input tests
    try {
        OptimizeWarehouseLayout(-1, space_requirements1, adjacency_benefits1, total_space1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }

    try {
        OptimizeWarehouseLayout(num_sections1, {1.0, 2.0}, adjacency_benefits1, total_space1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }

    try {
        OptimizeWarehouseLayout(num_sections1, space_requirements1, {{0.5, 0.2}, {0.2, 0.5}}, total_space1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
}
