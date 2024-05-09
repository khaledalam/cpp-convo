/***
 * Prompt:

 khaled_cpp_63-2024_05_03: 2c5c7d81-45e7-434c-a8e7-a8c2cf212386

 func_ReadNumber_khaled_cpp_63-2024_05_03


 Write a C++ function called ReadNumber, it will accept an input called number of type std::string. the input should consist of uppercase substrings "I", "V" and "IV". "I" equal 1, "V" equal 5 and "IV" equal 4. This function should return number of type int that represent the sum of numbers that appears in the string e.g. "III" string is equal to 3 and "IVV" is equal 9 and "VI" equal to 6. Please don't forget to validate the input.


 */

#include <stdexcept>
#include <iostream>
#include <cctype>
#include <map>

int ReadNumber(std::string number) {
	if (number.length() < 1) {
		throw std::invalid_argument("Number can't be empty string");
	}

	for (const char &digit : number) {
		if (digit != toupper(digit) || (digit != 'I' && digit != 'V')) {
			throw std::invalid_argument("I and V characters are only allowed");
		}
	}

	std::map<char, int> mapper_char;
	std::map<std::string, int> mapper_string;
	mapper_char['I'] = 1;
	mapper_char['V'] = 5;
	mapper_string["IV"] = 4;

	if (number.length() < 2) {
		return mapper_char[number[0]];
	}

	int result = 0;
	std::string str = "";
	for (int iter = 1; iter < number.size(); iter++) {
		str += number[iter - 1];
		str += number[iter];

		if (mapper_string[str] > 0) {
			result += mapper_string[str];
			number[iter - 1] = '#';
			number[iter] = '#';
		}

		str = "";
	}

	for (int iter = 0; iter < number.size(); iter++) {
		if (number[iter] != '#') {
			result += mapper_char[number[iter]];
		}
	}

	return result;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(ReadNumber("I") == 1);
	// TEST_END

	// TEST
	assert(ReadNumber("III") == 3);
	// TEST_END

	// TEST
	assert(ReadNumber("V") == 5);
	// TEST_END

	// TEST
	assert(ReadNumber("IV") == 4);
	// TEST_END

	// TEST
	assert(ReadNumber("IIV") == 5);
	// TEST_END

	// TEST
	assert(ReadNumber("IVV") == 9);
	// TEST_END

	// TEST
	assert(ReadNumber("VI") == 6);
	// TEST_END

	// TEST
	assert(ReadNumber("VIV") == 9);
	// TEST_END

	// TEST
	try {
		ReadNumber("");
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Number can't be empty string");
	}
	// TEST_END

	// TEST
	try {
		ReadNumber("iV");
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "I and V characters are only allowed");
	}
	// TEST_END

	// TEST
	try {
		ReadNumber("5");
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "I and V characters are only allowed");
	}
	// TEST_END
}

