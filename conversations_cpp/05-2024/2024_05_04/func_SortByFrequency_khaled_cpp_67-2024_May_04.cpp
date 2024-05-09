/***
 * Prompt:

 khaled_cpp_67-2024_May_04:

 func_SortByFrequency_khaled_cpp_67-2024_May_04

 Design a C++ function called SortByFrequency, it should accept a non-empty input called text of type std::string. The function should return another sorted by frequency text of type std::string. Sorted by frequency text is a string that its characters are sorted based on how many times they appear in the string and if there are 2 or more characters appears the with the same frequency then sort them based on their location in the input. e.g. "zbbccat" after sort should be "bbcczat". Please don't forget to validate input and use lambda function in the solution.


 */

#include <stdexcept>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

std::string SortByFrequency(std::string text) {

	if (text.empty()) {
		throw std::invalid_argument("input can't be empty");
	}

	std::map<char, int> mapper, first_appear_index;
	std::vector<std::pair<char, int>> vec;
	int idx = 0;
	for (const char &character : text) {
		mapper[character]++;
		first_appear_index[character] = idx++;
	}

	for (const std::pair<char, int> &mp_it : mapper) {
		vec.push_back(std::make_pair(mp_it.first, mp_it.second));
	}

	std::sort(vec.begin(), vec.end(), [&](const std::pair<char, int> &char_1, const std::pair<char, int> &char_2) {
		if (char_1.second != char_2.second) {
			return char_1.second > char_2.second;
		} else {
			return first_appear_index[char_1.first] < first_appear_index[char_2.first];
		}
	});

	std::string result = "";
	for (const std::pair<char, int> &vec_it : vec) {
		result += std::string(vec_it.second, vec_it.first);
	}

	return result;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert(SortByFrequency("aabccc") == std::string("cccaab"));
	// TEST_END

	// TEST
	assert(SortByFrequency("abb") == std::string("bba"));
	// TEST_END

	// TEST
	assert(SortByFrequency("abBb") == std::string("bbaB"));
	// TEST_END

	// TEST
	assert(SortByFrequency("zbbccat") == std::string("bbcczat"));
	// TEST_END

	// TEST
	assert(SortByFrequency("1223") == std::string("2213"));
	// TEST_END

	// TEST
	assert(SortByFrequency("Aavv") == std::string("vvAa"));
	// TEST_END

	// TEST
	assert(SortByFrequency("aaaccttttc") == std::string("ttttaaaccc"));
	// TEST_END

	// TEST
	assert(SortByFrequency("aaabbb") == std::string("aaabbb"));
	// TEST_END
	// TEST
	assert(SortByFrequency("aaavvbbb") == std::string("aaabbbvv"));
	// TEST_END

	// TEST
	assert(SortByFrequency("a") == std::string("a"));
	// TEST_END

	// TEST
	try {
		SortByFrequency("");
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "input can't be empty");
	}
	// TEST_END
}

