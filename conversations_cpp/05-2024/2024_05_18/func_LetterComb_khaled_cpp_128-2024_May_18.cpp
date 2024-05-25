/***
 * Prompt:




 khaled_cpp_128-2024_May_18: 2c97b984-452b-4cdd-ab70-acdd982718a4

 func_LetterComb_khaled_cpp_128-2024_May_18


Create a C++ function called LetterComb that takes one non-empty string called str that contains digits from 2-9 inclusive. This function should return an array of strings of type std::vector<std::string> that represent all possible letter combinations that the number could represent. Return the answer in any order. A mapping of digits to letters (just like on the telephone buttons). Note that 1 does not map to any letters. Don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string GetCharsFromDigit(char d) {
    std::string rev;
    for (int i = 0; i < ((d == '7' || d == '9') ? 4 : 3); i++) {
        rev += (d + 47 + (2 * ((d - '0') - 2)) + i + (d > '7' ? 1 : 0));
    }

    return rev;
}

bool CheckInvalidOption(int character) { return !isdigit(character) || character == '0' || character == '1'; }

std::vector<std::string> LetterComb(std::string str) {
    if (str.empty()) {
        throw std::invalid_argument("str can't be empty");
    }

    str.erase(std::remove_if(str.begin(), str.end(), CheckInvalidOption), str.end());

    std::vector<std::string> rev{""};

    for (int xdx = 0; xdx < str.size(); xdx++) {
        std::string charsFromDigit = GetCharsFromDigit(str[xdx]);

        std::vector<std::string> r_aux;

        for (int ydx = 0; ydx < charsFromDigit.size(); ydx++) {
            for (int zdx = 0; zdx < rev.size(); zdx++) {
                r_aux.push_back(rev[zdx] + charsFromDigit[ydx]);
            }
        }

        rev = r_aux;
    }

    std::sort(rev.begin(), rev.end());

    if (rev[0] == "") {
        rev.clear();
    }

    return rev;
}

#include <cassert>
int main() {
    // TEST
    assert((LetterComb("2") == std::vector<std::string>{"a", "b", "c"}));
    // TEST_END

    // TEST
    assert((LetterComb("21") == std::vector<std::string>{"a", "b", "c"}));
    // TEST_END

    // TEST
    assert((LetterComb("1*A----01Z") == std::vector<std::string>{}));
    // TEST_END

    // TEST
    assert((LetterComb("1*A----01Z2") == std::vector<std::string>{"a", "b", "c"}));
    // TEST_END

    // TEST
    assert((LetterComb("23") == std::vector<std::string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}));
    // TEST_END

    // TEST
    assert((LetterComb("2-3") == std::vector<std::string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}));
    // TEST_END

    // TEST
    assert((LetterComb("2 @ 3") == std::vector<std::string>{"ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"}));
    // TEST_END

    // TEST
    assert((LetterComb("92") == std::vector<std::string>{"wa", "wb", "wc", "xa", "xb", "xc", "ya", "yb", "yc", "za", "zb", "zc"}));
    // TEST_END

    // TEST
    assert((LetterComb("456") == std::vector<std::string>{"gjm", "gjn", "gjo", "gkm", "gkn", "gko", "glm", "gln", "glo",
                                                          "hjm", "hjn", "hjo", "hkm", "hkn", "hko", "hlm", "hln", "hlo",
                                                          "ijm", "ijn", "ijo", "ikm", "ikn", "iko", "ilm", "iln", "ilo"}));
    // TEST_END

    // TEST
    try {
        LetterComb("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
