/***






 khaled_cpp_158_2024_May_26: 347245aa-681a-46d4-97d2-0f067a50c3c3

 func_RabbitMinSteps_khaled_cpp_158_2024_May_26




Create a C++ function called RabbitMinSteps that takes a number of type const int as input called target, which should be between 1 and 100000.


A rabbit decided to visit his friend. It turned out that the rabbit's house is located at point 0 and his friend's house is located at point x(x > 0) of the coordinate line. In one step the rabbit can move 1, 2, 3, 4 or 5 positions forward. Determine, what is the minimum number of steps he needs to make in order to get to his friend's house.


This function should return a number of type int that represent the minimum number of steps that the rabbit needs to make to get from point 0 to point x. Please don't forget to validate the input.





*/

#include <array>
#include <iostream>
#include <stdexcept>
#include <string>

int RabbitMinSteps(const int target) {
    if (target < 1 || target > 100000) {
        throw std::invalid_argument("target should be between 1 and 100000");
    }

    const std::array<int, 5> rabbit_speed = {5, 4, 3, 2, 1};
    int position = 0;
    int steps = 0;

    while (position < target) {
        for (auto &speed : rabbit_speed) {
            if ((position + speed) <= target) {
                position += speed;
                steps++;
                break;
            }
        }
    }

    return steps;
}

#include <cassert>
int main() {
    // TEST
    assert(RabbitMinSteps(5) == 1);
    // TEST_END

    // TEST
    assert(RabbitMinSteps(12) == 3);
    // TEST_END

    // TEST
    try {
        RabbitMinSteps(0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RabbitMinSteps(-1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RabbitMinSteps(1000001);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}