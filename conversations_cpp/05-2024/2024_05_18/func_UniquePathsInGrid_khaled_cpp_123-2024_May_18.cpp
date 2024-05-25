/***
 * Prompt:




 khaled_cpp_123-2024_May_18: c4f61a0c-dc94-4fa3-a329-a7a72952489f

 func_UniquePathsInGrid_khaled_cpp_123-2024_May_18


Create a C++ function called UniquePathsInGrid that takes one non-empty array input called grid of type std::vector<std::vector<int>>, each item should be either 1 or 0 only. This function should return a number of type int that represents the number of unique paths in the grid. Please note that the start cell is (0,0) and if the start cell can't be with a value of 1. Also, note that a 0 value allows to be in the path and a 1 value is not allowed to be in the path(obstacle), all rows should be the same size and each path should end at (grid.size() - 1, grid[0].size() - 1). Please don't forget to validate the input.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int UniquePathsInGrid(const std::vector<std::vector<int>> &grid) {
    if (grid.empty()) {
        throw std::invalid_argument("grid can't be empty");
    }

    if (grid[0][0] == 1) {
        throw std::invalid_argument("first cell can't be 1");
    }

    int m_size = grid.size();
    int n_size = grid[0].size();

    if (grid[m_size - 1][n_size - 1] == 1) {
        throw std::invalid_argument("last cell can't be 1");
    }

    for (const std::vector<int> &row : grid) {
        if (n_size != row.size()) {
            throw std::invalid_argument("rows should be with the same size");
        }
    }

    std::vector<std::vector<int>> dynamic(m_size, std::vector<int>(n_size, 0));

    dynamic[0][0] = 1;

    for (int idx = 1; idx < m_size; ++idx) {
        dynamic[idx][0] = (grid[idx][0] == 0 && dynamic[idx - 1][0] == 1) ? 1 : 0;
    }

    for (int jdx = 1; jdx < n_size; ++jdx) {
        dynamic[0][jdx] = (grid[0][jdx] == 0 && dynamic[0][jdx - 1] == 1) ? 1 : 0;
    }

    for (int idx = 1; idx < m_size; ++idx) {
        for (int jdx = 1; jdx < n_size; ++jdx) {
            if (grid[idx][jdx] == 0) {
                dynamic[idx][jdx] = dynamic[idx - 1][jdx] + dynamic[idx][jdx - 1];
            }
        }
    }

    return dynamic[m_size - 1][n_size - 1];
}

#include <cassert>
int main() {
    // TEST
    assert(UniquePathsInGrid({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}) == 2);
    // TEST_END

    // TEST
    assert(UniquePathsInGrid({{0, 0}, {0, 0}}) == 2);
    // TEST_END

    // TEST
    assert(UniquePathsInGrid({{0}}) == 1);
    // TEST_END

    // TEST
    assert(UniquePathsInGrid({{0, 1}, {0, 0}}) == 1);
    // TEST_END

    // TEST
    try {
        UniquePathsInGrid({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        UniquePathsInGrid({{0, 0}, {0, 1}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        UniquePathsInGrid({{1, 3}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        UniquePathsInGrid({{1}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        UniquePathsInGrid({{0}, {0, 1}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
