/***
 * Prompt:




 khaled_cpp_101-2024_May_14: 4d1324f2-1b6d-4f82-8e2f-1ee43f832eaf

Design a C++ function called InterviewTimeSlot which accepts two inputs, The first input is a non-empty list of intervals called slots of type std::vector<std::pair<int, int>>, each pair represents an interval where the first argument should be less than or equal to the second argument, second input called suggestion of type int. This function should return a number of type int which represents how many intervals suit the suggestion. Please note that interval is suitable if the suggestion intersects it(between or equal first and second arguments of the interval). please also don't forget to validate the inputs.



func_InterviewTimeSlot_khaled_cpp_101-2024_May_14

 */

#include <algorithm>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

int InterviewTimeSlot(std::vector<std::pair<int, int>> slots, int suggestion) {
    if (slots.empty()) {
        throw std::invalid_argument("slots can't be empty");
    }

    if (suggestion < 0) {
        throw std::invalid_argument("suggestion can't be less than zero");
    }

    int ok_slots_count = 0;

    for (const std::pair<int, int> &slot : slots) {
        if (slot.first < 0 || slot.second < 0) {
            throw std::invalid_argument("slot is invalid");
        }

        if (slot.first > slot.second) {
            throw std::invalid_argument("slot first argument should be less than or equal second argument");
        }

        if (slot.first <= suggestion && slot.second >= suggestion) {
            ok_slots_count++;
        }
    }

    return ok_slots_count;
}

#include <cassert>
int main() {
    // TEST
    assert(InterviewTimeSlot({{1, 3}, {1, 5}}, 4) == 1);
    // TEST_END

    // TEST
    assert(InterviewTimeSlot({{1, 2}, {2, 5}}, 2) == 2);
    // TEST_END

    // TEST
    assert(InterviewTimeSlot({{1, 2}}, 1) == 1);
    // TEST_END

    // TEST
    assert(InterviewTimeSlot({{1, 2}}, 2) == 1);
    // TEST_END

    // TEST
    assert(InterviewTimeSlot({{1, 2}}, 0) == 0);
    // TEST_END

    // TEST
    assert(InterviewTimeSlot({{1, 3}, {5, 5}}, 4) == 0);
    // TEST_END

    // TEST
    try {
        InterviewTimeSlot({}, 2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        InterviewTimeSlot({{-1, 3}}, 2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        InterviewTimeSlot({{1, -3}}, 2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        InterviewTimeSlot({{1, 3}}, -2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        InterviewTimeSlot({{7, 3}}, 2);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
