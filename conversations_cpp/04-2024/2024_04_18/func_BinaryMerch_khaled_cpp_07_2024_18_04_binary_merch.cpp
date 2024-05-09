/***
 * Prompt:

 khaled_cpp_07_2024_18_04_binary_merch: a4801315-8e4f-4bc0-a788-7364b9e5179f

 Give me a C++ function called BinaryMerch that accepts one input called collection of type std::vector<std::pair<std::string, bool>>.
 The input collection contains a list of pairs, each pair represents t-shirt ID and t-shirt color, the color is black if the second argument of the pair is false otherwise the color is white. The function should returns std::vector<std::pair<std::string, std::string>> that contains valid binary merch pairs. Please note that 2 t-shirts called binary merch if one of them is white and the other one is black. Also consider that not necessary that collection contains same count of white and black t-shirts.


 */

#include <string>
#include <vector>

std::vector<std::pair<std::string, std::string>> BinaryMerch(std::vector<std::pair<std::string, bool>> collection) {
	std::vector<std::string> white, black;
	std::vector<std::pair<std::string, std::string>> valid_pairs;

	for (const std::pair<std::string, bool> &tshirt : collection) {
		if (tshirt.second) {
			white.push_back(tshirt.first);
		} else {
			black.push_back(tshirt.first);
		}
	}

	for (int i = 0; i < std::min(white.size(), black.size()); i++) {
		valid_pairs.push_back(std::make_pair(white[i], black[i]));
	}

	return valid_pairs;
}

#include <cassert>
int main() {
	// TEST
	std::vector<std::pair<std::string, bool>> collection { std::make_pair(std::string("UUID_1"), true), std::make_pair(std::string("UUID_2"), false) };
	std::vector<std::pair<std::string, std::string>> output { std::make_pair(std::string("UUID_1"), std::string("UUID_2")) };
	assert(BinaryMerch(collection) == output);
	// TEST_END

	// TEST
	collection = { std::make_pair(std::string("UUID_1"), true), std::make_pair(std::string("UUID_2"), true), std::make_pair(std::string("UUID_3"), false) };
	output = { std::make_pair(std::string("UUID_1"), std::string("UUID_3")) };
	assert(BinaryMerch(collection) == output);
	// TEST_END

	// TEST
	collection = { std::make_pair(std::string("UUID_1"), true), std::make_pair(std::string("UUID_2"), true), std::make_pair(std::string("UUID_3"), true) };
	output = { };
	assert(BinaryMerch(collection) == output);
	// TEST_END

	// TEST
	collection = { };
	output = { };
	assert(BinaryMerch(collection) == output);
	// TEST_END

}
