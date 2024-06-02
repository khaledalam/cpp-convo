/***






 khaled_cpp_171_2024_June_02: 046c73e7-adca-457e-842f-df756247627f

 func_MaxPerimeterRectangle_khaled_cpp_171_2024_June_02



Create a C++ function called MaxPerimeterRectangle that takes a non-empty array called grid of type
std::vector<std::string>, all rows are with the same length and each cell should be either '1' or '0'. 0 stands for a
free square meter of the office room. 1 stands for an occupied square meter.

We want to find the largest rectangular area of free square meters in the grid with the maximum possible perimeter.

For example, if a grid is like this:
0000
0010
0000

the maximum possible perimeter is 10 (3x2 rectangle).

This function should return a number of type int that represents the maximum possible perimeter of a free rectangle in
the grid. Please don't forget to validate the input.



*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int MaxPerimeterRectangle(std::vector<std::string> grid) {
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

    int max_perimeter = 0;

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
                        int perimeter = 2 * (width + height);
                        max_perimeter = std::max(max_perimeter, perimeter);
                    }
                }
            }
        }
    }

    return max_perimeter;
}

#include <cassert>
int main() {
    // TEST
    assert(MaxPerimeterRectangle({"0000", "0010", "0000"}) == 10);
    // TEST_END

    // TEST
    assert(MaxPerimeterRectangle({"0000", "0000", "0000"}) == 14);
    // TEST_END

    // TEST
    assert(MaxPerimeterRectangle({"1110", "0000", "0000", "0000", "0000"}) == 16);
    // TEST_END

    // TEST
    assert(MaxPerimeterRectangle({"000", "110", "000"}) == 8);
    // TEST_END

    // TEST
    assert(MaxPerimeterRectangle({"00", "10", "11", "00"}) == 6);
    // TEST_END

    // TEST
    try {
        MaxPerimeterRectangle({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxPerimeterRectangle({"a3"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MaxPerimeterRectangle({"0101", "10"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
