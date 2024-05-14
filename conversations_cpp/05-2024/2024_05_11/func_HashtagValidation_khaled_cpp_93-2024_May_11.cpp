/***
 * Prompt:




 khaled_cpp_93-2024_May_11: 7a388e93-6fbb-4253-b94a-46e018ddbee1

func_HashtagValidation_khaled_cpp_93-2024_May_11

 Create me a C++ function called HashtagValidation which accepts two inputs, The first input non-empty string called post of type std::string which can contain any type of characters including spaces and special characters, the second input is zero or positive number called max_hashtags_count of type int which represent the max count of hashtag words that allow in the post. Please note that hashtag word is the a word that has length of 2 or more and starts with hashtag symbol and there are no spaces between hashtag symbol and first character in the word so e.g. "#test" is a valid hashtag word but "# test" is not a hashtag word. Please make this function return a Boolean true if the post contains at most max_hashtags_count of valid hashtag words otherwise return false. Please also validate the inputs.




 */

#include <algorithm>

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

bool HashtagValidation(const std::string &post, int max_hashtags_count) {
    if (post.empty()) {
        throw std::invalid_argument("post can't be empty");
    }

    if (max_hashtags_count < 0) {
        throw std::invalid_argument("max_hashtags_count can't be less than 0");
    }

    std::stringstream stringstreamer;
    std::string word;

    stringstreamer << post;

    int hashtags_count = 0;

    while (stringstreamer >> word) {
        if (word.length() > 1 && word[0] == '#') {
            hashtags_count++;
        }

        if (hashtags_count > max_hashtags_count) {
            return false;
        }
    }

    return hashtags_count <= max_hashtags_count;
}

#include <cassert>
int main() {
    // TEST
    assert(HashtagValidation("This is #post", 1) == true);
    // TEST_END

    // TEST
    assert(HashtagValidation("This #is #post", 1) == false);
    // TEST_END

    // TEST
    assert(HashtagValidation("This is #post #", 1) == true);
    // TEST_END

    // TEST
    assert(HashtagValidation("This is # post #", 0) == true);
    // TEST_END

    // TEST
    assert(HashtagValidation("This is #post #", 0) == false);
    // TEST_END

    // TEST
    assert(HashtagValidation("###", 1) == true);
    // TEST_END

    // TEST
    assert(HashtagValidation("## #", 1) == true);
    // TEST_END

    // TEST
    assert(HashtagValidation("## # #@", 1) == false);
    // TEST_END

    // TEST
    assert(HashtagValidation("## # #@", 2) == true);
    // TEST_END

    // TEST
    try {
        HashtagValidation("", 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        HashtagValidation("test", -1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
