/***
 * Prompt:




 khaled_cpp_121-2024_May_18: 1462b8f4-1f7e-4047-a7ef-2908c847ec72


func_IsScramble_khaled_cpp_121-2024_May_18

Create a C++ function called IsScramble that takes two non-empty case-sensitive inputs of type string called str1 and str2, they should contain any kind of characters including spaces and special characters. This function should return a Boolean true if a string str2 is a scrambled string of str1, please use recursion and don't forget to validate the input.




 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>

bool IsScramble(const std::string &str1, const std::string &str2, std::unordered_map<std::string, bool> &memo) {
    if (str1 == str2) {
        return true;
    }

    if (str1.size() != str2.size()) {
        return false;
    }

    std::string key = str1 + " " + str2;

    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    int size = str1.size();

    for (int idx = 1; idx < size; ++idx) {
        if ((IsScramble(str1.substr(0, idx), str2.substr(0, idx), memo) && IsScramble(str1.substr(idx), str2.substr(idx), memo)) ||
            (IsScramble(str1.substr(0, idx), str2.substr(size - idx), memo) && IsScramble(str1.substr(idx), str2.substr(0, size - idx), memo))) {
            return memo[key] = true;
        }
    }

    return memo[key] = false;
}

bool IsScramble(const std::string &str1, const std::string &str2) {
    if (str1.empty() || str2.empty()) {
        throw std::invalid_argument("Both inputs can't be empty");
    }

    std::unordered_map<std::string, bool> memo;

    return IsScramble(str1, str2, memo);
}

#include <cassert>
int main() {
    // TEST
    assert(IsScramble("12", "21") == true);
    // TEST_END

    // TEST
    assert(IsScramble("A%^3", "^3A%") == true);
    // TEST_END

    // TEST
    assert(IsScramble("A ", " A") == true);
    // TEST_END

    // TEST
    assert(IsScramble("A", "a") == false);
    // TEST_END

    // TEST
    assert(IsScramble("A", "A") == true);
    // TEST_END

    // TEST
    try {
        IsScramble("12", "");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        IsScramble("", "fd");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
