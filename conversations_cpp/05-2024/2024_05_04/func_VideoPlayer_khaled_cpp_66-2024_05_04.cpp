/***
 * Prompt:

 khaled_cpp_66-2024_05_04: 6f29752b-d150-4cb4-8e79-72c6521d68da

 func_VideoPlayer_khaled_cpp_66-2024_05_04


 Design a C++ function called VideoPlayer, it will accept non-empty input called subtitle of type std::string. Subtitle should consist of number(has no leading zeros) then dot(".") then spaces or non-empty text e.g. "1. this is test", "2. " or "4. this is another test" but "05. test" and "6." are invalid subtitles. The function should return a boolean true if the subtitle is correct otherwise return false. Please don't forget to validate input.


 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>

bool VideoPlayer(std::string subtitle) {
	if (!subtitle.size()) {
		throw std::invalid_argument("subtitle can't be empty");
	}

	std::string tmp = "";
	int flag = -1;

	for (int idx = 0; idx < subtitle.length(); idx++) {
		if (subtitle[idx] == '.') {
			flag = true;
			break;
		}
		tmp += subtitle[idx];
	}

	if (flag == -1 || flag == subtitle.length() - 1) {
		return false;
	}

	int number;
	std::stringstream stringstreamer;

	stringstreamer << tmp;
	stringstreamer >> number;

	if (tmp.length() != std::to_string(number).length()) {
		return false;
	}

	return true;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(VideoPlayer("1. this is test") == true);
	// TEST_END

	// TEST
	assert(VideoPlayer("01. this is test") == false);
	// TEST_END

	// TEST
	assert(VideoPlayer("1. ") == true);
	// TEST_END

	// TEST
	assert(VideoPlayer("1.") == false);
	// TEST_END

	// TEST
	assert(VideoPlayer("1.. this is test") == true);
	// TEST_END

	// TEST
	assert(VideoPlayer("1test1. this is test") == false);
	// TEST_END

	// TEST
	try {
		VideoPlayer("");
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "subtitle can't be empty");
	}
	// TEST_END
}

