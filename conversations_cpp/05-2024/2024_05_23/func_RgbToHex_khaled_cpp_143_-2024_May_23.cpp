/***
 * Prompt:




 khaled_cpp_143_-2024_May_23: aafa8f36-7351-49dd-9bca-ecfb56804a4d


func_RgbToHex_khaled_cpp_143_-2024_May_23


Create a C++ function called RgbToHex that takes input called rgb of type std::string which should match the rgb color pattern, which means start with the prefix "rgb(" then 3 comma-separated numbers the suffix ")". Please note that the input string can contain spaces between the numbers, and input is case-sensitive which means "RGB(" prefix is not acceptable. This function should return another string of type std::string that represents the rgx in hex formats. example: input "rgb(   45, 255,    192)" should return "#2dffc0". Please don't forget to validate the inputs.
 
 
 */

#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>

std::string RgbToHex(std::string rgb) {
    if (rgb.empty()) {
        throw std::invalid_argument("rgb can't be empty");
    }

    std::string hex = "#";

    std::regex regex_rgb("(rgb\\(\\s*(\\s*[0-9]{1,3})\\s*,\\s*([0-9]{1,3})\\s*,\\s*([0-9]{1,3}\\s*)*)");

    std::smatch matches;

    if (std::regex_search(rgb, matches, regex_rgb)) {
        for (size_t i = 2; i < 5 && i < matches.size(); ++i) {
            std::stringstream ss_hex;

            ss_hex << std::setw(2) << std::setfill('0') << std::hex << atoi(matches[i].str().c_str());

            hex += ss_hex.str();
        }
    } else {
        throw std::invalid_argument("Invalid RGB string input");
    }

    return hex;
}

#include <cassert>
int main() {
    // TEST
    assert(RgbToHex("rgb(0, 128, 192)") == "#0080c0");
    // TEST_END

    // TEST
    assert(RgbToHex("rgb(   45, 255,    192)") == "#2dffc0");
    // TEST_END

    // TEST
    assert(RgbToHex("rgb(0, 0, 0)") == "#000000");
    // TEST_END

    // TEST
    try {
        RgbToHex("(10, 10, 10)");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RgbToHex("RGB(10, 10, 10)");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RgbToHex("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RgbToHex("$#");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RgbToHex("123");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}