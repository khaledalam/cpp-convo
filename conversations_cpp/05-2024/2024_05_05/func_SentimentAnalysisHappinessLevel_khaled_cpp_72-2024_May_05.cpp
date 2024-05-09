/***
 * Prompt:


 khaled_cpp_72-2024_May_05: 31d8ddf5-19f2-40fe-a34f-618b25896f8f

 func_SentimentAnalysisHappinessLevel_khaled_cpp_72-2024_May_05

 Design a C++ function called SentimentAnalysisHappinessLevel, it will accept one input called message of type std::string which consist of non-empty alphabetic characters and spaces only. This function should return number of type int that represent happiness level which refers to how many times happy words appears in the message. Please note that happy words are "happy", "ok", "cool", "wow" and "awesome". Also note that "OK" and "ok" are happy words.


 */
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int CountSubstring(const std::string &str, const std::string &sub) {
    if (sub.length() == 0) {
        return 0;
    }

    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos; offset = str.find(sub, offset + sub.length())) {
        ++count;
    }

    return count;
}

int SentimentAnalysisHappinessLevel(std::string message) {

    if (message.empty()) {
        throw std::invalid_argument("input shouldn't be empty");
    }

    for (const char &character : message) {
        if (!isalpha(character) && character != ' ') {
            throw std::invalid_argument("alphabetic characters only allowed");
        }
    }

    std::vector<std::string> happy_words = { "happy", "ok", "cool", "wow", "awesome" };

    std::transform(message.begin(), message.end(), message.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    int level = 0;
    for (const std::string &word : happy_words) {
        level += CountSubstring(message, word);
    }

    return level;
}

#include <cassert>
int main() {
    // TEST
    assert((SentimentAnalysisHappinessLevel(std::string("This is Happy text")) == 1));
    // TEST_END

    // TEST
    assert((SentimentAnalysisHappinessLevel(std::string("awesome awesomE is Happy text")) == 3));
    // TEST_END

    // TEST
    assert((SentimentAnalysisHappinessLevel(std::string("ok is Happy text")) == 2));
    // TEST_END

    // TEST
    assert((SentimentAnalysisHappinessLevel(std::string("cool")) == 1));
    // TEST_END

    // TEST
    assert((SentimentAnalysisHappinessLevel(std::string("wowwowWoW wOw")) == 4));
    // TEST_END

    // TEST
    assert((SentimentAnalysisHappinessLevel(std::string("test")) == 0));
    // TEST_END

    // TEST
    try {
        SentimentAnalysisHappinessLevel(std::string(""));
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SentimentAnalysisHappinessLevel("@test");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        SentimentAnalysisHappinessLevel("123");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

