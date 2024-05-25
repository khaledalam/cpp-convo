/***
 * Prompt:




 khaled_cpp_134-2024_May_19: b8ed7f2c-c1ee-4ee3-9dc5-ccbb4c3438bd

 func_TrafficLightValidator_khaled_cpp_134-2024_May_19


Create a C++ function called TrafficLightValidator that takes one non-empty input string of type std::string, this string should be a sequence of the following codes: R (red), Y (yellow), G (Green), P (Pause - flash red), C (Caution - flash yellow), and X (off). 

Note that a three-color traffic light must switch lights in the following order: red, green, yellow, and red. To indicate when crossing slowly without a stop is permitted, the yellow signal may be flashed. To indicate when crossing immediately after a full stop is permitted, the red signal may be flashed. 

Either flash sequence may only be started after the red light is lit and must be followed with a red. All lights are initially off. All sequences must begin with a red light. Lighting any light causes all other lights to turn off. No color may be repeated: e.g., red, red is not allowed. 

This function should return another text of type std::string that represents after checking if that sequence follows or violates the traffic light rules, if it follows then return "accept", and if it doesn't follow return "reject" and if input is invalid return "error". 

For example input "R G Y R" should return "accept" and input "R Y G P" should return "reject", and input "t e s t" should return "error". 

Please don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

std::string TrafficLightValidator(std::string lights) {
    if (lights.empty()) {
        throw std::invalid_argument("lights must not be empty");
    }

    const std::string accept = "accept";
    const std::string reject = "reject";
    const std::string error = "error";
    const std::vector<char> valid_lights = {'R', 'G', 'Y'};
    const std::vector<char> valid_flashes = {'C', 'P'};
    const char interval = ' ';
    const char off = 'X';
    const int min_size = 6;
    const int max_size = 30;

    if (lights.size() < min_size || lights.size() > max_size) {
        return error;
    }

    for (int idx = 0; idx < lights.size(); idx++) {
        if (idx % 2 != 0) {
            if (lights[idx] != interval) {
                return error;
            }
        } else {
            if (lights[idx] != off && std::find(valid_lights.begin(), valid_lights.end(), lights[idx]) == valid_lights.end() &&
                std::find(valid_flashes.begin(), valid_flashes.end(), lights[idx]) == valid_flashes.end()) {
                return error;
            }
        }
    }

    if (lights[0] != valid_lights[0]) {
        return reject;
    }

    for (int idx = 1; idx < lights.size(); idx++) {
        if (lights[idx] == interval) {
            continue;
        }

        bool isFlash = std::find(valid_flashes.begin(), valid_flashes.end(), lights[idx]) != valid_flashes.end();

        int light_index = -1;
        auto item = std::find(valid_lights.begin(), valid_lights.end(), lights[idx]);
        if (item != valid_lights.end()) {
            light_index = item - valid_lights.begin();
        }

        if (idx != (lights.size() - 1) && lights[idx] == off) {
            return reject;
        }

        if ((isFlash && lights.size() < 3) || (isFlash && idx == 0) || (isFlash && idx == lights.size() - 1) ||
            (isFlash && (lights[idx - 2] != lights[0] || lights[idx + 2] != lights[0]))) {
            return reject;
        }

        if (light_index > 0 && lights[idx - 2] != valid_lights[light_index - 1]) {
            return reject;
        }
    }

    return accept;
}

#include <cassert>
int main() {
    // TEST
    assert((TrafficLightValidator("R G Y R") == "accept"));
    // TEST_END

    // TEST
    assert((TrafficLightValidator("R G Y R C R G Y R") == "accept"));
    // TEST_END

    // TEST
    assert((TrafficLightValidator("R G Y R C R") == "accept"));
    // TEST_END

    // TEST
    assert((TrafficLightValidator("R G Y R C") == "reject"));
    // TEST_END

    // TEST
    assert((TrafficLightValidator("r") == "error"));
    // TEST_END

    // TEST
    assert((TrafficLightValidator("G Y") == "error"));
    // TEST_END

    // TEST
    assert((TrafficLightValidator("$@") == "error"));
    // TEST_END

    // TEST
    assert((TrafficLightValidator("R 5") == "error"));
    // TEST_END

    // TEST
    try {
        TrafficLightValidator("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}