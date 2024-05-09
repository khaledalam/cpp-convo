/***
 * Prompt:




 khaled_cpp_39_2024_24_04: cd043f5f-df63-4ce3-ba6e-7ff369e7e2dd

 alarm turn off of the day


 Write me C++ class called LockKeyboard which contains a method called Attempt, it will accept one input called hits of type std::vector<std::pair<std::string, std::string>>. Each pair in the input represents a hit(the first argument of the pair should be "top" or "bottom" which means the vertical direction of the hit and the second argument in the pair should be "left" or "right" which represents the horizontal direction) on the small keyboard that consists of 4 keys only, first key on the keyboard at the top left is 1, second key on the keyboard at the top right is 2, third key at the bottom left is 3, fourth key at the bottom right is 4. Input should be exactly 4 pairs representing 4 hits. The method should return another list of type std::vector<int> which means the keys' values that the user pressed. Please don't forget to validate the input and the values.

 class_LockKeyboard_khaled_cpp_39_2024_24_04

 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

class LockKeyboard {
public:
    std::vector<int> Attempt(std::vector<std::pair<std::string, std::string>> hits) {

        std::vector<int> result;

        std::map<std::pair<std::string, std::string>, int> mapper;
        mapper[std::make_pair("top", "left")] = 1;
        mapper[std::make_pair("top", "right")] = 2;
        mapper[std::make_pair("bottom", "left")] = 3;
        mapper[std::make_pair("bottom", "right")] = 4;

        if (hits.size() != 4) {
            throw std::invalid_argument("Input must be exactly 4 pairs");
        }

        for (const std::pair<std::string, std::string> &hit : hits) {
            if (hit.first != "top" && hit.first != "bottom") {
                throw std::invalid_argument("First argument in the pair should be 'top' or 'bottom'");
            }

            if (hit.second != "left" && hit.second != "right") {
                throw std::invalid_argument("Second argument in the pair should be 'top' or 'bottom'");
            }

            result.push_back(mapper[hit]);
        }

        return result;
    }
};

#include <cassert>
int main() {
    LockKeyboard lock_keyboard;

    // TEST
    assert((lock_keyboard.Attempt( { std::make_pair("top", "left"), std::make_pair("top", "left"), std::make_pair("top", "left"), std::make_pair("top", "left") }) == std::vector<int> { 1, 1, 1, 1 }));
    // TEST_END

    // TEST
    assert((lock_keyboard.Attempt( { std::make_pair("top", "left"), std::make_pair("top", "right"), std::make_pair("top", "left"), std::make_pair("top", "left") }) == std::vector<int> { 1, 2, 1, 1 }));
    // TEST_END

    // TEST
    assert((lock_keyboard.Attempt( { std::make_pair("top", "left"), std::make_pair("bottom", "right"), std::make_pair("top", "left"), std::make_pair("top", "left") }) == std::vector<int> { 1, 4, 1, 1 }));
    // TEST_END

    // TEST
    assert((lock_keyboard.Attempt( { std::make_pair("top", "left"), std::make_pair("bottom", "right"), std::make_pair("bottom", "left"), std::make_pair("top", "left") }) == std::vector<int> { 1, 4, 3, 1 }));
    // TEST_END

    // TEST
    assert((lock_keyboard.Attempt( { std::make_pair("top", "left"), std::make_pair("bottom", "right"), std::make_pair("bottom", "left"), std::make_pair("bottom", "left") }) == std::vector<int> { 1, 4, 3, 3 }));
    // TEST_END
    // TEST
    assert((lock_keyboard.Attempt( { std::make_pair("bottom", "right"), std::make_pair("bottom", "right"), std::make_pair("bottom", "right"), std::make_pair("bottom", "right") }) == std::vector<int> { 4, 4, 4, 4 }));
    // TEST_END

    // TEST
    try {
        lock_keyboard.Attempt( { std::make_pair("top", "left"), std::make_pair("bottom", "right"), std::make_pair("bottom", "Left"), std::make_pair("bottom", "left") });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        lock_keyboard.Attempt( { std::make_pair("bottom", "right"), std::make_pair("bottom", "right"), std::make_pair("bottom", "top"), std::make_pair("bottom", "right") });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
    // TEST
    try {
        lock_keyboard.Attempt( { std::make_pair("bottom", "left") });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        lock_keyboard.Attempt( { std::make_pair("left", "left") });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        lock_keyboard.Attempt( { std::make_pair("top", "top") });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        assert((lock_keyboard.Attempt( { }) == std::vector<int> { 1, 4, 3, 3 }));
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_EN
}

