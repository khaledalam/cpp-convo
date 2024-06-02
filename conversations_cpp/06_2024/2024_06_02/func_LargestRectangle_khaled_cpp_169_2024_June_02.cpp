/***






 khaled_cpp_169_2024_June_02: 759438f2-10fa-4d8c-b411-82412556ea86

 func_LargestRectangle_khaled_cpp_169_2024_June_02


Design a C++ function called LargestRectangle that takes a non-empty array called grid of type std::vector<std::string>,
all rows are with the same length and each cell should be either '1' or '0'. 0 stands for a free square meter of the
office room. 1 stands for an occupied square meter.

We want to find the largest rectangular area of free square meters in the grid.

For example, if a grid is like this:
0000
0010
0000

the maximum possible area is 6 (3x2 rectangle).

This function should return a number of type int that represents the maximum possible area of a free rectangle in the
grid. Please don't forget to validate the input.



*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int LargestRectangle(std::vector<std::string> grid) {
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

    int max_area = 0;

    for (int start_row = 0; start_row < row_count; ++start_row) {
        for (int start_col = 0; start_col < col_count; ++start_col) {
            if (grid[start_row][start_col] == '1')
                continue;

            for (int end_row = start_row; end_row < row_count; ++end_row) {
                for (int end_col = start_col; end_col < col_count; ++end_col) {
                    bool valid = true;

                    for (int row = start_row; row <= end_row && valid; ++row) {
                        for (int col = start_col; col <= end_col; ++col) {
                            if (grid[row][col] == '1') {
                                valid = false;
                                break;
                            }
                        }
                    }

                    if (valid) {
                        int width = end_col - start_col + 1;
                        int height = end_row - start_row + 1;
                        int area = width * height;
                        max_area = std::max(max_area, area);
                    }
                }
            }
        }
    }

    return max_area;
}

#include <cassert>
int main() {
    // TEST
    assert(LargestRectangle({"0000", "0010", "0000"}) == 6);
    // TEST_END

    // TEST
    assert(LargestRectangle({"1110", "0000", "0000", "0000", "0000"}) == 16);
    // TEST_END

    // TEST
    assert(LargestRectangle({"000", "110", "000"}) == 3);
    // TEST_END

    // TEST
    assert(LargestRectangle({"00", "10", "11", "00"}) == 2);
    // TEST_END

    // TEST
    try {
        LargestRectangle({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LargestRectangle({"a3"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        LargestRectangle({"0101", "10"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}