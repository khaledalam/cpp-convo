/***
 * Prompt:




 khaled_cpp_139-2024_May_23: 8ae4a435-c179-4204-b0f2-1d3f99598aaa

 func_IsAllow_khaled_cpp_139-2024_May_23


Create a C++ function called IsAllow that takes a non-empty input called mat of type std::vector<std::vector<int>>, all rows should be the same size and each element in the 2D input array can be either zero or one, one means it's part of swimming pool and zero means it's not part of the swimming pool. This function should return a boolean true if the swimming pool design is approved. Note that a pool is considered approved if it does not touch any of the four borders in this 2D array input otherwise returns false. Don't forget to validate the inputs.

 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool IsAllow(std::vector<std::vector<int>> mat) {
    if (mat.size() <= 0) {
        throw std::invalid_argument("mat can't be empty");
    }

    if (mat[0].size() <= 0) {
        throw std::invalid_argument("mat rows can't be empty");
    }

    int first_row_length = mat[0].size();

    for (const std::vector<int> &row : mat) {

        for (const int &item : row) {
            if (item != 0 && item != 1) {
                throw std::invalid_argument("item should be 0 or 1");
            }
        }

        if (row.size() != first_row_length) {
            throw std::invalid_argument("rows should be the same size");
        }
    }

    for (int jdx = 0; jdx < mat.size(); jdx++) {
        for (int idx = 0; idx < mat[jdx].size(); idx++) {
            if (jdx == 0 || jdx == mat.size() - 1 || idx == 0 || idx == mat[jdx].size() - 1) {
                if (mat[jdx][idx] != 0) {
                    return false;
                }
            }
        }
    }

    return true;
}

#include <cassert>
int main() {
    // TEST
    assert((IsAllow({{0, 0}, {0, 0}}) == true));
    // TEST_END

    // TEST
    assert((IsAllow({{0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 1, 1, 1, 1, 1, 0, 0},
                     {0, 1, 1, 1, 1, 1, 0, 0},
                     {0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0}}) == true));
    // TEST_END

    // TEST
    assert((IsAllow({{1, 1, 0, 0, 0, 0, 0, 0},
                     {1, 1, 1, 1, 1, 1, 0, 0},
                     {0, 1, 1, 1, 1, 1, 0, 0},
                     {0, 1, 1, 0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0}}) == false));
    // TEST_END

    // TEST
    assert((IsAllow({{0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0}}) == true));
    // TEST_END

    // TEST
    assert((IsAllow({{0, 0, 0, 0, 0, 0, 0, 1},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 0, 0, 0, 0, 0, 0, 0}}) == false));
    // TEST_END

    // TEST
    assert((IsAllow({{0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 0, 0, 0, 0, 0, 1, 0}}) == false));
    // TEST_END

    // TEST
    assert((IsAllow({{0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 0, 0, 1, 0, 0, 0, 0}}) == false));
    // TEST_END

    // TEST
    assert((IsAllow({{0, 0, 0, 0, 0, 0, 0, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {0, 1, 1, 1, 1, 1, 1, 0},
                     {1, 1, 1, 1, 1, 1, 1, 0},
                     {0, 0, 0, 1, 0, 0, 0, 0}}) == false));
    // TEST_END

    // TEST
    try {
        IsAllow({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IsAllow({{}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IsAllow({{1, 0}, {1}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IsAllow({{1, 2}, {1, 0}});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}