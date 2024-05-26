/***






 khaled_cpp_147_-2024_May_25: 1c5dc76c-0014-4030-84fa-ae350a671407

func_AddTwoBinaryStrs_khaled_cpp_147_-2024_May_25



Create a C++ function called AddTwoBinaryStrs that takes 2 non-empty texts called str1 and str2 of type std::string
which representing two binary numbers represented as string. This function should return another text of type
std::string that represents the sum of the 2 input strings in binary representation too. Please don't forget to validate the input.


 */

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string AddTwoBinaryStrs(const std::string &str1, const std::string &str2) {
    if (str1.empty()) {
        throw std::invalid_argument("str1 can't be empty");
    }

    if (str2.empty()) {
        throw std::invalid_argument("str2 can't be empty");
    }

    for (const char &character : str1) {
        if (character != '0' && character != '1') {
            throw std::invalid_argument("str1 contains invalid character");
        }
    }

    for (const char &character : str2) {
        if (character != '0' && character != '1') {
            throw std::invalid_argument("str2 contains invalid character");
        }
    }

    std::string str11 = (str1.length() > str2.length() ? str1 : str2);
    std::string str22 = (str1.length() > str2.length() ? str2 : str1);

    int diff = str11.length() - str22.length();
    std::stringstream stringstreamer;

    while (diff) {
        stringstreamer << "0";
        --diff;
    }

    str22 = stringstreamer.str() + str22;

    stringstreamer.str(std::string());

    int idx = str11.length() - 1, carry = 0;
    while (idx >= 0) {
        int xdx = (str11[idx] - '0') + (str22[idx] - '0') + carry;
        if (xdx == 2) {
            xdx = 0;
            carry = 1;
        } else if (xdx == 3) {
            xdx = 1;
            carry = 1;
        } else {
            carry = 0;
        }
        stringstreamer << xdx;
        --idx;
    }
    if (carry == 1) {
        stringstreamer << carry;
    }

    std::string result = stringstreamer.str();

    std::reverse(result.begin(), result.end());

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(AddTwoBinaryStrs("1010", "1011") == "10101");
    // TEST_END

    // TEST
    assert(AddTwoBinaryStrs("1", "0") == "1");
    // TEST_END

    // TEST
    assert(AddTwoBinaryStrs("0", "1") == "1");
    // TEST_END

    // TEST
    assert(AddTwoBinaryStrs("1", "1") == "10");
    // TEST_END

    // TEST
    assert(AddTwoBinaryStrs("0", "0") == "0");
    // TEST_END

    // TEST
    try {
        AddTwoBinaryStrs("", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AddTwoBinaryStrs("1", "");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AddTwoBinaryStrs("", "");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AddTwoBinaryStrs("21", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        AddTwoBinaryStrs("sfa$@#", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}