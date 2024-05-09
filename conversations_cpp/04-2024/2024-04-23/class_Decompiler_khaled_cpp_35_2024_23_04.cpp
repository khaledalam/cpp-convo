/***
 * Prompt:




 khaled_cpp_35_2024_23_04: 594b999e-e25f-4783-a0ce-1156ed271be7


 class_Decompiler_khaled_cpp_35_2024_23_04

 Design a C++ class called Decompiler. This class contains a function member called AnalyzeLine, it accepts an input called binary of type std::string. This input string should consists of one or multiple operations and numbers, operation can be one of these two words "add" and "remove" and number can be negative, zero or positive. The function should return number of type integer. "add" means increase the initial value by the next followed number and remove means decrease the initial value by the next followed number. Please note that the initial value is zero. Don't forget to validate the inputs.


 */

#include <stdexcept>
#include <string>
#include <sstream>

class Decompiler {
public:
	int AnalyzeLine(std::string binary) {
		std::string tmp;
		std::stringstream ss;
		ss << binary;

		int result = 0;

		while (ss >> tmp) {
			if (tmp == "add") {
				ss >> tmp;
				try {
					result += stoi(tmp);
				} catch (const std::exception e) {
					throw std::invalid_argument("Invalid conversion");
				}
			} else if (tmp == "remove") {
				ss >> tmp;
				try {
					result -= stoi(tmp);
				} catch (const std::exception e) {
					throw std::invalid_argument("Invalid conversion");
				}
			} else {
				throw std::invalid_argument("Invalid input");
			}
		}

		return result;
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	Decompiler decompiler;

	// TEST
	assert(decompiler.AnalyzeLine(std::string("add 1 remove 5 add 2")) == -2);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("")) == 0);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("add 1 add 2")) == 3);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("add 1")) == 1);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("add -20")) == -20);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("remove -20")) == 20);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("add 0")) == 0);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("remove 1   add 2")) == 1);
	// TEST_END

	// TEST
	assert(decompiler.AnalyzeLine(std::string("remove 1 remove 2")) == -3);
	// TEST_END

	// TEST
	try {
		assert(decompiler.AnalyzeLine(std::string("1 remove 2")) == -3);
	} catch (const std::invalid_argument e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert(decompiler.AnalyzeLine(std::string("1 remove 2")) == -3);
	} catch (const std::invalid_argument e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert(decompiler.AnalyzeLine(std::string("remove 1 remove remove 2")) == -3);
	} catch (const std::invalid_argument e) {
		assert(std::string(e.what()) == "Invalid conversion");
	}
	// TEST_END

	// TEST
	try {
		assert(decompiler.AnalyzeLine(std::string("1")) == -3);
	} catch (const std::invalid_argument e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

