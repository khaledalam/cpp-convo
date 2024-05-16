/***
 * Prompt:




 khaled_cpp_105-2024_May_14: bcde5bca-140f-4d3e-9750-7cef462e08af


func_RoadBumps_khaled_cpp_105-2024_May_14


Write a C++ function called RoadBumps that accepts a non-empty string input called road of type std::string which should contains only "@"
and "." symbols. "@" represent bump and "." represents good. This function should return a Boolean true if there are no two or more
consecutive bumps in the road otherwise return false. Please validate the inputs.

 */

#include <algorithm>

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool RoadBumps(std::string road) {
    if (road.empty()) {
        throw std::invalid_argument("road can't be empty");
    }

    for (const char character : road) {
        if (character != '.' && character != '@') {
            throw std::invalid_argument("Invalid character");
        }
    }

    return road.find(std::string("@@")) == std::string::npos;
}

#include <cassert>
int main() {
    // TEST
    assert(RoadBumps(".@.@") == true);
    // TEST_END

    // TEST
    assert(RoadBumps(".@.@....@@") == false);
    // TEST_END\

    // TEST
    assert(RoadBumps(".@@.") == false);
    // TEST_END

    // TEST
    assert(RoadBumps(".@@@@@@.") == false);
    // TEST_END

    // TEST
    assert(RoadBumps(".") == true);
    // TEST_END

    // TEST
    assert(RoadBumps("..") == true);
    // TEST_END

    // TEST
    assert(RoadBumps("@") == true);
    // TEST_END

    // TEST
    assert(RoadBumps("@@") == false);
    // TEST_END

    // TEST
    try {
        RoadBumps("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RoadBumps("#");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RoadBumps("Test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
