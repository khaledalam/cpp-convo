/***






 khaled_cpp_156_2024_May_26: 2884c9b1-ee8c-4d64-8c89-52743a58c633

 func_MonthsToCyberpunk2080_khaled_cpp_156_2024_May_26





Create a C++ function called MonthsToCyberpunk2080 that takes 2 inputs std::string current_month, and int
months_to_release

The game Cyberpunk 2080 will appear after exactly k months. At the moment is the month number s.

All the twelve months in our calendar are named using their usual English names: January, February, March, April,
May, June, July, August, September, October, November, December.

This function should return another text of type std::string that represent what month Cyberpunk 2080 will appear? Please don't forget to validate the input.





*/

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

std::string MonthsToCyberpunk2080(std::string current_month, int months_to_release) {
    if (months_to_release < 0) {
        throw std::invalid_argument("months_to_release can't be less than 0");
    }

    std::map<int, std::string> months_of_the_year;

    months_of_the_year[0] = "January";
    months_of_the_year[1] = "February";
    months_of_the_year[2] = "March";
    months_of_the_year[3] = "April";
    months_of_the_year[4] = "May";
    months_of_the_year[5] = "June";
    months_of_the_year[6] = "July";
    months_of_the_year[7] = "August";
    months_of_the_year[8] = "September";
    months_of_the_year[9] = "October";
    months_of_the_year[10] = "November";
    months_of_the_year[11] = "December";

    bool flag = false;
    std::pair<int, std::string> current_month_aux;

    for (auto item : months_of_the_year) {
        if (item.second == current_month) {
            flag = true;
            current_month_aux = item;
            break;
        }
    }

    if (!flag) {
        throw std::invalid_argument("current_month is invalid");
    }

    int pln = ((current_month_aux.first) + months_to_release) % 12;

    return months_of_the_year[pln];
}

#include <cassert>
int main() {
    // TEST
    assert(MonthsToCyberpunk2080("November", 3) == "February");
    // TEST_END

    // TEST
    assert(MonthsToCyberpunk2080("May", 24) == "May");
    // TEST_END

    // TEST
    assert(MonthsToCyberpunk2080("May", 0) == "May");
    // TEST_END

    // TEST
    try {
        MonthsToCyberpunk2080("May", -1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MonthsToCyberpunk2080("", 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MonthsToCyberpunk2080("m@y", 1);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}