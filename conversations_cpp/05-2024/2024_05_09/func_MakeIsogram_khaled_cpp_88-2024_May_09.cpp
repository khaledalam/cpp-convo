/***
 * Prompt:




 khaled_cpp_89-2024_May_09: 

 Create a C++ function called MakeIsogram which accepts non-empty input called
 text of type std:string, this input can be any character. Please make this
 function return another isogram string of type std::string. Please note that an
 isogram string is a string that does not contain any duplicated characters, if
 you have some duplicated characters, leave the first character of them and
 remove the others.


 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_set>

std::string MakeIsogram(const std::string &text) {
    if (text.empty()) {
        throw std::invalid_argument("text can't be empty");
    }

    std::unordered_set<char> char_set;
    std::string result = "";

    for (const char &character : text) {
        if (char_set.find(character) == char_set.end()) {
            char_set.insert(character);
            result += character;
        }
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(MakeIsogram("test") == std::string("tes"));
    // TEST_END

    // TEST
    assert(MakeIsogram("@122") == std::string("@12"));
    // TEST_END

    // TEST
    assert(MakeIsogram("aa") == std::string("a"));
    // TEST_END

    // TEST
    assert(MakeIsogram("programming") == std::string("progamin"));
    // TEST_END

    // TEST
    assert(MakeIsogram("aabbcaz") == std::string("abcz"));
    // TEST_END

    // TEST
    try {
        MakeIsogram("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
