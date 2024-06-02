/***






 khaled_cpp_175_2024_June_02: 40910a43-5fb5-4a46-8e77-e41ee2a3de0e

 func_CheckSymmetry_khaled_cpp_175_2024_June_02
 



Create a C++ function called CheckSymmetry that takes a non-empty matrix matrix of type std::vector<std::vector<int>>
that contains only integers between 1 and N where N is the size of each row in the matrix and all rows should be with
the same size.

We want to check if the matrix is symmetric along its main diagonal and also determine the sum of the main diagonal
elements.

This function should return 2 values s d of type std::array<int, 2> where s is 1 if the matrix is symmetric and 0
otherwise, and d is the sum of the main diagonal elements. Please use lambda function in the solution and don't forget
to validate the input.


*/

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::array<int, 2> CheckSymmetry(std::vector<std::vector<int>> matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("matrix can't be empty");
    }

    int n_size = matrix[0].size();
    for (const auto &row : matrix) {
        if (row.size() != n_size) {
            throw std::invalid_argument("all rows should be with the same size");
        }
        for (const auto &item : row) {
            if (item < 1 || item > n_size) {
                throw std::invalid_argument("cell value should be between 1 and N");
            }
        }
    }

    auto is_symmetric = [&]() {
        for (int row = 0; row < n_size; ++row) {
            for (int col = 0; col < n_size; ++col) {
                if (matrix[row][col] != matrix[col][row]) {
                    return false;
                }
            }
        }
        return true;
    };

    int diagonal_sum = 0;
    for (int i = 0; i < n_size; ++i) {
        diagonal_sum += matrix[i][i];
    }

    return {is_symmetric() ? 1 : 0, diagonal_sum};
}

#include <cassert>
int main() {
    // TEST
    assert((CheckSymmetry({{1, 2}, {2, 1}}) == std::array<int, 2>{1, 2}));
    // TEST_END

    // TEST
    assert((CheckSymmetry({{1, 2, 3}, {2, 1, 3}, {2, 3, 1}}) == std::array<int, 2>{0, 3}));
    // TEST_END

    // TEST
    assert((CheckSymmetry({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}) == std::array<int, 2>{1, 3}));
    // TEST_END

    // TEST
    try {
        CheckSymmetry({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckSymmetry({{2, 1, 5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckSymmetry({{2, 1, 0}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckSymmetry({{2, 1, -5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckSymmetry({{2, 1, 3}, {1, 2}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
