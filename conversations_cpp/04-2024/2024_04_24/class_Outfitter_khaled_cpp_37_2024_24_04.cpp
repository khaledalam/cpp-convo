/***
 * Prompt:




 khaled_cpp_37_2024_24_04: b3ad6c08-f645-4e99-a8fb-63d3a79c26e7

 class_Outfitter_khaled_cpp_37_2024_24_04

 Write me a C++ class called Outfitter. This class contains a method named HowManySets, it accepts an input called items of type std::vector<Item> where Item is a struct type that contains int member called color and boolean member called top which represent group. We have 2 groups based on top value. The method should return number of type integer which refers to the count of sets that we can form from these items. Note that each set consists of 2 items from different group. Please consider that we can't use same color in same group but we can use same color in different groups. Also note that color can be any negative, zero or positive number and items list input can't be empty, don't forget to validate the input.


 */

#include <stdexcept>
#include <set>
#include <map>
#include <iostream>
#include <algorithm>

struct Item {
	int color;
	bool top;
};

class Outfitter {
public:
	int HowManySets(std::vector<Item> items) {
		if (items.empty()) {
			throw std::invalid_argument("Items can't be empty");
		}

		std::map<int, std::set<int>> category;

		for (const Item &item : items) {
			category[item.top].insert(item.color);
		}

		return std::min(category[0].size(), category[1].size());
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	Outfitter outfitter;

	// TEST
	assert(outfitter.HowManySets( { Item { color: 1, top: true } }) == 0);
	// TEST_END

	// TEST
	assert(outfitter.HowManySets( { Item { color: 1, top: true }, Item { color: 1, top: false } }) == 1);
	// TEST_END

	// TEST
	assert(outfitter.HowManySets( { Item { color: 1, top: true }, Item { color: 1, top: true }, Item { color: 1, top: false }, Item { color: 1, top: false } }) == 1);
	// TEST_END

	// TEST
	assert(outfitter.HowManySets( { Item { color: 1, top: true }, Item { color: 1, top: true }, Item { color: 1, top: false }, Item { color: 2, top: false } }) == 1);
	// TEST_END

	// TEST
	assert(outfitter.HowManySets( { Item { color: -1, top: true }, Item { color: 2, top: true }, Item { color: 1, top: false }, Item { color: 2, top: false } }) == 2);
	// TEST_END

	// TEST
	assert(outfitter.HowManySets( { Item { color: 1, top: true }, Item { color: 1, top: true }, Item { color: 2, top: true }, Item { color: 1, top: false }, Item { color: 2, top: false } }) == 2);
	// TEST_END

	// TEST
	try {
		assert(outfitter.HowManySets( { }) == 1);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Items can't be empty");
	}
	// TEST_END
}

