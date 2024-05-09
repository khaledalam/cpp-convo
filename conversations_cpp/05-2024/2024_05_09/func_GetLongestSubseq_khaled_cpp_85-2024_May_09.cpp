/***
 * Prompt:




 khaled_cpp_85-2024_May_09: b86b1779-9e23-4246-afb9-b67b8027bd4c


 func_GetLongestSubseq_khaled_cpp_85-2024_May_09

 Create me a C++ function called GetLongestSubseq that accepts two non-empty inputs, first one string called sequence of type std::string and second one called subsequence of type std::string subsequence. The function should find the length of the longest subsequence of a sequence that matches the subsequence in the same order but not necessarily contiguous. Please make this function return the number of type int that represents the length of the longest subsequence.


 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int GetLongestSubseq(const std::string &sequence, const std::string &subsequence) {

    if (sequence.empty() || subsequence.empty()) {
        throw std::invalid_argument("both inputs can't be empty");
    }

    int sequence_length = sequence.length();
    int subsequence_length = subsequence.length();

    std::vector<std::vector<int>> dynamic(sequence_length + 1, std::vector<int>(sequence_length + 1, 0));

    for (int idx = 1; idx <= sequence_length; idx++) {
        for (int jdx = 1; jdx <= subsequence_length; jdx++) {
            if (sequence[idx - 1] == subsequence[jdx - 1]) {
                dynamic[idx][jdx] = dynamic[idx - 1][jdx - 1] + 1;
            } else {
                dynamic[idx][jdx] = std::max(dynamic[idx - 1][jdx], dynamic[idx][jdx - 1]);
            }
        }
    }

    return dynamic[sequence_length][subsequence_length];
}

#include <cassert>
int main() {

    // TEST
    assert(GetLongestSubseq("abcde", "ace") == 3);
    // TEST_END

    // TEST
    assert(GetLongestSubseq("aa", "a") == 1);
    // TEST_END

    // TEST
    assert(GetLongestSubseq("Abc", "z") == 0);
    // TEST_END

    // TEST
    assert(GetLongestSubseq("a@c#OzA", "@vv#") == 2);
    // TEST_END

    // TEST
    assert(GetLongestSubseq("abCcdE", "aec") == 2);
    // TEST_END

    // TEST
    assert(GetLongestSubseq("abcde", "xyz") == 0);
    // TEST_END

    // TEST
    assert(GetLongestSubseq("Abcde", "a") == 0);
    // TEST_END

    // TEST
    assert(GetLongestSubseq("abcde", "a") == 1);
    // TEST_END

    // TEST
    try {
        GetLongestSubseq("", "abc");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        GetLongestSubseq("abc", "");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        GetLongestSubseq("", "");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
