/***
 * Prompt:




 khaled_cpp_53_2024_26_04: 202320ee-cb57-4ef0-9b1c-036464c957b6


 Write a C++ function called LongestArrow, it will accept one input called text which represent some text. This function should return number of type int which represent the max arrow string length in the input. Some string called arrow if it consist of only one or more continuous dashes and greater than symbol or less than symbol and one or more continuous dashes, so arrow string can be something like this "->", "<-", "-->", "<--", "--->" and so on. Please throw exception if the input is empty string and use regex in the solution.




 (<-+|-+>)



 =>
 <-
 -->
 <--<--
 -->>
 -><-
 <-<-<-
 >>-<-><--<
 --><---
 >>-><
 -->>
 -<>
 >
 <
 >>
 <<
 --
 -
 --<



 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <regex>

int LongestArrow(std::string text) {

	if (text.length() < 1) {
		throw std::invalid_argument("The input should not be empty");
	}

	int max_length = 0;

	const std::regex pattern("<-+|-+>");

	std::sregex_iterator matches(text.begin(), text.end(), pattern);

	for (std::sregex_iterator end; matches != end; matches++) {
		max_length = std::max(max_length, (int) matches->str().length());
	}

	return max_length;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(LongestArrow("->--->-->>") == 4);
	// TEST_END

	// TEST
	assert(LongestArrow("-->") == 3);
	// TEST_END

	// TEST
	assert(LongestArrow("-->>") == 3);
	// TEST_END

	// TEST
	assert(LongestArrow("-<>") == 0);
	// TEST_END

	// TEST
	assert(LongestArrow("-<--") == 3);
	// TEST_END

	// TEST
	assert(LongestArrow("--><---") == 4);
	// TEST_END

	// TEST
	try {
		assert(LongestArrow("") == 3);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "The input should not be empty");
	}
	// TEST_END
}

