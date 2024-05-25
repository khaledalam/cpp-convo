/***
 * Prompt:




 khaled_cpp_129-2024_May_19: 744d9b4f-ef65-4551-becb-eb771b69b35a

 func_UniqueBST_khaled_cpp_129-2024_May_19


Create a C++ function called UniqueBST that takes one input number called num that can be greater than 0. This function should return another number of type int that represents how many structurally unique BST's (binary search trees) store values 1 ... num? Please use recursion and don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

int UniqueBST(int num) {
    if (num < 0) {
        throw std::invalid_argument("num cannot be less than 0");
    }

    if (num <= 1) {
        return 1;
    }

    int r_num = 0;

    for (int idx = 1; idx <= num; idx++) {
        r_num += UniqueBST(idx - 1) * UniqueBST(num - idx);
    }

    return r_num;
}

#include <cassert>
int main() {
    // TEST
    assert((UniqueBST(1) == 1));
    // TEST_END

    // TEST
    assert((UniqueBST(2) == 2));
    // TEST_END

    // TEST
    assert((UniqueBST(3) == 5));
    // TEST_END

    // TEST
    assert((UniqueBST(4) == 14));
    // TEST_END

    // TEST
    assert((UniqueBST(0) == 1));
    // TEST_END

    // TEST
    try {
        UniqueBST(-3);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
