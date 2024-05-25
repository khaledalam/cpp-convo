/***
 * Prompt:




 khaled_cpp_140-2024_May_23: cdced835-b298-4066-a475-9308deed87a6

func_GalaxiesCollision_khaled_cpp_140-2024_May_23

Create a C++ function called GalaxiesCollision that takes a non-empty input called galaxies of type std::vector<int> that represents galaxies in a row. For each galaxy, the absolute value represents its size, and the sign represents its direction (positive meaning right, negative meaning left). Each galaxy moves at the same speed. Find out the state of the galaxies after all collisions. If two galaxies meet, the smaller one will explode. If both are the same size, both will explode. Two galaxies moving in the same direction will never meet. This function should return another array of integers of type std::vector<int> that represents the state of the galaxies after all collisions. Please don't forget to validate the inputs.

 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

std::vector<int> GalaxiesCollision(std::vector<int> galaxies) {
    if (galaxies.empty()) {
        throw std::invalid_argument("galaxies can't be empty");
    }

    std::vector<int> result;
    std::stack<int> stack_con;

    stack_con.push(galaxies[0]);
    galaxies.erase(galaxies.begin());

    for (const int &galaxy : galaxies) {
        if (galaxy == 0) {
            result.clear();
            return result;
        }
        if (std::signbit(galaxy) == std::signbit(stack_con.top())) {
            stack_con.push(galaxy);
        } else {
            bool exploded = false;
            while (!stack_con.empty()) {
                if (abs(galaxy) == abs(stack_con.top()) && std::signbit(galaxy) && !std::signbit(stack_con.top())) {
                    stack_con.pop();
                    exploded = true;
                    break;
                } else {
                    if (abs(galaxy) > abs(stack_con.top()) && std::signbit(galaxy) && !std::signbit(stack_con.top())) {
                        stack_con.pop();
                    } else {
                        if (!std::signbit(galaxy) && std::signbit(stack_con.top())) {
                            stack_con.push(galaxy);
                        }
                        break;
                    }
                }
            }
            if (stack_con.empty() && !exploded) {
                stack_con.push(galaxy);
            }
        }
    }

    while (!stack_con.empty()) {
        result.push_back(stack_con.top());
        stack_con.pop();
    }

    std::reverse(result.begin(), result.end());

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((GalaxiesCollision({5, 10, -5}) == std::vector<int>{5, 10}));
    // TEST_END

    // TEST
    assert((GalaxiesCollision({8, -8}) == std::vector<int>{}));
    // TEST_END

    // TEST
    assert((GalaxiesCollision({0, -8}) == std::vector<int>{-8}));
    // TEST_END

    // TEST
    assert((GalaxiesCollision({10, 2, -5}) == std::vector<int>{10}));
    // TEST_END

    // TEST
    assert((GalaxiesCollision({-2, -1, 1, 2}) == std::vector<int>{-2, -1, 1, 2}));
    // TEST_END

    // TEST
    try {
        GalaxiesCollision({});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}