/***
 * Prompt:




 khaled_cpp_95-2024_May_11: 177452b8-c581-4455-9659-0924a2d0f65f


func_CanInstallApp_khaled_cpp_95-2024_May_11

 Create me a C++ function called CanInstallApp which accepts two inputs, the first input is a non-empty list called system_ext of type std::vector<std::string> each string in the list represents if system ext is enabled or not, system ext is enabled if it doesn't has semicolon as prefix and it form in this pattern ext-{name_of_ext} where {name_of_ext} is some non empty string represent the pure ext name, second input called app_ext_requires of type std::vector<std::string> each string represent non-empty pure name of ext. This function should return a Boolean true if all app_ext_requires list are enabled in the system otherwise return false. Please note that if the same ext appears multiple times in the system_ext list and has one or more disabled ext(has semicolon as prefix) that means this ext is considered as disabled even if all other occurs are enabled. Please don't forget to validate the inputs.




 */

#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

bool CanInstallApp(const std::vector<std::string> &system_ext, const std::vector<std::string> &app_ext_requires) {
    if (system_ext.empty()) {
        throw std::invalid_argument("system_ext can't be empty");
    }

    if (app_ext_requires.empty()) {
        throw std::invalid_argument("app_ext_requires can't be empty");
    }

    std::map<std::string, bool> enabled;

    for (std::string line : system_ext) {

        if (line.length() < 5) {
            throw std::invalid_argument("invalid system ext format");
        }

        std::string prefix = line.substr(0, 5);
        std::string prefix_short = line.substr(0, 4);

        if (prefix == ";ext-") {
            enabled[line.substr(5)] = false;
        } else if (prefix_short == "ext-") {
            if (enabled.find(line.substr(4)) == enabled.end()) {
                enabled[line.substr(4)] = true;
            } else {
                enabled[line.substr(4)] &= true;
            }
        } else {
            throw std::invalid_argument("invalid system ext format-");
        }

        std::stringstream stringstreamer;
        std::string word;

        std::replace(line.begin(), line.end(), '-', ' ');

        stringstreamer << line;
        stringstreamer >> word;
        word = "";
        stringstreamer >> word;
        if (word.empty()) {
            throw std::invalid_argument("invalid required ext format-");
        }
    }

    for (const std::string &ext : app_ext_requires) {
        if (ext.empty()) {
            throw std::invalid_argument("invalid require ext format");
        }

        if (!enabled[ext]) {
            return false;
        }
    }

    return true;
}

#include <cassert>
int main() {
    // TEST
    assert(CanInstallApp({";ext-mysql"}, {"mysql"}) == false);
    // TEST_END

    // TEST
    assert(CanInstallApp({"ext-mysql"}, {"mysql"}) == true);
    // TEST_END

    // TEST
    assert(CanInstallApp({"ext-mysql"}, {"mysql", "zip"}) == false);
    // TEST_END

    // TEST
    assert(CanInstallApp({"ext-mysql", ";ext-mysql"}, {"mysql"}) == false);
    // TEST_END

    // TEST
    assert(CanInstallApp({";ext-mysql", "ext-mysql"}, {"mysql"}) == false);
    // TEST_END

    // TEST
    try {
        CanInstallApp({""}, {"mysql"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({"ext-mysql"}, {""});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({"ext-mysql"}, {""});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({}, {"mysql"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({"ext-mysql"}, {});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({}, {});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({"test-mysql"}, {"mysql"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({";ext- "}, {"mysql"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanInstallApp({"ext- "}, {"mysql"});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
