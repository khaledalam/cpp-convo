/***






 khaled_cpp_163_2024_May_27: a2825fe3-5986-4042-a1c8-8a82c8b8bfe6

 func_FitTable_khaled_cpp_163_2024_May_27



Design a C++ function called FitTable that takes a non-empty array called grid of type std::vector<std::string>, all rows
are with the same length and each cell should be either '1' or '0', 0 stands for a free square meter of the office room.
1 stands for an occupied square meter.


Our office room is a rectangular room n × m meters. Each square meter of the room is either occupied by some furniture,
or free. A bargaining table is rectangular and should be placed so, that its sides are parallel to the office walls. We
want to change or rearrange anything, that's why all the squares that will be occupied by the table should be initially
free. We want the new table to sit as many people as possible, thus its perimeter should be maximal.

for example if a grid is like this:
000
010
000

the maximum possible perimeter is 8

This function should return a number of type int that represent the maximum possible perimeter of a bargaining table for
his office. Please don't forget to validate the input.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int FitTable(std::vector<std::string> grid) {
    int nnn = grid.size(); 
    if (nnn < 1) {
        throw std::invalid_argument("grid cannot be empty");
    }

    int mmm = grid[0].size();
    for (auto row : grid) {
        if (row.size() != mmm) {
            throw std::invalid_argument("all rows should be with the same size");
        }

        for (const char &character : row) {
            if (character != '0' && character != '1') {
                throw std::invalid_argument("character should be '0' or '1'");
            }
        }
    }

    int ans = 0;

    for (int start_row = 0; start_row < nnn; ++start_row) {
        for (int start_col = 0; start_col < mmm; ++start_col) {
            if (grid[start_row][start_col] == '1')
                continue;

            for (int end_row = start_row; end_row < nnn; ++end_row) {
                for (int end_col = start_col; end_col < mmm; ++end_col) {
                    bool valid = true;

                    for (int idx = start_row; idx <= end_row && valid; ++idx) {
                        for (int jdx = start_col; jdx <= end_col; ++jdx) {
                            if (grid[idx][jdx] == '1') {
                                valid = false;
                                break;
                            }
                        }
                    }

                    if (valid) {
                        int width = end_col - start_col + 1;
                        int height = end_row - start_row + 1;
                        int per = 2 * (width + height);
                        ans = std::max(ans, per);
                    }
                }
            }
        }
    }

    return ans;
}

#include <cassert>
int main() {
    // TEST
    assert(FitTable({"000", "010", "000"}) == 8);
    // TEST_END

    // TEST
    assert(FitTable({"1100", "0000", "0000", "0000", "0000"}) == 16);
    // TEST_END

    // TEST
    assert(FitTable({"000", "110", "000"}) == 8);
    // TEST_END

    // TEST
    assert(FitTable({"00", "10", "11", "00"}) == 6);
    // TEST_END

    // TEST
    try {
        FitTable({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FitTable({"a3"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        FitTable({"0101", "10"});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}