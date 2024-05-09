/***
 * Prompt:




 khaled_cpp_21_2024_20_04: 3ace393b-ef7a-48d4-9444-98d516b812af







 Create a C++ class named Progressbar, this class will include a method called Percentage. The method accepts an input called bar of type std:string which represents the progress bar string that consists of dot "." and bars "|". Bar "|" represents a done progress and Dot "." represents a remain progress. This method should returns number of type float that represent the done progress percentage. Please note that Bars should comes before Dots and it's impossible to have Dots between Bars. The EPSILON for compare percentage correctness is 0.1, don't forget to validate inputs.


 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

class Progressbar {
public:
    float Percentage(std::string bar) {
        float length = bar.length();

        if (length < 1) {
            return 0;
        }

        int last_bar = -1, first_dot = 1e9;

        int idx = 0;
        for (const char &character : bar) {
            if (character != '|' && character != '.') {
                throw std::invalid_argument("Not allowed characters");
            }

            if (character == '|') {
                last_bar = idx;
            }

            if (character == '.' && first_dot == 1e9) {
                first_dot = idx;
            }

            idx++;
        }

        if (first_dot < last_bar) {
            throw std::invalid_argument("Input format is invalid");
        }

        float bars = std::count(bar.begin(), bar.end(), '|');

        return (bars / length) * 100;
    }
};

#include <cassert>
int main() {
    Progressbar progressbar;
    float EPSILON = 0.1;

    // TEST
    std::string input = std::string("||.");
    float output = 66.6;
    assert(progressbar.Percentage(input) - output < EPSILON);
    // TEST_END

    return 0;

    // TEST
    input = std::string("||...");
    output = 40;
    assert(progressbar.Percentage(input) - output < EPSILON);
    // TEST_END

    // TEST
    input = std::string("");
    output = 0;
    assert(progressbar.Percentage(input) - output < EPSILON);
    // TEST_END

    // TEST
    input = std::string("..");
    output = 0;
    assert(progressbar.Percentage(input) - output < EPSILON);
    // TEST_END

    // TEST
    input = std::string("||");
    output = 100;
    assert(progressbar.Percentage(input) - output < EPSILON);
    // TEST_END

    // TEST
    input = std::string("|||.||..");
    try {
        progressbar.Percentage(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input = std::string("..||");
    try {
        progressbar.Percentage(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input = std::string("|F..");
    try {
        progressbar.Percentage(input);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
