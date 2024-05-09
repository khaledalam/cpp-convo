/***
 * Prompt:




 khaled_cpp_79-2024_May_07: 6cdff2f8-bdb9-4e92-882f-9c52cf42b3ed


 class_FileHelper_GroupByExt_khaled_cpp_79-2024_May_07

 Design a C++ class called FileHelper. This class contains a method member called GroupByExt, it accepts one input called files_names of type std::vector<std::string>. This method should return a number of type int that represents how many file extensions of these file names list. Please note that file extension should be only uppercase, lowercase, or mixed between uppercase and lowercase letters with a prefix of dot(".") and you can ignore the validation of the empty or non-empty file name. Also don't forget to validate the inputs.


 */

#include <stdexcept>
#include <string>
#include <map>
#include <regex>
#include <iostream>

class FileHelper {
public:
    int GroupByExt(std::vector<std::string> files_names) {

        std::map<std::string, int> freq;

        for (const std::string &file_name : files_names) {
            std::string ext = "";

            if (count(file_name.begin(), file_name.end(), '.') < 1) {
                throw std::invalid_argument("file name has no dot");
            }

            for (int idx = 0; idx < file_name.length(); idx++) {
                if (file_name[idx] == '.') {
                    ext = "";
                } else {
                    ext += file_name[idx];
                }
            }

            if (ext.empty()) {
                throw std::invalid_argument("file name can't be empty");
            }

            for (const char &character : ext) {
                if (!isalpha(character)) {
                    throw std::invalid_argument("Invalid file name characters");
                }
            }

            ++freq[ext];
        }

        return freq.size();
    }
};

#include <cassert>
int main() {
    FileHelper file_helper;

    // TEST
    assert(file_helper.GroupByExt( { std::string("test.pdf"), std::string("test.jpg") }) == 2);
    // TEST_END

    // TEST
    assert(file_helper.GroupByExt( { std::string("test.pdf"), std::string("test.pdf") }) == 1);
    // TEST_END

    // TEST
    assert(file_helper.GroupByExt( { std::string(".pdf"), std::string(".txt"), std::string("a.png") }) == 3);
    // TEST_END

    // TEST
    assert(file_helper.GroupByExt( { std::string("a.y"), std::string(".a"), std::string("y.a") }) == 2);
    // TEST_END

    // TEST
    assert(file_helper.GroupByExt( { }) == 0);
    // TEST_END

    // TEST
    try {
        file_helper.GroupByExt( { std::string("test."), std::string("test.jpg") });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        file_helper.GroupByExt( { std::string(".."), std::string("test.jpg") });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        file_helper.GroupByExt( { std::string("") });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        file_helper.GroupByExt( { std::string("test") });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        file_helper.GroupByExt( { std::string(".123") });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        file_helper.GroupByExt( { std::string(".@") });
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}

