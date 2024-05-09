/***
 * Prompt:




 khaled_cpp_33_2024_23_04: 6cefb029-bbda-4fef-8170-5840f4465f7c


 Design a C++ class called CheckSum. This class contains a method member called GetValue, it accepts two inputs, first input called content of type std::string, second input called key of type std::pair<int, int>, both values in second input pair should be positive number grater than zero. This method should return number of type long long that represent custom checksum value based on this formula: The sum of the ascii values of each character in the content plus the multiplication of the first argument of the second input pair by the length of the content input. Please Don't forget to return the result mod the second argument of the second input pair. Also don't forget to validate the inputs.


 */

#include <stdexcept>
#include <string>
#include <iostream>

class CheckSum {
public:
    long long GetValue(std::string content, std::pair<int, int> key) {
        long long result = 0;

        if (key.first <= 0 || key.second <= 0) {
            throw std::invalid_argument("Key values should be positive number greater than zero");
        }

        for (const char &ch : content) {
            result += int(ch);
        }

        result += (key.first * content.length());

        result %= key.second;

        return result;
    }
};

#include <cassert>
int main() {
    CheckSum checksum;

    // TEST
    assert(checksum.GetValue(std::string("123"), std::pair<int, int> { 1, 5 }) == checksum.GetValue(std::string("123"), std::pair<int, int> { 1, 5 }));
    // TEST_END

    // TEST
    assert(checksum.GetValue(std::string("abc"), std::pair<int, int> { 72, 72 + 82 }) == checksum.GetValue(std::string("efg"), std::pair<int, int> { 72 + 82, 72 }));
    // TEST_END

    // TEST
    assert(checksum.GetValue(std::string("3"), std::pair<int, int> { 1, 3 }) == checksum.GetValue(std::string("1"), std::pair<int, int> { 2, 2 }));
    // TEST_END

    // TEST
    assert(checksum.GetValue(std::string("0"), std::pair<int, int> { 1, 1 }) == checksum.GetValue(std::string("1"), std::pair<int, int> { 1, 2 }));
    // TEST_END

    // TEST
    assert(checksum.GetValue(std::string("1"), std::pair<int, int> { 2, 4 }) != checksum.GetValue(std::string("1"), std::pair<int, int> { 3, 2 }));
    // TEST_END

    // TEST
    try {
        checksum.GetValue(std::string("1"), std::pair<int, int> { -1, 7 });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        checksum.GetValue(std::string("1"), std::pair<int, int> { 0, 0 });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        checksum.GetValue(std::string("1"), std::pair<int, int> { 0, 7 });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        checksum.GetValue(std::string("1"), std::pair<int, int> { 1, -7 });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}

