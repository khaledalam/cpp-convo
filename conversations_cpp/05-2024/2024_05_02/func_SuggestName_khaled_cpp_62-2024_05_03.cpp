/***
 * Prompt:

 khaled_cpp_62-2024_05_03: c18abf00-669a-445d-89e2-5a50e8c78b00


 Design a C++ function called SuggestName, it will accept two inputs, first input is a non-empty list called names of type std::vector<std::string> each string in the list is a non-empty string as well, and second input is a non-empty string called prefix of type std::string. This function should return a number of type int that represent how many strings in the list that start with the prefix of the second input. Please don't forget to validate the inputs and throw invalid_argument if there are invalid inputs.


 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

int SuggestName(const std::vector<std::string> &names, std::string prefix) {

	if (names.empty()) {
		throw std::invalid_argument("Names list can't be empty");
	}

	if (prefix.length() < 1) {
		throw std::invalid_argument("Prefix can't be empty");
	}

	int valid_names_count = 0;

	for (const std::string &name : names) {

		if (name.empty()) {
			throw std::invalid_argument("Name can't be empty");
		}

		if (name.length() < prefix.length()) {
			continue;
		}

		bool match = true;
		for (int i = 0; i < prefix.length(); i++) {
			match &= (name[i] == prefix[i]);
		}

		if (match) {
			valid_names_count++;
		}
	}

	return valid_names_count;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(SuggestName( { std::string("test"), std::string("testtext") }, std::string("test")) == 2);
	// TEST_END

	// TEST
	assert(SuggestName( { std::string("tast"), std::string("testtext") }, std::string("test")) == 1);
	// TEST_END

	// TEST
	assert(SuggestName( { std::string("tast"), std::string("testtext") }, std::string("text")) == 0);
	// TEST_END

	// TEST
	assert(SuggestName( { std::string("test"), std::string("te") }, std::string("tes")) == 1);
	// TEST_END

	// TEST
	assert(SuggestName( { std::string("test") }, std::string("t")) == 1);
	// TEST_END

	// TEST
	try {
		SuggestName( { }, std::string("t"));
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Names list can't be empty");
	}
	// TEST_END

	// TEST
	try {
		SuggestName( { std::string("") }, std::string("test"));
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Name can't be empty");
	}
	// TEST_END

	// TEST
	try {
		SuggestName( { std::string("test") }, std::string(""));
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Prefix can't be empty");
	}
	// TEST_END
}

