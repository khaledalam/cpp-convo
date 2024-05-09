/***
 * Prompt:




 khaled_cpp_22_2024_20_04: 593cd789-62f3-4a84-bc2d-fe70708b2ca5


 class_SpamHandle_khaled_cpp_22_2024_20_04




 Write me a C++ class named SpamHandle, this class will include a function called SpamSafe. The function accepts two inputs called message of type std:string that consists of empty or non-empty lines of sentences each line ends with "\n", and levels of type std::map<std::string, int> which represents a list of pairs for the weight of each spam word. This function should return a boolean true if there is at least one line where the sum of all spam words' weight in it is greater than 100, Please note that each word in the first argument of levels pairs should be a non-empty string that all its characters lowercase or uppercase, not allow mixed upper and lower cases. Also, remove dots from the end of words in the message and if some words existed twice in the levels with different case sensitivity use any of them. Don't forget to validate inputs.


 */

#include <stdexcept>
#include <string>
#include <sstream>
#include <map>
#include <iostream>
#include <algorithm>

class SpamHandle {
public:
    bool SpamSafe(std::string message, std::map<std::string, int> levels) {
        std::stringstream ss(message);
        std::string to;

        for (const std::pair<std::string, int> &level : levels) {
            std::string a = level.first, b = level.first;

            if (a.empty()) {
                throw std::invalid_argument("level can't be empty");
            }

            std::transform(a.begin(), a.end(), a.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            std::transform(b.begin(), b.end(), b.begin(), [](unsigned char c) {
                return std::toupper(c);
            });

            if (level.first != a && level.first != b) {
                throw std::invalid_argument("all characters should be lowercase or uppercase in level's pairs");
            }
        }

        while (std::getline(ss, to, '\n')) {

            int level = 0;

            std::stringstream line_ss(to);
            std::string word;

            while (line_ss >> word) {

                if (word[word.length() - 1] == '.') {
                    word.erase(word.end() - 1);
                }

                std::string word_upper = word, word_lower = word;

                std::transform(word_lower.begin(), word_lower.end(), word_lower.begin(), [](unsigned char c) {
                    return std::tolower(c);
                });

                std::transform(word_upper.begin(), word_upper.end(), word_upper.begin(), [](unsigned char c) {
                    return std::toupper(c);
                });

                if (levels.find(word) != levels.end()) {
                    level += levels[word];
                } else {
                    int level_val = levels[word_upper];
                    if (!level_val) {
                        level_val = levels[word_lower];
                    }
                    level += level_val;
                }

                if (level > 100) {
                    return false;
                }
                word = "";
            }
        }

        return true;
    }
};

#include <cassert>
int main() {
    SpamHandle spam_handle;

    // TEST
    std::string input1 = std::string("This is test.\nAnd this is a new line");
    std::map<std::string, int> input2 = { std::make_pair("is", 60) };
    bool output = true;
    assert(spam_handle.SpamSafe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = std::string("This is test.\nAnd this is a new line");
    input2 = { std::make_pair("is", 60), std::make_pair("test", 50), };
    output = false;
    assert(spam_handle.SpamSafe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = std::string("This is NEW test.\nAnd this is a new line");
    input2 = { std::make_pair("is", 1), std::make_pair("new", 99), std::make_pair("NEW", 90) };
    output = true;
    assert(spam_handle.SpamSafe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = std::string("This is test.\n\nTest");
    input2 = { std::make_pair("TEST", 101) };
    output = false;
    assert(spam_handle.SpamSafe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = std::string("This is test.\nAnd this is a new line");
    input2 = { };
    output = true;
    assert(spam_handle.SpamSafe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = std::string("");
    input2 = { std::make_pair("is", 60) };
    output = true;
    assert(spam_handle.SpamSafe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = std::string("");
    input2 = { };
    output = true;
    assert(spam_handle.SpamSafe(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = std::string("Test.\nok.");
    input2 = { std::make_pair("NeW", 90) };
    try {
        spam_handle.SpamSafe(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = std::string("Test");
    input2 = { std::make_pair("", 90) };
    try {
        spam_handle.SpamSafe(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
