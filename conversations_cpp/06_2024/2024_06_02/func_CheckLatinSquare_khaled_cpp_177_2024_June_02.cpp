/***






 khaled_cpp_177_2024_June_02: 5e0b2f21-2499-40e2-8e41-82afaefce139

func_CheckLatinSquare_khaled_cpp_177_2024_June_02


Create me a C++ function called CheckLatinSquare that takes a non-empty matrix matrix of type
std::vector<std::vector<int>> that contains only integers between 1 and N where N is the size of each row in the matrix
and all rows should be with the same size.

We want to check if the matrix is a Latin square and also determine the trace of the matrix.

This function should return 2 values l t of type std::array<int, 2> where l is 1 if the matrix is a Latin square and 0
otherwise, and t is the trace of the matrix. Please use lambda function in the solution and don't forget to validate the
input.


*/

#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

std::array<int, 2> CheckLatinSquare(std::vector<std::vector<int>> matrix) {
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
    bool is_latin = true;

    auto CheckUnique = [&](const std::vector<int> &vec) {
        std::set<int> s(vec.begin(), vec.end());
        return s.size() == vec.size();
    };

    for (int i = 0; i < n_size; ++i) {
        trace += matrix[i][i];
        if (!CheckUnique(matrix[i])) {
            is_latin = false;
        }
        std::vector<int> column(n_size);
        for (int j = 0; j < n_size; ++j) {
            column[j] = matrix[j][i];
        }
        if (!CheckUnique(column)) {
            is_latin = false;
        }
    }

    return {is_latin ? 1 : 0, trace};
}

#include <cassert>
int main() {
    // TEST
    assert((CheckLatinSquare({{1, 2, 3}, {2, 3, 1}, {3, 1, 2}}) == std::array<int, 2>{1, 6}));
    // TEST_END

    // TEST
    assert((CheckLatinSquare({{1, 2, 3}, {2, 3, 1}, {3, 1, 3}}) == std::array<int, 2>{0, 7}));
    // TEST_END

    // TEST
    assert((CheckLatinSquare({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}}) == std::array<int, 2>{0, 3}));
    // TEST_END

    // TEST
    try {
        CheckLatinSquare({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckLatinSquare({{2, 1, 5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckLatinSquare({{2, 1, 0}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckLatinSquare({{2, 1, -5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CheckLatinSquare({{2, 1, 3}, {1, 2}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
