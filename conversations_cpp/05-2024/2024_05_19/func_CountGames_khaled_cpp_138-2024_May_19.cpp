/***
 * Prompt:




 khaled_cpp_138-2024_May_19: 6be48ea3-bbb5-418c-8ebc-04408bc48a99

func_CountGames_khaled_cpp_138-2024_May_19

Create a C++ function called CountGames that takes 2 inputs of type int, both of them greater than 0, the first input is called pages which represents the number of pages we have in the book, the second input is called target which represents the target page that we want to reach. This function should return another number of type int which represents find and return the minimum number of pages that must be turned in order to arrive at the page target. Don't forget to validate the inputs.

 */

#include <iostream>
#include <stdexcept>
#include <string>

int MinTurns(int pages, int target) {
    if (pages <= 0) {
        throw std::invalid_argument("pages should be greater 0");
    }

    if (target <= 0) {
        throw std::invalid_argument("target should be greater 0");
    }

    if (pages < target) {
        throw std::invalid_argument("target can't be greater than pages");
    }

    if (target % 2 != 0) {
        --target;
    }

    if (pages % 2 != 0) {
        --pages;
    }

    int front = target / 2;

    int back = (pages - target) / 2;

    return front < back ? front : back;
}

#include <cassert>
int main() {
    // TEST
    assert((MinTurns(5, 3) == 1));
    // TEST_END

    // TEST
    assert((MinTurns(21, 20) == 0));
    // TEST_END

    // TEST
    assert((MinTurns(21, 17) == 2));
    // TEST_END

    // TEST
    assert((MinTurns(21, 15) == 3));
    // TEST_END

    // TEST
    assert((MinTurns(21, 21) == 0));
    // TEST_END

    // TEST
    try {
        MinTurns(0, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinTurns(-1, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinTurns(1, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinTurns(1, -3);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinTurns(21, 22);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}