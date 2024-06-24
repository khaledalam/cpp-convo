/***


 khaled_cpp_mil_226_2024_June_16: 2df0f32e-0247-494c-b7bd-c6331926b845
 

func_LargestWhiteSquare_khaled_cpp_mil_226_2024_June_16



*/

/*


Design me a C++ function called LargestWhiteSquare that takes a non-empty array called grid of type
std::vector<std::string>, all rows are with the same length and each cell should be either '1' or '0'. 0 stands for a
white square meter of the office room. 1 stands for an occupied square meter.

We want to find the largest square of white square meters in the grid.

For example, if a grid is like this:

0110
1110
0110
0000

the maximum possible square has side length 1 (1x1 square).

This function should return a number of type int that represents the maximum side length of the largest white square in
the grid. Please use dynamic programming in the solution.





*/


#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int LargestWhiteSquare(std::vector<std::string> grid) {
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

    return max_side;
}

#include <cassert>
int main() {
    // TEST
    assert(LargestWhiteSquare({"0110", "1110", "0110", "0000"}) == 1);
    // TEST_END

    // TEST
    assert(LargestWhiteSquare({"1110", "0000", "0000", "0000", "0000"}) == 4);
    // TEST_END

    // TEST
    assert(LargestWhiteSquare({"000", "110", "000"}) == 1);
    // TEST_END

    // TEST
    assert(LargestWhiteSquare({"00", "10", "11", "00"}) == 1);
    // TEST_END

    // TEST
    assert(LargestWhiteSquare({"00", "00", "11", "00"}) == 2);
    // TEST_END

    // TEST
    try {
        LargestWhiteSquare({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LargestWhiteSquare({"a3"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LargestWhiteSquare({"0101", "10"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
