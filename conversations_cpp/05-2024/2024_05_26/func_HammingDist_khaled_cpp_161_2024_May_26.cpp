/***






 khaled_cpp_161_2024_May_26: 2340cf4e-9211-4dbe-8f86-34636d571725


func_HammingDist_khaled_cpp_161_2024_May_26

Create a C++ function called HammingDist that takes non-empty two text inputs of type std::string called first and
second, the length of both of them should be between 1 and 100000, and each character should be '0' or '1'.


The length of some string s is denoted |s|. The Hamming distance between two strings s and t of equal length is defined
as:

n∑x=|si-ti|

where n = |s| and x => i=1 , and where si is the i-th character of s and ti is the i-th character of t. For example,
the Hamming distance between string "0011" and string "0110" is
|0 - 0| + |0 - 1| + |1 - 1| + |1 - 0| = 0 + 1 + 0 + 1 = 2.


This function should return a number of type int that represent the sum of the Hamming distances between the first input and
all contiguous substrings of the second input of length |first|. Please don't forget to validate the input.





*/

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <string.h>

const int maxn = 1e5 + 7;
int frame[maxn][2];

int HammingDist(std::string first, std::string second) {
    memset(frame, 0, sizeof frame); 

    if (first.empty() || second.empty()) {
        throw std::invalid_argument("first and second can't be empty");
    }

    if (first.length() > 100000 || second.length() > 100000) {
        throw std::invalid_argument("first and second lengths should be between 1 and 100000");
    }

    for (const char character : first) {
        if (character != '0' && character != '1') {
            throw std::invalid_argument("only allow '1' and '0' in first input");
        }
    }

    for (const char character : second) {
        if (character != '0' && character != '1') {
            throw std::invalid_argument("only allow '1' and '0' in second input");
        }
    }

    for (int idx = 1; idx <= second.length(); idx++) {
        for (int jdx = 0; jdx < 2; jdx++) {
            frame[idx][jdx] += frame[idx - 1][jdx];
        }
        frame[idx][second[idx - 1] - '0']++;
    }

    int ans = 0;
    for (int idx = 0; idx < first.length(); idx++) {
        for (int jdx = 0; jdx < 2; jdx++) {
            ans += abs((first[idx] - '0') - jdx) *
                   (frame[second.length() - first.length() + idx + 1][jdx] - frame[idx][jdx]);
        }
    }

    return ans;
}

#include <cassert>
int main() {
    // TEST
    assert(HammingDist("01", "00111") == 3);
    // TEST_END

    // TEST
    assert(HammingDist("0011", "0110") == 2);
    // TEST_END

    // TEST
    try {
        HammingDist("", "");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        HammingDist("g", "#");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        HammingDist(std::string("1", 100001), "0");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}