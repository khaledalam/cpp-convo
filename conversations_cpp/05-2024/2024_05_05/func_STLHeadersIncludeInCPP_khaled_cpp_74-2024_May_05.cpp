/***
 * Prompt:

 khaled_cpp_74-2024_May_05: 962200f6-c81d-4c38-a4de-346b4dffc3af


 func_STLHeadersIncludeInCPP_khaled_cpp_74-2024_May_05

 Design a C++ function called STLHeadersIncludeInCPP, it will accept empty or non-empty input called line_of_code of type std::string which represent one line of code in a C++ source code file. Please make this function to return a boolean true if this line is a valid "header include" line of STL C++ container headers otherwise return false. Please assume that we have only 3 containers in C++ which are "map", "vector" and "set". Also please consider that the valid "header include" line can consist of different formats, it should follow this flow:
 - the line can contains trailing and leading spaces
 - the line should start with "#include"
 - header word should start with less than symbol "<" then the container name then greater than symbol ">"
 - there can be no-space, one or multiple spaces between "#include" and header word
 - there should not be any spaces between both symbols "<" and ">" and the container name

 Examples of valid "header include" lines:
 - "#include <map>"
 - "#include <map> "
 - "#include   <map>"

 Examples of invalid "header include" lines:
 - "#includ e <map>"
 - "#include < map> "
 - "#include   <map >"


 */

#include <stdexcept>

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

bool STLHeadersIncludeInCPP(std::string line_of_code) {

    std::vector<std::string> containers = { "vector", "set", "map" };

    Trimmer(line_of_code);

    if (line_of_code.length() > 8) {
        if (line_of_code.substr(0, 8) == std::string("#include")) {
            line_of_code.erase(0, 8);

            std::string header = "";
            std::stringstream string_streamer;
            string_streamer << line_of_code;
            string_streamer >> header;

            Trimmer(header);

            if (header.length() > 2 && header[0] == '<' && header[header.length() - 1] == '>') {
                header.erase(0, 1);
                header.pop_back();
                if (std::find(containers.begin(), containers.end(), header) != containers.end()) {
                    return true;
                }
            }
        }
    }

    return false;
}

#include <cassert>
int main() {
    // TEST
    assert(STLHeadersIncludeInCPP("#include <map>") == true);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include < set>") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include < set >") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include <vector >") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP(" #include <set>") == true);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP(" #include <set>  ") == true);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include <set> ") == true);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include   <  map>") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include    <set>") == true);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("# include <set>") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#includ e <set>") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include< set>") == false);
    // TEST_END

    // TEST
    assert(STLHeadersIncludeInCPP("#include<vector>") == true);
    // TEST_END
}

