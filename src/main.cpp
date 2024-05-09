/***
 * Prompt:




 khaled_cpp_88-2024_May_09: 01c5efc6-632d-445f-a722-c6feab3c9e96

func_MakeIsogram_khaled_cpp_88-2024_May_09

 Create a C++ function called MakeIsogram which accepts non-empty input called
 text of type std:string, this input can be any character. Please make this
 function return another isogram string of type std::string. Please note that an
 isogram string is a string that does not contain any duplicated characters, if
 you have some duplicated characters, leave the first character of them and
 remove the others.


 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include <queue>
#include <vector>

struct Cell {
    int value;
    size_t row, col;
    Cell(int value, size_t row, size_t col)
        : value(value), row(row), col(col) {}
    bool operator>(const Cell &another) const { return value > another.value; }
};

int KthSmallestInMatrix(const std::vector<std::vector<int>> &matrix,
                        int k_value) {
    size_t matrix_size = matrix.size();
    std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> min_heap;
    for (size_t idx = 0; idx < matrix_size; idx++) {
        min_heap.push(Cell(matrix[idx][0], idx, 0));
    }
    while (k_value > 1) {
        Cell cell = min_heap.top();
        min_heap.pop();
        if (cell.col < matrix_size - 1) {
            min_heap.push(
                Cell(matrix[cell.row][cell.col + 1], cell.row, cell.col + 1));
        }
        k_value--;
    }

    return min_heap.top().value;
}

#include <cassert>
int main() {
    // TEST
    std::vector<std::vector<int>> matrix = {
        {1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    assert(KthSmallestInMatrix(matrix, 8) == 13);
    // TEST_END

    // TEST
    matrix = {{1, 2}, {1, 3}};
    assert(KthSmallestInMatrix(matrix, 2) == 1);
    // TEST_END

    // TEST
    matrix = {{-5}};
    assert(KthSmallestInMatrix(matrix, 1) == -5);
    // TEST_END

    // // TEST
    // try {
    //     MakeIsogram("");
    //     assert(false);
    // } catch (const std::exception &e) {
    //     assert(true);
    // }
    // // TEST_END
}
