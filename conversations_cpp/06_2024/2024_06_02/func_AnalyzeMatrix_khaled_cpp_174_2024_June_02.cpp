/***






 khaled_cpp_174_2024_June_02: 23f2e015-170b-4c53-92ac-b14a27387722

 func_AnalyzeMatrix_khaled_cpp_174_2024_June_02



Create a C++ function called AnalyzeMatrix that takes a non-empty matrix matrix of type std::vector<std::vector<int>>
that contains only integers between 1 and M where M is the size of each row in the matrix and all rows should be with
the same size.

The determinant of a square matrix is a special number that can be calculated from its elements. We will not actually
calculate the determinant, but we will consider a matrix as determinant-special if the sum of its elements is even.

Additionally, we want to check how many rows and columns contain at least one element that is an even number.

This function should return 3 values d r c of type std::array<int, 3> where d is 1 if the matrix is determinant-special
and 0 otherwise, r is the number of rows containing at least one even element, and c is the number of columns containing
at least one even element. Please use lambda function in the solution and don't forget to validate the input.


*/

#include <algorithm>
#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>

std::array<int, 3> AnalyzeMatrix(std::vector<std::vector<int>> matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("matrix can't be empty");
    }

    int m_size = matrix[0].size();
    for (auto row : matrix) {
        if (row.size() != m_size) {
            throw std::invalid_argument("all rows should be with the same size");
        }
        for (auto item : row) {
            if (item < 1 || item > m_size) {
                throw std::invalid_argument("cell value should be between 1 and M");
            }
        }
    }

    auto is_even = [](int x) { return x % 2 == 0; };

    int sum = 0;
    int even_rows = 0;
    int even_columns = 0;

    for (const auto &row : matrix) {
        sum += std::accumulate(row.begin(), row.end(), 0);
    }

    for (int row_idx = 0; row_idx < matrix.size(); ++row_idx) {
        bool row_has_even = std::any_of(matrix[row_idx].begin(), matrix[row_idx].end(), is_even);
        if (row_has_even) {
            ++even_rows;
        }
    }

    for (int col_idx = 0; col_idx < m_size; ++col_idx) {
        bool col_has_even = false;
        for (int row_idx = 0; row_idx < matrix.size(); ++row_idx) {
            if (is_even(matrix[row_idx][col_idx])) {
                col_has_even = true;
                break;
            }
        }
        if (col_has_even) {
            ++even_columns;
        }
    }

    return {sum % 2 == 0 ? 1 : 0, even_rows, even_columns};
}

#include <cassert>
int main() {
    // TEST
    assert((AnalyzeMatrix({{1, 2, 3, 4}, {2, 1, 4, 3}, {3, 4, 1, 2}, {4, 3, 2, 1}}) == std::array<int, 3>{1, 4, 4}));
    // TEST_END

    // TEST
    assert((AnalyzeMatrix({{2, 2, 2, 2}, {2, 3, 2, 3}, {2, 2, 2, 3}, {2, 2, 2, 2}}) == std::array<int, 3>{0, 4, 4}));
    // TEST_END

    // TEST
    assert((AnalyzeMatrix({{2, 1, 3}, {1, 3, 2}, {1, 2, 3}}) == std::array<int, 3>{1, 3, 3}));
    // TEST_END

    // TEST
    try {
        AnalyzeMatrix({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AnalyzeMatrix({{2, 1, 5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AnalyzeMatrix({{2, 1, 0}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AnalyzeMatrix({{2, 1, -5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AnalyzeMatrix({{2, 1, 3}, {1, 2}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
