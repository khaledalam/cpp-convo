/***
 * Prompt:

 khaled_cpp_65-2024_05_03: c85c1b6b-78d5-4849-9203-2944e0fea868


 func_NeedFilter_khaled_cpp_65-2024_05_03

 Design me a C++ function called NeedFilter, it will accept an input called text of type std::string. The function should return a boolean true if the input need to be changed otherwise return false. The input will need to be changed if it contain space at the beginning or at the end or if it contain 2 or more continuous spaces. Please also note that the input can't be empty.


 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>

bool NeedFilter(std::string text) {
	if (!text.length()) {
		throw std::invalid_argument("Input can't be empty");
	}

	if (text.front() == ' ' || text.back() == ' ') {
		return true;
	}

	std::stringstream stringstreamer;
	std::string temp = text, process = "";

	stringstreamer << temp;
	temp = "";
	int index = 0;
	while (stringstreamer >> temp) {
		if (index++) {
			process += " " + temp;
		} else {
			process += temp;
		}
	}

	return text.length() != process.length();
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(NeedFilter("This is test ") == true);
	// TEST_END

	// TEST
	assert(NeedFilter("4 +  4 = 8") == true);
	// TEST_END

	// TEST
	assert(NeedFilter(" This is test") == true);
	// TEST_END

	// TEST
	assert(NeedFilter(" This is test ") == true);
	// TEST_END

	// TEST
	assert(NeedFilter("This is  test") == true);
	// TEST_END

	// TEST
	assert(NeedFilter("This is test") == false);
	// TEST_END

	// TEST
	assert(NeedFilter(" ") == true);
	// TEST_END

	// TEST
	assert(NeedFilter("This is test...") == false);
	// TEST_END

	// TEST
	try {
		NeedFilter("");
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Input can't be empty");
	}
	// TEST_END
}

