/***
 * Prompt:




 	
khaled_cpp_88-2024_May_09: 


 Create me a C++ function called GetAverageWordLength that takes a string called sentence of type std::string, this sentence containing words separated by spaces. Please make this function return the average length of the words of the input, the average length of the words of some sentence is the count of words divided by the total length of the words in this sentence. Please also note that the sentence can't be empty and EPS value is 1e-9 for doubles comparing.


 */


#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

double GetAverageWordLength(const std::string &sentence) {
    if (sentence.empty()) {
        throw std::invalid_argument("sentence can't be empty");
    }

    std::istringstream iss(sentence);
    std::string word;
    double totalLength = 0;
    double wordCount = 0;
    while (iss >> word) {
        totalLength += word.length();
        wordCount++;
    }
    if (wordCount == 0) {
        return 0;
    }

    return totalLength / wordCount;
}

#include <cassert>
int main() {
    // TEST
    assert(GetAverageWordLength("The quick brown fox") - 4.0 < 1e-9);
    // TEST_END

    // TEST
    assert(GetAverageWordLength("C++ programming is fun") - 4.75 < 1e-9);
    // TEST_END

    // TEST
    assert(GetAverageWordLength("test") - 4.0 < 1e-9);
    // TEST_END

    // TEST
    assert(GetAverageWordLength("test test") - 4.0 < 1e-9);
    // TEST_END

    // TEST
    assert(GetAverageWordLength("tes test") - 3.5 < 1e-9);
    // TEST_END

    // TEST
    assert(GetAverageWordLength("A @1") - 1.5 < 1e-9);
    // TEST_END

    // TEST
    assert(GetAverageWordLength("z") - 1.0 < 1e-9);
    // TEST_END

    // TEST
    try {
        GetAverageWordLength("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
