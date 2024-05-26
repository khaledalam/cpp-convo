/***






 khaled_cpp_154_2024_May_26: aeaa2aff-02f2-4175-aa89-9773da645b60

 func_Vester_khaled_cpp_154_2024_May_26





Create a C++ function called Vester that takes a non-empty matrix maze of type std::vector<std::vector<int>> that
contains only integers between 1 and N where N is the size of each row in the matrix and all rows should be with the
same size.

The trace of a square matrix is the sum of the values on the main diagonal (which runs from the upper left to the lower
right).

An N-by-N square matrix is a Latin square if each cell contains one of N different values, and no value is repeated
within a row or a column. Consider we will deal only with "natural Latin squares" in which the N values are the integers
between 1 and N.

We want to compute the matrix trace and check whether it is a natural Latin square. To give some additional information,
instead of simply telling us whether the matrix is a natural Latin square or not, please compute the number of rows and
the number of columns that contain repeated values.

This function should return 3 values k r c of type std::array<int, 3> where x is the test case number (starting from 1),
k is the trace of the matrix, r is the number of rows of the matrix that contain repeated elements, and c is the number
of columns of the matrix that contain repeated elements. Please use lambda function in the solution and don't forget to validate the input.





*/

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::array<int, 3> Vester(std::vector<std::vector<int>> maze) {
    if (maze.empty()) {
        throw std::invalid_argument("maze can't be empty");
    }

    int n_size = maze[0].size();

    for (auto row : maze) {
        if (row.size() != n_size) {
            throw std::invalid_argument("all rows should be with the same size");
        }
        for (auto item : row) {
            if (item < 1 || item > n_size) {
                throw std::invalid_argument("cell value should be between 1 and N");
            }
        }
    }

    auto repeat = [&](const int &vna, std::vector<int> &lna) {
        auto iter = std::find(lna.begin(), lna.end(), vna);
        if (iter != lna.end()) {
            return true;
        }

        lna.push_back(vna);

        return false;
    };

    std::array<int, 3> result = {0, 0, 0};

    for (int jdx = 0; jdx < maze.size(); jdx++) {
        std::vector<int> rcc, rrr;

        result[0] += maze[jdx][jdx];

        bool brcol = false, brrow = false;
        for (int idx = 0; idx < maze.size(); idx++) {
            if (!brcol) {
                brcol = repeat(maze[idx][jdx], rcc);
            }
            if (!brrow) {
                brrow = repeat(maze[jdx][idx], rrr);
            }
        }
        result[1] += brrow ? 1 : 0;
        result[2] += brcol ? 1 : 0;
    }
    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((Vester({{1, 2, 3, 4}, {2, 1, 4, 3}, {3, 4, 1, 2}, {4, 3, 2, 1}}) == std::array<int, 3>{4, 0, 0}));
    // TEST_END

    // TEST
    assert((Vester({{2, 2, 2, 2}, {2, 3, 2, 3}, {2, 2, 2, 3}, {2, 2, 2, 2}}) == std::array<int, 3>{9, 4, 4}));
    // TEST_END

    // TEST
    assert((Vester({{2, 1, 3}, {1, 3, 2}, {1, 2, 3}}) == std::array<int, 3>{8, 0, 2}));
    // TEST_END

    // TEST
    try {
        Vester({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Vester({{2, 1, 5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Vester({{2, 1, 0}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Vester({{2, 1, -5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Vester({{2, 1, 3}, {1, 2}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}