/***
 * Prompt:




 khaled_cpp_115-2024_May_17: 4183a754-b2bd-4e9e-8b34-d579f433a653

 func_ExpandEncoded_khaled_cpp_115-2024_May_17

Design a C++ function called ExpandEncoded that takes a non-empty string of type std::string that follows this exact pattern "number[string]", the number part should be greater than zero and the string part can contain any type of characters including spaces and special characters. This function should return another string of type std::string which represents an expanded string. For example, "2[a]" should return "aa" and "3[b]2[bc]" should return "b]2[bcb]2[bcb]2[bc". Please don't forget to validate the input.




 */

#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>

std::string ExpandEncoded(std::string str) {
    if (str.empty()) {
        throw std::invalid_argument("str can't be empty");
    }

    if (str.back() != ']') {
        throw std::invalid_argument("str is missing ]");
    }

    if (str.find('[') == std::string::npos) {
        throw std::invalid_argument("str is missing [");
    }

    str[str.length() - 1] = ' ';

    int idx = 0;
    for (char &character : str) {
        idx++;
        if (character == '[') {
            character = ' ';
            break;
        }
    }

    std::stringstream stringstreamer;

    stringstreamer << str;
    int count;
    stringstreamer >> count;

    if (count < 1) {
        throw std::invalid_argument("number should be greater than 0");
    }

    std::string tmp = "", result = "";
    for (int idxx = idx; idxx < str.length() - 1; idxx++) {
        tmp += str[idxx];
    }

    if (tmp.empty()) {
        throw std::invalid_argument("string should not be empty");
    }

    for (size_t idx = 0; idx < count; idx++) {
        result += tmp;
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert(ExpandEncoded("3[b]2[bc]") == std::string("b]2[bcb]2[bcb]2[bc"));
    // TEST_END

    // TEST
    assert(ExpandEncoded("3[b2[bc]") == std::string("b2[bcb2[bcb2[bc"));
    // TEST_END

    // TEST
    assert(ExpandEncoded("2[@bc]") == std::string("@bc@bc"));
    // TEST_END

    // TEST
    assert(ExpandEncoded("2[ ]") == std::string("  "));
    // TEST_END

    // TEST
    try {
        ExpandEncoded("");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ExpandEncoded("2[]");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ExpandEncoded("[abc]");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ExpandEncoded("-2[avc]");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ExpandEncoded("0[q]");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        ExpandEncoded("1[f[");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
