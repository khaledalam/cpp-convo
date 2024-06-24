/***


 khaled_cpp_mil_212_2024_June_16: f9f1277c-ec2a-46e4-b37e-8c321f509acd


func_MTraceAndUniqueness_khaled_cpp_mil_212_2024_June_16

*/

/*

Design me a C++ function called MTraceAndUniqueness that takes a non-empty matrix of type
std::vector<std::vector<int>> that contains only integers between 1 and N where N is the size of each row in the matrix
and all rows should be with the same size.

We want to compute the matrix trace and check whether all elements in the matrix are unique.

This function should return 2 values t u of type std::array<int, 2> where t is the trace of the matrix, and u is 1 if
all elements are unique and 0 otherwise. Please use the lambda function in the solution and don't forget to validate the
input.



*/

// #include <algorithm>
// #include <cassert>
#include <iostream>
// #include <stdexcept>

#include <array>
#include <set>
#include <stdexcept>
#include <tuple>
#include <vector>

std::array<int, 2> MTraceAndUniqueness(const std::vector<std::vector<int>> &matrix) {
    // Validate input
    if (matrix.empty()) {
        throw std::invalid_argument("Input matrix is empty.");
    }

    int n_size = matrix.front().size();

    if (n_size == 0) {
        throw std::invalid_argument("Input matrix items can't be empty.");
    }

    if (n_size != matrix.size()) {
        throw std::invalid_argument("matrix should has rows are not equal to column size");
    }

    for (const auto &row : matrix) {
        if (row.size() != n_size) {
            throw std::invalid_argument("Matrix rows are not of equal size.");
        }
        for (int num : row) {
            if (num < 1 || num > n_size) {
                throw std::invalid_argument("Matrix elements should be between 1 and the size of each row.");
            }
        }
    }

    int trace = 0;
    std::set<int> unique_elements;

    auto IsUnique = [&]() {
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

    return {trace, IsUnique() ? 1 : 0};
}

#include <cassert>
int main() {
    // TEST
    assert(
        (MTraceAndUniqueness({{1, 2, 4, 3}, {1, 3, 4, 2}, {1, 2, 3, 1}, {1, 1, 1, 3}}) == std::array<int, 2>{10, 0}));
    // TEST_END

    // TEST
    assert((MTraceAndUniqueness({{1}}) == std::array<int, 2>{1, 1}));
    // TEST_END

    // TEST
    assert((MTraceAndUniqueness({{1, 2}, {1, 1}}) == std::array<int, 2>{2, 0}));
    // TEST_END

    // TEST
    try {
        MTraceAndUniqueness({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MTraceAndUniqueness({{2, 1, 5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MTraceAndUniqueness({{2, 1, 0}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MTraceAndUniqueness({{2, 1, -5}, {1, 3, 2}, {1, 2, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MTraceAndUniqueness({{2, 1, 3}, {1, 2}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MTraceAndUniqueness({{2, 1, 3}});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
