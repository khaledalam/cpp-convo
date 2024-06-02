/***






 khaled_cpp_173_2024_June_02: 1338f2c6-0672-4fd6-87dd-9cf6177ec17e

 func_LongestFreePath_khaled_cpp_173_2024_June_02



Create a C++ function called LongestFreePath that takes a non-empty array called grid of type std::vector<std::string>,
all rows are with the same length and each cell should be either '1' or '0'. 0 stands for a free square meter of the
office room. 1 stands for an occupied square meter.

We want to find the longest path of free square meters in the grid, starting from the top-left corner to the
bottom-right corner. A path can only move right or down.

For example, if a grid is like this:

0000
0010
0000

the maximum possible path length is 6.

This function should return a number of type int that represents the length of the longest free path in the grid. Note
that is there is no path return 0. Please don't forget to validate the input.


*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int LongestFreePath(std::vector<std::string> grid) {
    int row_count = grid.size();
    if (row_count < 1) {
        throw std::invalid_argument("grid cannot be empty");
    }

    int col_count = grid[0].size();
    for (const auto &row : grid) {
        if (row.size() != col_count) {
            throw std::invalid_argument("all rows should be with the same size");
        }

        for (const char &cell : row) {
            if (cell != '0' && cell != '1') {
                throw std::invalid_argument("cell should be '0' or '1'");
            }
        }
    }

    std::vector<std::vector<int>> dyn(row_count, std::vector<int>(col_count, 0));
    dyn[0][0] = (grid[0][0] == '0') ? 1 : 0;

    for (int row = 0; row < row_count; ++row) {
        for (int col = 0; col < col_count; ++col) {
            if (grid[row][col] == '0') {
                if (row > 0 && dyn[row - 1][col] > 0) {
                    dyn[row][col] = std::max(dyn[row][col], dyn[row - 1][col] + 1);
                }
                if (col > 0 && dyn[row][col - 1] > 0) {
                    dyn[row][col] = std::max(dyn[row][col], dyn[row][col - 1] + 1);
                }
            }
        }
    }

    return dyn[row_count - 1][col_count - 1];
}

#include <cassert>
int main() {
    // TEST
    assert(LongestFreePath({"0000", "0010", "0000"}) == 6);
    // TEST_END

    // TEST
    assert(LongestFreePath({"0000", "1011", "0000"}) == 6);
    // TEST_END

    // TEST
    assert(LongestFreePath({"1110", "0000", "0000", "0000", "0000"}) == 0);
    // TEST_END

    // TEST
    assert(LongestFreePath({"000", "110", "000"}) == 5);
    // TEST_END

    // TEST
    assert(LongestFreePath({"00", "10", "11", "00"}) == 0);
    // TEST_END

    // TEST
    try {
        LongestFreePath({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LongestFreePath({"a3"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LongestFreePath({"0101", "10"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
