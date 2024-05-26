/***






 khaled_cpp_149_-2024_May_26: 77db162f-4b3c-4687-bbd9-4ce14959bd3d

func_IslandsCount_khaled_cpp_149_-2024_May_26

Create a C++ function called IslandsCount that takes a non-empty 2d array called grid of type std::vector<std::vector<int>>, all its rows should be the same size and size should be greater than zero and each cell should be zero or one, 1 represents land and 0 represents. This function should return a number of type int which represents the count number of islands. Note that an island is surrounded by connecting neighboring lands vertically or horizontally. Assume that everything around the grid is water. Please use the DFS algorithm in the solution and don't forget to validate the input.


 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void Dfs(std::vector<std::vector<int>> &grid, int idx, int jdx) {
    int m_size = grid.size();
    int n_size = grid[0].size();

    if (idx < 0 || idx >= m_size || jdx < 0 || jdx >= n_size) {
        return;
    }

    grid[idx][jdx] = 0;

    if (idx + 1 < m_size && grid[idx + 1][jdx] == 1) {
        Dfs(grid, idx + 1, jdx);
    }

    if (idx - 1 >= 0 && grid[idx - 1][jdx] == 1) {
        Dfs(grid, idx - 1, jdx);
    }

    if (jdx + 1 < n_size && grid[idx][jdx + 1] == 1) {
        Dfs(grid, idx, jdx + 1);
    }

    if (jdx - 1 >= 0 && grid[idx][jdx - 1] == 1) {
        Dfs(grid, idx, jdx - 1);
    }
}

int IslandsCount(std::vector<std::vector<int>> grid) {
    int m_size = grid.size();

    if (m_size == 0) {
        throw std::invalid_argument("grid can't be empty");
    }

    int n_size = grid[0].size();

    if (!n_size) {
        throw std::invalid_argument("rows length should be greater than zero");
    }

    for (auto rww : grid) {
        if (rww.size() != n_size) {
            throw std::invalid_argument("all rows should be with the same size");
        }

        for (auto cell : rww) {
            if (cell != 0 && cell != 1) {
                throw std::invalid_argument("cell should be zero or one");
            }
        }
    }

    int total_islands = 0;

    for (int idx = 0; idx < m_size; ++idx) {
        for (int jdx = 0; jdx < n_size; ++jdx) {
            if (grid[idx][jdx] == 1) {
                ++total_islands;
                Dfs(grid, idx, jdx);
            }
        }
    }

    return total_islands;
}

#include <cassert>
int main() {
    // TEST
    assert(IslandsCount({{1, 1, 0, 0, 0}, {1, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}}) == 3);
    // TEST_END

    // TEST
    assert(IslandsCount({{1, 1, 0, 0, 0}, {1, 1, 1, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 1}}) == 2);
    // TEST_END

    // TEST
    assert(IslandsCount({{1, 1, 0, 0, 0}, {1, 1, 1, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 1, 1}}) == 1);
    // TEST_END

    // TEST
    assert(IslandsCount({{1, 0}, {0, 1}}) == 2);
    // TEST_END

    // TEST
    assert(IslandsCount({{0, 0}, {0, 1}}) == 1);
    // TEST_END

    // TEST
    assert(IslandsCount({{0, 0}, {0, 0}}) == 0);
    // TEST_END

    // TEST
    try {
        IslandsCount({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IslandsCount({{}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IslandsCount({{1}, {0, 1}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}