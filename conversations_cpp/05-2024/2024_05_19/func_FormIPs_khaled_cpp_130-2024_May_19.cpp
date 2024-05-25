/***
 * Prompt:




 khaled_cpp_130-2024_May_19: 04f9224b-3ee7-4e7f-ba58-7489c80656a3

func_FormIPs_khaled_cpp_130-2024_May_19

Create a C++ function called FormIPs that takes one non-empty string input of type std::string called str containing only digits. This function should return list of string of type std::vector<std::string> that represent all possible valid IP addresses that can be obtained from input str. Consider that valid IP address is consisting of 4 parts separated by dot, each part is a number between 0 and 255. No problem if you return list in any order. Please don't forget to validate the input.



 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

bool IsValid(std::string ip_part) { return !(stoi(ip_part) > 255) && !(ip_part.size() > 1 && ip_part[0] == '0'); }

std::vector<std::string> FormIPs(std::string str) {
    if (str.empty()) {
        throw std::invalid_argument("str cannot be empty");
    }

    std::vector<std::string> result;

    if (str.size() >= 4 && str.size() <= 12) {
        for (int wdx = 1; wdx <= 3; wdx++) {
            for (int xdx = 1; xdx <= 3; xdx++) {
                for (int ydx = 1; ydx <= 3; ydx++) {
                    for (int zdx = 1; zdx <= 3; zdx++) {
                        if (!(wdx + xdx + ydx + zdx > str.length() || wdx + xdx + ydx + zdx < str.length())) {
                            std::string part1 = str.substr(0, wdx);
                            std::string part2 = str.substr(wdx, xdx);
                            std::string part3 = str.substr(wdx + xdx, ydx);
                            std::string part4 = str.substr(wdx + xdx + ydx, zdx);

                            if (IsValid(part1) && IsValid(part2) && IsValid(part3) && IsValid(part4)) {
                                result.push_back(part1 + "." + part2 + "." + part3 + "." + part4);
                            }
                        }
                    }
                }
            }
        }
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((FormIPs("0.011.255.245") == std::vector<std::string>{}));
    // TEST_END

    // TEST
    assert((FormIPs("0000") == std::vector<std::string>{"0.0.0.0"}));
    // TEST_END

    // TEST
    assert((FormIPs("1111") == std::vector<std::string>{"1.1.1.1"}));
    // TEST_END

    // TEST
    assert((FormIPs("010010") == std::vector<std::string>{"0.10.0.10", "0.100.1.0"}));
    // TEST_END

    // TEST
    assert((FormIPs("101023") == std::vector<std::string>{"1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3", "101.0.2.3"}));
    // TEST_END

    // TEST
    try {
        FormIPs("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
