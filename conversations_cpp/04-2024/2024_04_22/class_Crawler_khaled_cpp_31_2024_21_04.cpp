/***
 * Prompt:




 khaled_cpp_31_2024_21_04:






 Create a C++ class named Crawler, this class will include a method called CanReach. This method will accept three inputs. First input called links of type std::map<std::string, std::vector<std::string>> which represents the relation between each key word and a list of words that can be reached to from this key word. Second input named "reach_from" of type std::string which represents the word that we will start the iteration from. Third input called "reach_to" of type std::string which represents the word that we want to reach to from reach_from. Note that all words should be alphabetic lower case characters only. This method should return boolean true if we can reach the third input from the second input. We can Please use dfs (Depth-first search) in your solution and don't forget to validate the inputs.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

class Crawler {
public:
	bool CanReach(std::map<std::string, std::vector<std::string>> &links, std::string &reach_from, const std::string &reach_to) {
		bool can_reach = false;
		std::map<std::string, bool> visit;

		for (const std::pair<std::string, std::vector<std::string>> pair : links) {

			for (const char &character : pair.first) {
				if (!isalpha(character) || !islower(character)) {
					throw std::invalid_argument("Invalid input");
				}
			}

			for (const std::string &word : pair.second) {
				for (char character : word) {
					if (!isalpha(character) || !islower(character)) {
						throw std::invalid_argument("Invalid input");
					}
				}
			}
		}

		DFS(links, reach_from, reach_to, can_reach, reach_from, visit);

		return can_reach;
	}

	void DFS(std::map<std::string, std::vector<std::string>> &links, const std::string &reach_from, const std::string &reach_to, bool &can_reach, std::string &walker, std::map<std::string, bool> &visit) {
		if (walker == reach_to) {
			can_reach = true;
			return;
		}

		if (visit[walker] || can_reach) {
			return;
		}

		if (links.find(walker) == links.end()) {
			return;
		}

		visit[walker] = true;

		for (std::string &value : links[walker]) {
			DFS(links, reach_from, reach_to, can_reach, value, visit);
		}
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	Crawler crawler;

	// TEST
	std::map<std::string, std::vector<std::string>> input1 = { { std::string("google"), { std::string("yahoo") } } };
	std::string input2 = std::string("google");
	std::string input3 = std::string("yahoo");
	bool output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("google"), { std::string("yahoo") } }, { std::string("yahoo"), { std::string("google") } } };
	input2 = std::string("yahoo");
	input3 = std::string("yahoo");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("google"), { std::string("amazon") } }, { std::string("amazon"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("yahoo");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("google"), { std::string("amazon"), std::string("apple") } }, { std::string("apple"), { std::string("yahoo") } } };
	input2 = std::string("apple");
	input3 = std::string("yahoo");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("google"), { std::string("amazon"), std::string("apple") } }, { std::string("apple"), { std::string("yahoo"), std::string("google") } } };
	input2 = std::string("apple");
	input3 = std::string("apple");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("google"), { std::string("amazon") } }, { std::string("amazon"), { std::string("yahoo") } } };
	input2 = std::string("yahoo");
	input3 = std::string("google");
	output = false;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { };
	input2 = std::string("yahoo");
	input3 = std::string("google");
	output = false;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string(""), { std::string("google") } } };
	input2 = std::string("");
	input3 = std::string("google");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("yahoo"), { std::string("") } } };
	input2 = std::string("yahoo");
	input3 = std::string("");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string(""), { std::string("") } } };
	input2 = std::string("");
	input3 = std::string("");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("google"), { std::string("amazon") } }, { std::string("amazon"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("amazon");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("google"), { std::string("amazon") } }, { std::string("amazon"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("amazon");
	output = true;
	assert(crawler.CanReach(input1, input2, input3) == output);
	//TEST_END

	// TEST
	input1 = { { std::string("Google"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("amazon");
	output = false;
	try {
		assert(crawler.CanReach(input1, input2, input3) == output);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	// TEST
	input1 = { { std::string("G00gle"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("amazon");
	output = true;
	try {
		assert(crawler.CanReach(input1, input2, input3) == output);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	// TEST
	input1 = { { std::string(" google"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("amazon");
	output = false;
	try {
		assert(crawler.CanReach(input1, input2, input3) == output);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	// TEST
	input1 = { { std::string("G00gle"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("amazon");
	output = true;
	try {
		assert(crawler.CanReach(input1, input2, input3) == output);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	// TEST
	input1 = { { std::string("amazon"), { std::string("yahoo") } }, { std::string("zoho"), { std::string("z00m") } } };
	input2 = std::string("amazon");
	input3 = std::string("yahoo");
	output = true;
	try {
		assert(crawler.CanReach(input1, input2, input3) == output);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END

	// TEST
	input1 = { { std::string("g oogle"), { std::string("yahoo") } } };
	input2 = std::string("google");
	input3 = std::string("amazon");
	output = true;
	try {
		assert(crawler.CanReach(input1, input2, input3) == output);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	//TEST_END
}

