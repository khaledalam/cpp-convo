/*
 *
 * 804076bd-165a-43b2-91fc-a34a243c027d
 *
 * Prompt:
 *
 * Create a C++ class named NumbersHelper. This class will include a method named HighestNumber.
 * This method will accept an input of type string, the string consists of digits only.
 * This method will return another string that represents the highest positive value that can be formed from the given input.
 * Please note that minimum length of input is 1 character and maximum length of input is 9 characters otherwise raise an exception,
 * also note that if the final output value consists of only zeros characters or if input contains of non-digit characters you should raise an exception as well.
 *
 */

#include <algorithm>
#include <cassert>
#include <string>

class NumbersHelper {
public:
	std::string HighestNumber(const std::string &number) {
		std::string number_output = number;

		if (number_output.length() < 1) {
			throw std::invalid_argument("The minimum acceptable length is 1 character");
		}

		if (number_output.length() > 9) {
			throw std::invalid_argument("The maximum acceptable length is 9 characters");
		}

		int count_zeros = 0;
		for (const char &ch : number_output) {
			if (!isdigit(ch)) {
				throw std::invalid_argument("The input should contain only digits");
			}
			count_zeros += (ch == '0');
		}

		if (count_zeros == number_output.length()) {
			throw std::invalid_argument("The output should not be zeros");
		}

		std::sort(number_output.begin(), number_output.end(), std::greater<char>());

		return number_output;
	}
};

int main() {
	NumbersHelper number_helper;

	// TEST
	assert(number_helper.HighestNumber("09821") == "98210");
	// TEST_END

	// TEST
	assert(number_helper.HighestNumber("1010") == "1100");
	// TEST_END

	//TEST
	try {
		assert(number_helper.HighestNumber("000") == "000");
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "The output should not be zeros");
	}
	//TEST_END

	//TEST
	try {
		assert(number_helper.HighestNumber("") == "");
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "The minimum acceptable length is 1 character");
	}
	//TEST_END

	//TEST
	try {
		assert(number_helper.HighestNumber("9876543210") == "");
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "The maximum acceptable length is 9 characters");
	}
	//TEST_END

	//TEST
	try {
		assert(number_helper.HighestNumber("12:00PM") == "");
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "The input should contain only digits");
	}
	//TEST_END
}
