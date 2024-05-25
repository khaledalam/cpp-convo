/***
 * Prompt:




 khaled_cpp_116-2024_May_18: 02cb68de-a4c5-47cf-bfba-fa5371e4827d


 func_RearrangeMe_khaled_cpp_116-2024_May_18

 

Design a C++ function called RearrangeMe that takes a non-empty string of type std::string. This input string can contains any kind of character
including spaces and special characters. This function should rearrange characters of the input string such that no two adjacent characters are
the same for example "abcc" should be "cbca" and "AaBb" should be "baBA", and return this sorted string of type std::string. Please note that if
it's impossible to achieve the goal of the function throw an exception and please don't forget to validate the input.




 */

#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

std::string RearrangeMe(const std::string &str) {
    if (str.empty()) {
        throw std::invalid_argument("str can't be empty");
    }

    std::unordered_map<char, int> frequency;
    for (const char &character : str) {
        frequency[character]++;
    }

    std::priority_queue<std::pair<int, char>> max_heap;
    for (const auto &entry : frequency) {
        max_heap.push({entry.second, entry.first});
    }

    std::string result = "";
    std::pair<int, char> prev = {-1, '#'};
    while (!max_heap.empty()) {
        std::pair<int, char> top = max_heap.top();
        max_heap.pop();
        result += top.second;
        if (prev.first > 0) {
            max_heap.push(prev);
        }
        prev = {top.first - 1, top.second};
    }

    if (result.length() != str.length()) {
        throw std::invalid_argument("it's impossible to achieve the goal of the function");
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(RearrangeMe("abcc") == std::string("cbca"));
    // TEST_END

    // TEST
    assert(RearrangeMe("aBcc") == std::string("cacB"));
    // TEST_END

    // TEST
    assert(RearrangeMe("zzzab") == std::string("zbzaz"));
    // TEST_END

    // TEST
    assert(RearrangeMe("aaavvv") == std::string("vavava"));
    // TEST_END

    // TEST
    assert(RearrangeMe("zadd") == std::string("dzda"));
    // TEST_END

    // TEST
    assert(RearrangeMe("Aa") == std::string("aA"));
    // TEST_END

    // TEST
    assert(RearrangeMe("AaBb") == std::string("baBA"));
    // TEST_END

    // TEST
    assert(RearrangeMe("@@z") == std::string("@z@"));
    // TEST_END

    // TEST
    try {
        RearrangeMe("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        RearrangeMe("aa");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
