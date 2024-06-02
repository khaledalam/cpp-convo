/***






 khaled_cpp_190_2024_June_02: fe497bbe-2e6e-4e65-bbe0-ab16b292576b

 func_MaximalRectangle_khaled_cpp_190_2024_June_02



Design a C++ function called MaximalRectangle that takes one input: a non-empty matrix of characters called matrix where
each element is either '0' or '1'. This function should return an integer representing the area of the largest rectangle
containing only '1's. Use dynamic programming to solve the problem. Please don't forget to validate the input.


*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

int MaximalRectangle(const std::vector<std::vector<char>> &matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        throw std::invalid_argument("matrix cannot be empty");
    }

    int max_area = 0;
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<int> heights(cols, 0);

    for (int rrr = 0; rrr < rows; ++rrr) {
        for (int ccc = 0; ccc < cols; ++ccc) {
            heights[ccc] = matrix[rrr][ccc] == '1' ? heights[ccc] + 1 : 0;
        }

        std::stack<int> stk;
        for (int ccc = 0; ccc <= cols; ++ccc) {
            while (!stk.empty() && (ccc == cols || heights[ccc] < heights[stk.top()])) {
                int hhh = heights[stk.top()];
                stk.pop();
                int www = stk.empty() ? ccc : ccc - stk.top() - 1;
                max_area = std::max(max_area, hhh * www);
            }
            stk.push(ccc);
        }
    }

    return max_area;
}

#include <cassert>
int main() {
    // TEST
    assert(MaximalRectangle({{'1', '0', '1', '0', '0'},
                             {'1', '0', '1', '1', '1'},
                             {'1', '1', '1', '1', '1'},
                             {'1', '0', '0', '1', '0'}}) == 6);
    // TEST_END

    // TEST
    assert(MaximalRectangle({{'0'}}) == 0);
    // TEST_END

    // TEST
    assert(MaximalRectangle({{'1'}}) == 1);
    // TEST_END

    // TEST
    try {
        MaximalRectangle({});
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
