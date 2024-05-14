/***
 * Prompt:




 khaled_cpp_100-2024_May_12: 68f23ea6-0286-4d14-a960-94ec79fa4e62

 func_StreetLighting_khaled_cpp_100-2024_May_12

Design a C++ function called StreetLighting which accepts two inputs, The first input non-empty digits-only string called light_power of type std::string, second input called street_lamps of type std::vector<int> which represents the level of the lamp, we consider the lamp needs power if its level less than zero. This function should return a Boolean true if the light_power can cover the needed levels otherwise return false. Please note that each digit in light_power can increase the lamp level by the digit's value, please also don't forget to validate the inputs.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool StreetLighting(std::string light_power, std::vector<int> street_lamps) {
    if (light_power.empty()) {
        throw std::invalid_argument("light_power can't be empty");
    }

    if (street_lamps.empty()) {
        throw std::invalid_argument("street_lamps can't be empty");
    }

    if (street_lamps.size() != light_power.size()) {
        throw std::invalid_argument("questions and street_lamps should be with the same size");
    }

    int power_sum = 0;

    for (const char &light : light_power) {
        if (!isdigit(light)) {
            throw std::invalid_argument("light_power characters should be digits only");
        }

        power_sum += (light - '0');
    }

    for (const int &lamp : street_lamps) {

        if (lamp < 0) {
            power_sum += lamp;
        }

        if (power_sum < 0) {
            return false;
        }
    }

    return power_sum >= 0;
}

#include <cassert>
int main() {
    // TEST
    assert((StreetLighting("123", {-1, -2, -3}) == true));
    // TEST_END

    // TEST
    assert((StreetLighting("123", {-1, -2, -2}) == true));
    // TEST_END

    // TEST
    assert((StreetLighting("123", {-1, -2, -4}) == false));
    // TEST_END

    // TEST
    assert((StreetLighting("123", {1, -2, -4}) == true));
    // TEST_END

    // TEST
    assert((StreetLighting("123", {0, -2, -4}) == true));
    // TEST_END

    // TEST
    try {
        StreetLighting("-23", {1, -2, -4});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        StreetLighting("", {1, -2, -4});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        StreetLighting("#$", {1, -2, -4});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        StreetLighting("23", {1, -2, -4});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
