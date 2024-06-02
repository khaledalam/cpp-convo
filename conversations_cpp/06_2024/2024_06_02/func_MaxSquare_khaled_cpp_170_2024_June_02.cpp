/***






 khaled_cpp_170_2024_June_02: c044ad58-1114-432c-9b48-a59b68e0518e

 func_MaxSquare_khaled_cpp_170_2024_June_02


Design me a C++ function called MaxSquare that takes a non-empty array called grid of type std::vector<std::string>, all
rows are with the same length and each cell should be either '1' or '0'. 0 stands for a free square meter of the office
room. 1 stands for an occupied square meter.

We want to find the largest square area of free square meters in the grid.

For example, if a grid is like this:
0010
0110
1110
the maximum possible area is 1 (1x1 square).

This function should return a number of type int that represents the maximum possible area of a free square in the grid.
Please don't forget to validate the input.



*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int MaxSquare(std::vector<std::string> grid) {
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
    int max_side = 0;

    for (int row = 0; row < row_count; ++row) {
        for (int col = 0; col < col_count; ++col) {
            if (grid[row][col] == '0') {
                if (row == 0 || col == 0) {
                    dyn[row][col] = 1;
                } else {
                    dyn[row][col] = std::min({dyn[row - 1][col], dyn[row][col - 1], dyn[row - 1][col - 1]}) + 1;
                }
                max_side = std::max(max_side, dyn[row][col]);
            }
        }
    }

    return max_side * max_side;
}

#include <cassert>
int main() {
    // TEST
    assert(MaxSquare({"0010", "0110", "1110"}) == 1);
    // TEST_END

    // TEST
    assert(MaxSquare({"000", "110", "000"}) == 1);
    // TEST_END

    // TEST
    assert(MaxSquare({"1110", "0000", "0000", "0000", "0000"}) == 16);
    // TEST_END

    // TEST
    assert(MaxSquare({"00", "10", "11", "00"}) == 1);
    // TEST_END

    // TEST
    try {
        MaxSquare({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxSquare({"a3"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxSquare({"0101", "10"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
