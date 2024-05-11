/***
 * Prompt:




 khaled_cpp_89-2024_May_09: e81c2d65-91bb-4143-a7d4-d064c6c98515

 func_KthSmallestNumberInMatrix_khaled_cpp_89-2024_May_09

 Create me a C++ function called KthSmallestNumberInMatrix which accepts two inputs, the first input non-empty list called matrix of type
 std::vector<std::vector<int>> all its rows are the same length and each row can't be empty, and the second input called k_value of type int
 which its value should be greater than 0 and less than or equal to the count of items in the matrix. Please make this function return
 another number of type int, this number should be the kth smallest value that we need from the matrix. Also please note that the matrix can
 contain negative, zero, and positive numbers. Use std::priority_queue in the solution.



 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

int KthSmallestNumberInMatrix(const std::vector<std::vector<int>> &matrix, int k_value) {
    if (matrix.empty()) {
        throw std::invalid_argument("matrix can't be empty");
    }

    if (matrix[0].empty()) {
        throw std::invalid_argument("matrix can't be empty");
    }

    int first_row_length = matrix[0].size();

    for (const std::vector<int> &row : matrix) {
        if (row.size() != first_row_length) {
            throw std::invalid_argument("matrix rows are not the same length");
        }
    }

    if (k_value < 1 || k_value > matrix.size() * matrix[0].size()) {
        throw std::invalid_argument("k_value should be grater than zero and less than or equal to the count of items in the matrix");
    }

    size_t matrix_size = matrix.size();
    std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
    for (size_t idx = 0; idx < matrix_size; idx++) {
        for (size_t jdx = 0; jdx < matrix[idx].size(); jdx++) {
            min_heap.push(matrix[idx][jdx]);
        }
    }
    while (k_value-- > 1) {
        min_heap.pop();
    }

    return min_heap.top();
}

#include <cassert>
int main() {
    // TEST
    std::vector<std::vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    assert(KthSmallestNumberInMatrix(matrix, 8) == 13);
    // TEST_END

    // TEST
    matrix = {{1, 2}, {1, 3}};
    assert(KthSmallestNumberInMatrix(matrix, 2) == 1);
    // TEST_END

    // TEST
    matrix = {{-5}};
    assert(KthSmallestNumberInMatrix(matrix, 1) == -5);
    // TEST_END

    // TEST
    matrix = {{1, 3}};
    assert(KthSmallestNumberInMatrix(matrix, 2) == 3);
    // TEST_END

    // TEST
    try {
        matrix = {};
        KthSmallestNumberInMatrix(matrix, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        matrix = {{}};
        KthSmallestNumberInMatrix(matrix, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        matrix = {{1}};
        KthSmallestNumberInMatrix(matrix, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        matrix = {{1}};
        KthSmallestNumberInMatrix(matrix, -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        matrix = {{1}};
        KthSmallestNumberInMatrix(matrix, 2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
