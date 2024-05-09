/***
 * Prompt:




 khaled_cpp_49_2024_25_04: a53475f8-2b44-45b1-b6f5-7bda54816e7d

 func_BotDetector_khaled_cpp_49_2024_25_04

 Write a C++ function called BotDetector, it will accept one input called visitors of type std::vector<Visitor> where Visitor is a struct type that contains id member of type int, signature member of type std::string and time member of type int. This function should return boolean true if there is some bot visit in the input list otherwise return false. The visit considered as a bot visit if there are 2 visits from same visitor id the difference between their time member values less than 4 or if there is same signature of 2 or more visits from same id. Please note that time member can't be negative value, don't forget to validate that. Also please use std::map and std::set in the solution.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

struct Visitor {
	int id;
	std::string signature;
	int time;
};

bool BotDetector(std::vector<Visitor> visitors) {
	std::vector<std::string> bot_keywords;
	std::map<int, std::vector<int>> mapper;
	std::map<int, std::set<std::string>> uniqueness;

	for (const Visitor &visitor : visitors) {
		if (std::find(bot_keywords.begin(), bot_keywords.end(), visitor.signature) != bot_keywords.end()) {
			return true;
		}
	}

	for (const Visitor &visitor : visitors) {
		if (visitor.time < 0) {
			throw std::invalid_argument("Invalid input");
		}

		mapper[visitor.id].push_back(visitor.time);

		int size_before = uniqueness[visitor.id].size();
		uniqueness[visitor.id].insert(visitor.signature);
		int size_after = uniqueness[visitor.id].size();

		if (size_before == size_after) {
			return true;
		}
	}

	std::map<int, std::vector<int>>::iterator map_iterator = mapper.begin();

	while (map_iterator != mapper.end()) {
		std::vector<int> &times = (*map_iterator).second;

		sort(times.begin(), times.end());

		std::vector<int>::iterator vector_iterator = times.begin();

		vector_iterator++;

		while (vector_iterator != (*map_iterator).second.end()) {

			if ((*vector_iterator) - (*(vector_iterator - 1)) < 4) {
				return true;
			}

			vector_iterator++;
		}

		map_iterator++;
	}

	return false;
}

#include <cassert>
int main(int argc, const char *argv[]) {

	// TEST
	assert(BotDetector( { Visitor { .id = 1, .signature = std::string("linux123"), .time = 1 } }) == false);
	// TEST_END

	// TEST
	assert(BotDetector( { Visitor { .id = 1, .signature = std::string("linux123@abc"), .time = 1 }, Visitor { .id = 1, .signature = std::string("linux123"), .time = 3 } }) == true);
	// TEST_END

	// TEST
	assert(BotDetector( { Visitor { .id = 1, .signature = std::string("linux123A"), .time = 1 }, Visitor { .id = 1, .signature = std::string("linux123"), .time = 5 } }) == false);
	// TEST_END

	// TEST
	assert(BotDetector( { Visitor { .id = 1, .signature = std::string("linux123"), .time = 1 }, Visitor { .id = 1, .signature = std::string("linux123B"), .time = 3 } }) == true);
	// TEST_END

	// TEST
	assert(BotDetector( { Visitor { .id = 1, .signature = std::string("linux123"), .time = 1 }, Visitor { .id = 1, .signature = std::string("linux123"), .time = 10 } }) == true);
	// TEST_END

	// TEST
	assert(BotDetector( { Visitor { .id = 1, .signature = std::string("linux123"), .time = 1 }, Visitor { .id = 2, .signature = std::string("linux123"), .time = 10 } }) == false);
	// TEST_END

	// TEST
	try {
		assert(BotDetector( { Visitor { .id = 1, .signature = std::string("linux123"), .time = -1 } }) == true);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

