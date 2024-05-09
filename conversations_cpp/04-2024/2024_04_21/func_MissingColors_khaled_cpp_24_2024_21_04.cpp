/***
 * Prompt:




 khaled_cpp_24_2024_21_04: 97eb4e44-5564-4b47-b17f-7a9a55230617



 func_MissingColors_khaled_cpp_24_2024_21_04



 Design me a C++ function named MissingColors that accepts two inputs called wall and colors both of them of type std::string. Each character in both inputs represents a color and it should be alphabetic in lower or upper case. Note that lowercase color equal to uppercase color. We need to color all the positions of the wall string using the same color character that mentioned in the wall string, and we only have colors characters in the colors string. The function should returns another text of type std::string that represent the needed colors to complete painting the wall. Please note that you can combine any 2 colors we have in colors string together to get any new color we want e.g. we can combine 'G' and 'G' and get 'R' or we can combine 'G' and 'A' and get 'S' and so on. Don't forget to validate the inputs.



 */

#include <stdexcept>
#include <string>
#include <map>
#include <cctype>
#include <iostream>

std::string MissingColors(std::string wall, std::string colors) {
	std::string missing_colors;

	std::map<char, int> freq;

	for (char &character : colors) {
		if (!isalpha(character)) {
			throw std::invalid_argument("Invalid character in colors");
		}

		character = tolower(character);

		freq[character]++;
	}

	for (char &character : wall) {
		if (!isalpha(character)) {
			throw std::invalid_argument("Invalid character in wall");
		}

		character = tolower(character);

		--freq[character];

		if (freq[character] < 0) {
			missing_colors += character;
		}
	}

	int items = 0;
	bool remove = false;
	for (const std::pair<char, int> pair : freq) {
		if (pair.second >= 0) {
			items += pair.second;
			remove = true;
		}
	}

	items /= 2;

	std::string result = "";
	if (remove) {
		if (missing_colors.length() > 0) {
			for (int i = 0; i < missing_colors.length() - items; i++) {
				result += missing_colors[i];
			}
		}
	} else {
		result = missing_colors;
	}

	return result;
}

#include <cassert>
int main() {
	// TEST
	std::string input1 = std::string("RGGRA");
	std::string input2 = std::string("ARRRE");
	std::string output = std::string("g");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("aa");
	input2 = std::string("A");
	output = std::string("a");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("AAa");
	input2 = std::string("ABBcc");
	output = std::string("");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("a");
	input2 = std::string("bc");
	output = std::string("");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("");
	input2 = std::string("");
	output = std::string("");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("");
	input2 = std::string("ABC");
	output = std::string("");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("ABC");
	input2 = std::string("");
	output = std::string("abc");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("AAa");
	input2 = std::string("ABBc");
	output = std::string("a");
	assert(MissingColors(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("BA");
	input2 = std::string("1A");
	try {
		assert(MissingColors(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid character in colors");
	}
	// TEST_END

	// TEST
	input1 = std::string("#A");
	input2 = std::string("aa");
	try {
		MissingColors(input1, input2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid character in wall");
	}
	// TEST_END

	// TEST
	input1 = std::string("f");
	input2 = std::string("a9");
	try {
		MissingColors(input1, input2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid character in colors");
	}
	// TEST_END
}
