/***
 * Prompt:


 khaled_cpp_71-2024_May_04: 6bb3cdb1-8548-4b5b-89f0-b98424d0bd28

 func_GroupByLength_khaled_cpp_71-2024_May_04


 Design a C++ function called GroupByLength, it will accept one input called lines of type std::vector<std::string>. This function should return number of type int that represent how many groups that we can form from the input list based on string lengths in the list. Please note that we need to trim the spaces from the beginning and the end of the string and replace all 2 or more continuous spaces into 1 single space. Last note is that the input list can't be empty and each line in the input list can't be empty as well.


 */

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

int GroupByLength(const std::vector<std::string> &lines) {
    if (lines.empty()) {
        throw std::invalid_argument("lines list can't be empty");
    }

    std::map<int, int> freq;

    for (const std::string &line : lines) {
        std::stringstream stringstreamer;
        std::string tmp = "", parsed_line = "";
        stringstreamer << line;

        int idx = 0;
        while (stringstreamer >> tmp) {
            if (idx++) {
                parsed_line += " " + tmp;
            } else {
                parsed_line += tmp;
            }
        }

        if (parsed_line.length() < 1) {
            throw std::invalid_argument("line can't be empty");
        }

        freq[parsed_line.length()]++;
    }

    return freq.size();
}

#include <cassert>
int main() {
    // TEST
    assert(GroupByLength( { "test", "string" }) == 2);
    // TEST_END

    // TEST
    assert(GroupByLength( { "test", "four" }) == 1);
    // TEST_END

    // TEST
    assert(GroupByLength( { " 1", "four" }) == 2);
    // TEST_END

    // TEST
    assert(GroupByLength( { " 1 ", "5" }) == 1);
    // TEST_END

    // TEST
    assert(GroupByLength( { " 1   3  ", "te" }) == 2);
    // TEST_END

    // TEST
    assert(GroupByLength( { " 1   3  ", "te", "1" }) == 3);
    // TEST_END

    // TEST
    assert(GroupByLength( { "  2", "44" }) == 2);
    // TEST_END

    // TEST
    assert(GroupByLength( { "a a  2", "ok ab" }) == 1);
    // TEST_END

    // TEST
    try {
        GroupByLength( { "", "four" });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        GroupByLength( { });
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}

