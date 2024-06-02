/***






 khaled_cpp_176_2024_June_02: 0a0c2b6e-9341-429e-a740-235cf1778f2e

 func_MatrixTraceAndUniqueness_khaled_cpp_176_2024_June_02




Design me a C++ function called MatrixTraceAndUniqueness that takes a non-empty matrix matrix of type
std::vector<std::vector<int>> that contains only integers between 1 and N where N is the size of each row in the matrix
and all rows should be with the same size.

We want to compute the matrix trace and check whether all elements in the matrix are unique.

This function should return 2 values t u of type std::array<int, 2> where t is the trace of the matrix, and u is 1 if
all elements are unique and 0 otherwise. Please use lambda function in the solution and don't forget to validate the
input.


*/

#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

std::array<int, 2> MatrixTraceAndUniqueness(std::vector<std::vector<int>> matrix) {
    if (matrix.empty()) {
        throw std::invalid_argument("matrix can't be empty");
    }

    int n_size = matrix[0].size();
    if (matrix.size() != n_size) {
        throw std::invalid_argument("matrix should has rows are not equal to column size");
    }

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

    int trace = 0;
    std::set<int> unique_elements;

    auto is_unique = [&]() {
        for (const auto &row : matrix) {
            for (const auto &item : row) {
                if (!unique_elements.insert(item).second) {
                    return false;
                }
            }
        }
        return true;
    };

    for (int iii = 0; iii < n_size; ++iii) {
        trace += matrix[iii][iii];
    }

    return {trace, is_unique() ? 1 : 0};
}

#include <cassert>
int main() {
    // TEST
    assert((MatrixTraceAndUniqueness({{1, 2, 4, 3}, {1, 3, 4, 2}, {1, 2, 3, 1}, {1, 1, 1, 3}}) ==
            std::array<int, 2>{10, 0}));
    // TEST_END

    // TEST
    assert((MatrixTraceAndUniqueness({{1}}) == std::array<int, 2>{1, 1}));
    // TEST_END

    // TEST
    assert((MatrixTraceAndUniqueness({{1, 2}, {1, 1}}) == std::array<int, 2>{2, 0}));
    // TEST_END

    // TEST
    try {
        MatrixTraceAndUniqueness({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MatrixTraceAndUniqueness({{2, 1, 5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MatrixTraceAndUniqueness({{2, 1, 0}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MatrixTraceAndUniqueness({{2, 1, -5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MatrixTraceAndUniqueness({{2, 1, 3}, {1, 2}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MatrixTraceAndUniqueness({{2, 1, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
