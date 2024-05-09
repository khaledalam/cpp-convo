/***
 * Prompt:




 khaled_cpp_80-2024_May_08: 1ff30094-4d26-4012-bb91-a17229d9d37c

 class_FileHelper_CanForm_khaled_cpp_80-2024_May_08


 Design a C++ class called FileHelper. This class contains a method member called CanForm, which accepts two inputs, first one is a non-empty string called digits of type std::string which consists of digits only, second one is zero or positive input called number of type int. This method should return a boolean true if we can get a sum of digits from the first input which is greater than or equal to the second input number. Please don't forget to validate the inputs.


 */

#include <stdexcept>
#include <string>
#include <iostream>

class FileHelper {
public:
    bool CanForm(std::string digits, int number) {
        int sum = 0;

        if (digits.empty()) {
            throw std::invalid_argument("digits input can't be empty");
        }

        if (number < 0) {
            throw std::invalid_argument("number should be zero or positive");
        }

        for (const char &digit : digits) {
            if (!isdigit(digit)) {
                throw std::invalid_argument("invalid character");
            }

            sum += (digit - '0');

            if (sum >= number) {
                return true;
            }
        }

        return sum >= number;
    }
};

#include <cassert>
int main() {
    FileHelper file_helper;

    // TEST
    assert(file_helper.CanForm(std::string("123"), 3) == true);
    // TEST_END

    // TEST
    assert(file_helper.CanForm(std::string("42"), 6) == true);
    // TEST_END

    // TEST
    assert(file_helper.CanForm(std::string("51"), 7) == false);
    // TEST_END

    // TEST
    assert(file_helper.CanForm(std::string("0"), 0) == true);
    // TEST_END

    // TEST
    assert(file_helper.CanForm(std::string("01"), 0) == true);
    // TEST_END

    // TEST
    try {
        file_helper.CanForm(std::string("-1"), 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        file_helper.CanForm(std::string("1"), -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        file_helper.CanForm(std::string("a"), -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}

