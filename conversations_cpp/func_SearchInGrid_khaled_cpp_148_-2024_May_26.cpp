/***






 khaled_cpp_148_-2024_May_26: 1c27a115-55cd-48b8-8d5b-268d3fdfec4d

 func_SearchInGrid_khaled_cpp_148_-2024_May_26



Create a C++ function called SearchInGrid that takes 2 inputs, the first input is a non-empty 2d array called grid of type std::vector<std::vector<char>>, all its rows should be the same size and size should be greater than zero, the second input is a non-empty text called word of type std::string. This function should search a given word input in a 2D board containing letters. Note that The word can be constructed by sequentially traversing adjacent horizontal or vertical cells. In a sequence to form a word, a letter in the same position can not be used more than once. Please use the DFS algorithm in the solution and don't forget to validate the input.


 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool Dfs(std::vector<std::vector<char>> &grid, const std::string &word, int rdx, int cdx, int index) {
    if (index == word.size()) {
        return true;
    }
    int rows = grid.size();
    int cols = grid[0].size();
    if (rdx < 0 || rdx >= rows || cdx < 0 || cdx >= cols) {
        return false;
    }

    if (word[index] != grid[rdx][cdx]) {
        return false;
    }

    char cur = grid[rdx][cdx];
    grid[rdx][cdx] = '$';
    bool result = false;

    result = Dfs(grid, word, rdx - 1, cdx, index + 1) || Dfs(grid, word, rdx + 1, cdx, index + 1) ||
             Dfs(grid, word, rdx, cdx - 1, index + 1) || Dfs(grid, word, rdx, cdx + 1, index + 1);

    grid[rdx][cdx] = cur;

    return result;
}

bool SearchInGrid(std::vector<std::vector<char>> grid, const std::string word) {
    int rows = grid.size();
    if (rows < 1) {
        throw std::invalid_argument("grid can't be empty");
    }

    if (word.empty()) {
        throw std::invalid_argument("word can't be empty");
    }

    int cols = grid[0].size();

    if (!cols) {
        throw std::invalid_argument("rows length should be greater than zero");
    }

    for (auto rww : grid) {
        if (rww.size() != cols) {
            throw std::invalid_argument("all rows should be with the same size");
        }
    }

    for (int idx = 0; idx < rows; ++idx) {
        for (int jdx = 0; jdx < cols; ++jdx) {
            if (word[0] == grid[idx][jdx]) {
                if (Dfs(grid, word, idx, jdx, 0)) {
                    return true;
                }
            }
        }
    }

    return false;
}

#include <cassert>
int main() {
    // TEST
    assert(SearchInGrid({{'H', 'E', 'Y', 'A'}, {'O', 'L', 'A', 'Y'}, {'I', 'L', 'O', 'V'}}, "HELLO") == true);
    // TEST_END

    // TEST
    assert(SearchInGrid({{'H', 'E', 'Y', 'A'}, {'O', 'L', 'A', 'Y'}, {'I', 'L', 'O', 'V'}}, "HELL") == true);
    // TEST_END

    // TEST
    assert(SearchInGrid({{'H', 'E', 'Y', 'A'}, {'O', 'L', 'A', 'Y'}, {'I', 'L', 'O', 'V'}}, "HOLA") == true);
    // TEST_END

    // TEST
    assert(SearchInGrid({{'H', 'E', 'Y', 'A'}, {'O', 'L', 'A', 'Y'}, {'I', 'L', 'O', 'V'}}, "HEE") == false);
    // TEST_END

    // TEST
    assert(SearchInGrid({{'O', 'K', 'A', 'Y'}}, "OK") == true);
    // TEST_END

    // TEST
    assert(SearchInGrid({{'O', 'K', 'A', 'Y'}}, "Ok") == false);
    // TEST_END

    // TEST
    assert(SearchInGrid({{'1', '3', '@'}, {'1', '3', '@'}}, "133@") == true);
    // TEST_END

    // TEST
    try {
        SearchInGrid({}, "1");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SearchInGrid({{}}, "1");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SearchInGrid({{'1'}}, "");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}