/***
 * Prompt:




 khaled_cpp_117-2024_May_18: 6214fe72-840a-4c70-a844-5db9c5ef0fd5

func_SmallestSubstrAllChars_khaled_cpp_117-2024_May_18


Design a C++ function called SmallestSubstrAllChars that takes two non-empty string inputs, the first input called str of type std::string, the second input called another of type std::string. Both inputs can contain any kind of characters including spaces and special characters. This function should return the smallest substring in the first input string that contains all characters of the second input another string for example "Zab@cc" and "abc" should return "ab@c". Please note that if it's impossible to achieve the goal of the function throw an exception and please don't forget to validate the inputs.




 */

#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

std::string SmallestSubstrAllChars(const std::string &str, const std::string &another) {
    if (str.empty() || another.empty()) {
        throw std::invalid_argument("Both inputs can't be empty");
    }

    std::unordered_map<char, int> map_t, window;
    for (const char &character : another) {
        map_t[character]++;
    }

    int have = 0, need = map_t.size(), left = 0, right = 0, min_len = INT_MAX, start = 0;
    while (right < str.size()) {
        char character = str[right];
        window[character]++;
        if (map_t.find(character) != map_t.end() && window[character] == map_t[character]) {
            have++;
        }

        while (have == need) {
            if (right - left + 1 < min_len) {
                min_len = right - left + 1;
                start = left;
            }
            window[str[left]]--;
            if (map_t.find(str[left]) != map_t.end() && window[str[left]] < map_t[str[left]]) {
                have--;
            }
            left++;
        }
        right++;
    }

    if (min_len == INT_MAX) {
        throw std::invalid_argument("Can't find result");
    }

    return str.substr(start, min_len);
}

#include <cassert>
int main() {
    // TEST
    assert(SmallestSubstrAllChars("Zab@cc", "abc") == std::string("ab@c"));
    // TEST_END

    // TEST
    assert(SmallestSubstrAllChars("Zab@ccZaaaa@", "Z@") == std::string("Zab@"));
    // TEST_END

    // TEST
    assert(SmallestSubstrAllChars("   avb", " v") == std::string(" av"));
    // TEST_END

    // TEST
    try {
        SmallestSubstrAllChars("", "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SmallestSubstrAllChars("test", "");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SmallestSubstrAllChars("", "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SmallestSubstrAllChars("Abc", "ac");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
