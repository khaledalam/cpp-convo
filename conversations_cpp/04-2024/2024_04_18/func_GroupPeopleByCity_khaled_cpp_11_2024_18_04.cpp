/***
 * Prompt:




 khaled_cpp_11_2024_18_04: f16fe0db-a3ef-4542-a19f-deb4367bc674








 Write me a C++ function named GroupPeopleByCity which accepts only one input called cities of type std::vector<std::string>, Each string in the input represents a city of the user of the same index. City name can contains uppercase, lowercase and spaces. The function should trim the cities names and convert them to lowercase and returns map of type std::map<std::string, std::vector<std::string>> which each pair of it represents key as city and value as list of users in this city. Please note that users names should start with prefix "user_" and the index of the user, consider that the first user start with index 1.



 */

#include <string>
#include <vector>
#include <map>

std::map<std::string, std::vector<std::string>> GroupPeopleByCity(std::vector<std::string> cities) {
	std::map<std::string, std::vector<std::string>> result;

	int idx = 1;
	for (std::string &city : cities) {

		while (city[0] == ' ') {
			city.erase(0, 1);
		}

		while (city[city.size() - 1] == ' ') {
			city.erase(city.size() - 1);
		}

		std::transform(city.begin(), city.end(), city.begin(), [](unsigned char c) {
			return std::tolower(c);
		});

		result[city].push_back(("user_" + std::to_string(idx++)));
	}

	return result;
}

#include <cassert>
int main() {
	// TEST
	std::vector<std::string> input { std::string("Bologna"), std::string(" Genoa "), std::string("genoa") };
	std::map<std::string, std::vector<std::string>> output;
	output["genoa"] = { std::string("user_2"), std::string("user_3") };
	output["bologna"] = { std::string("user_1") };
	assert(GroupPeopleByCity(input) == output);
	// TEST_END

	// TEST
	input = { std::string("La Spezia"), std::string(" La spezia"), std::string("Pisa"), std::string("la speziA") };
	output.clear();
	output["la spezia"] = { std::string("user_1"), std::string("user_2"), std::string("user_4") };
	output["pisa"] = { std::string("user_3") };
	assert(GroupPeopleByCity(input) == output);
	// TEST_END

	// TEST
	input = { std::string("Altamura") };
	output.clear();
	output["altamura"] = { std::string("user_1") };
	assert(GroupPeopleByCity(input) == output);
	// TEST_END

	// TEST
	input = { };
	output.clear();
	assert(GroupPeopleByCity(input) == output);
	// TEST_END
}
