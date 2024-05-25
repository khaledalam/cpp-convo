/***
 * Prompt:




 khaled_cpp_125-2024_May_18: 33b57b3c-7e96-4733-bec8-04d0646db0be


func_LowestCostRoadPath_khaled_cpp_125-2024_May_18


Create a C++ function called LowestCostRoadPath that takes one non-empty array input called grid of type std::vector<int>, each item represents the cost of crossing through it and it should be zero or positive number. This function should return a number of type int that represents the minimum path sum from the top-left corner to the bottom-right corner, where you can only move right or down. Please don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int LowestCostRoadPath(const std::vector<std::vector<int>> &grid) {
    if (grid.empty()) {
        throw std::invalid_argument("grid can't be empty");
    }

    if (grid[0].empty()) {
        throw std::invalid_argument("grid's rows can't be empty");
    }

    int m_size = grid.size();
    int n_size = grid[0].size();

    for (const std::vector<int> &row : grid) {
        if (n_size != row.size()) {
            throw std::invalid_argument("rows should be with the same size");
        }
        for (const int &item : row) {
            if (item < 0) {
                throw std::invalid_argument("values should be zero or positive");
            }
        }
    }

    std::vector<std::vector<int>> dynamic(m_size, std::vector<int>(n_size, 0));

    dynamic[0][0] = grid[0][0];

    for (int idx = 1; idx < m_size; ++idx) {
        dynamic[idx][0] = dynamic[idx - 1][0] + grid[idx][0];
    }

    for (int jdx = 1; jdx < n_size; ++jdx) {
        dynamic[0][jdx] = dynamic[0][jdx - 1] + grid[0][jdx];
    }

    for (int idx = 1; idx < m_size; ++idx) {
        for (int jdx = 1; jdx < n_size; ++jdx) {
            dynamic[idx][jdx] = std::min(dynamic[idx - 1][jdx], dynamic[idx][jdx - 1]) + grid[idx][jdx];
        }
    }

    return dynamic[m_size - 1][n_size - 1];
}

#include <cassert>
int main() {
    // TEST
    assert(LowestCostRoadPath({{1, 3, 1}, {1, 9, 1}, {6, 2, 1}}) == 7);
    // TEST_END

    // TEST
    assert(LowestCostRoadPath({{1, 3}, {1, 9}}) == 11);
    // TEST_END

    // TEST
    assert(LowestCostRoadPath({{0, 3, 1}, {1, 0, 1}, {6, 2, 1}}) == 3);
    // TEST_END

    // TEST
    try {
        LowestCostRoadPath({{-1}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
    
    // TEST
    try {
        LowestCostRoadPath({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LowestCostRoadPath({{}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
