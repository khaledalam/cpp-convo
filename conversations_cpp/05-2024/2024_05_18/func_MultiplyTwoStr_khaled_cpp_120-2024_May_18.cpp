/***
 * Prompt:




 khaled_cpp_120-2024_May_18: b9214620-4fd3-4197-a439-fd28f52cf8ba

func_MultiplyTwoStr_khaled_cpp_120-2024_May_18



Create a C++ function called MultiplyTwoStr that takes two non-empty inputs of type string called num1 and num2, they should contain only representation of zero or positive numbers. This function should multiply two large numbers represented as strings and return the result as a std::string. Please don't forget to validate the input.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string MultiplyTwoStr(const std::string &num1, const std::string &num2) {
    if (num1.empty() || num2.empty()) {
        throw std::invalid_argument("Both inputs can't be empty");
    }

    if (num1[0] == '-' || num2[0] == '-') {
        throw std::invalid_argument("Both inputs should represent zero or positive numbers");
    }

    if (num1 == "0" || num2 == "0") {
        return "0";
    }

    for (char const character : num1) {
        if (!isdigit(character)) {
            throw std::invalid_argument("num1 is invalid number");
        }
    }

    for (char const character : num2) {
        if (!isdigit(character)) {
            throw std::invalid_argument("num2 is invalid number");
        }
    }

    std::vector<int> result(num1.size() + num2.size(), 0);

    for (int idx = num1.size() - 1; idx >= 0; --idx) {
        for (int jdx = num2.size() - 1; jdx >= 0; --jdx) {
            int mul = (num1[idx] - '0') * (num2[jdx] - '0');
            int sum = mul + result[idx + jdx + 1];
            result[idx + jdx] += sum / 10;
            result[idx + jdx + 1] = sum % 10;
        }
    }

    std::string result_str;

    for (int num : result) {
        if (!(result_str.empty() && num == 0)) {
            result_str.push_back(num + '0');
        }
    }

    return result_str;
}

#include <cassert>
int main() {
    // TEST
    assert(MultiplyTwoStr("12", "2") == std::string("24"));
    // TEST_END

    // TEST
    assert(MultiplyTwoStr("12", "1") == std::string("12"));
    // TEST_END

    // TEST
    assert(MultiplyTwoStr("12", "0") == std::string("0"));
    // TEST_END

    // TEST
    assert(MultiplyTwoStr("0", "12140") == std::string("0"));
    // TEST_END

    // TEST
    assert(MultiplyTwoStr("01", "2") == std::string("2"));
    // TEST_END

    // TEST
    try {
        MultiplyTwoStr("", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MultiplyTwoStr("-1", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MultiplyTwoStr("12", "-2");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MultiplyTwoStr("12@", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MultiplyTwoStr("12", "1T");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
