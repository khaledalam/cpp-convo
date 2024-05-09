/***
 * Prompt:




 khaled_cpp_36_2024_23_04: 6d5e2bed-6700-413a-aa0c-d34f76ce477d

 class_DateHelper_khaled_cpp_36_2024_23_04

 Design a C++ class called DateHelper. This class contains a function member called IsValid, it accepts an input called dates of type of vector of strings. Each valid date should follow the format of yyyy-mm-dd, e.g. 1900-12-14. Please note that year can't be less that 1000 and spaces are not allowed. This function should return boolean true if all dates in input list are valid otherwise return false. Consider using regex in the solution and don't forget to validate the inputs.


 */

#include <stdexcept>

#include <vector>
#include <regex>
#include <algorithm>
#include <iostream>

class DateHelper {
public:
	bool IsValid(std::vector<std::string> dates) {
		if (dates.empty()) {
			return false;
		}

		for (std::string date : dates) {
			std::regex pattern("^(\\d{4})[-](\\d{2})[-](\\d{2})$");
			std::smatch result;

			if (std::regex_search(date, result, pattern)) {
				int year = std::stoi(result[0].str());

				if (year < 1000 || result[1].str().length() != std::to_string(year).length()) {
					return false;
				}

				if (std::stoi(result[2].str()) > 12 || std::stoi(result[2].str()) < 1) {
					return false;
				}

				if (std::stoi(result[3].str()) > 31 || std::stoi(result[3].str()) < 1) {
					return false;
				}
			} else {
				return false;
			}
		}

		return true;
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	DateHelper date;

	// TEST
	assert(date.IsValid( { std::string("1985-11-13") }) == true);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string(" 19801-10-13 ") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("2025-12-01") }) == true);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string(" 1980-10-13 ") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string(" 1980-10-13 ") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string(" 1980-13-13 ") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string(" 1980-12--1 ") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("1980-12-01-04") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("1980-11-12-11-41") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string(" 1980-01-33 ") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("1980-01-01") }) == true);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("0001-12-12") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("1900-12-12"), std::string("0100-12-12") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("999-12-12") }) == false);
	// TEST_END

	// TEST
	assert(date.IsValid( { std::string("1980-13-13") }) == false);
	// TEST_END
}

