/***
 * Prompt:




 khaled_cpp_34_2024_23_04: f81cc09b-b0d8-4aaa-bf97-94adf436b9de


 class_AI_khaled_cpp_34_2024_23_04

 Design a C++ class called AI. This class contains a method member called Train, it accepts three inputs, first input called model of type std::string, second and third inputs called db_1 and db_2 both of them of type std::map<std::string, std::string>. This method should check if the model string existed as key in any of db_1 or db_2 and return the value otherwise check if we can split the model into 2 parts that both of them are existed as keys in the db_1 and/or db_2 and return the concatenated values of both of them. The output of this method should be type of std::string. Please note that the words are case sensitive and spaces are allowed.


 */

#include <stdexcept>
#include <string>
#include <map>

class AI {
public:
	std::string Train(std::string model, std::map<std::string, std::string> db_1, std::map<std::string, std::string> db_2) {
		if (db_1.find(model) != db_1.end()) {
			return db_1[model];
		}

		if (db_2.find(model) != db_2.end()) {
			return db_2[model];
		}

		std::string result = std::string("");

		for (int i = 1; i < model.length(); i++) {
			result = std::string("");
			std::string part_1 = model.substr(0, i), part_2 = model.substr(i);

			int found = 0;

			if (db_1.find(part_1) != db_1.end()) {
				result += db_1[part_1];
				found++;
			} else if (db_2.find(part_1) != db_2.end()) {
				result += db_2[part_1];
				found++;
			}

			if (found) {
				if (db_1.find(part_2) != db_1.end()) {
					result += db_1[part_2];
					found++;
				} else if (db_2.find(part_2) != db_2.end()) {
					result += db_2[part_2];
					found++;
				}
			}

			if (found == 2) {
				return result;
			}

		}

		return result;
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	AI ai;

	// TEST
	assert(ai.Train(std::string("Test"), { { std::string("Te"), std::string("OK") } }, { { std::string("st"), std::string("!") } }) == std::string("OK!"));
	// TEST_END

	// TEST
	assert(ai.Train(std::string("Test"), { { std::string("Te"), std::string("OK") } }, { { std::string("St"), std::string("!") } }) == std::string(""));
	// TEST_END

	// TEST
	assert(ai.Train(std::string("Test r "), { { std::string("Test"), std::string("OK") } }, { { std::string(" r "), std::string(" Done !") } }) == std::string("OK Done !"));
	// TEST_END

	// TEST
	assert(ai.Train(std::string(""), { { std::string(""), std::string("OK") } }, { { std::string("St"), std::string("!") } }) == std::string("OK"));
	// TEST_END

	// TEST
	assert(ai.Train(std::string(""), { { std::string(""), std::string("") } }, { { std::string(""), std::string("@") } }) == std::string(""));
	// TEST_END

	// TEST
	assert(ai.Train(std::string(""), { { std::string(""), std::string("@") } }, { { std::string(""), std::string("") } }) == std::string("@"));
	// TEST_END

	// TEST
	assert((ai.Train(std::string("TeSt"), { { std::string("Te"), std::string("OK") } }, { { std::string("st"), std::string("!") } }) == std::string("")));
	// TEST_END
}

