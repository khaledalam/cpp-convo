/***
 * Prompt:




 khaled_cpp_14_2024_18_04: 94cc5065-babb-4425-9406-daf1bf318b71










 Write me a C++ function named CardBlockGuardMiddleware that accepts only one input called transactions of type std::vector<Transaction> where Transaction is a struct type that contains 2 variables card_number and used_at_time_24h members both of them of type std::string and 3 functions IsValidVisaCardNumber, IsValidTime and IsValidData members which all of them not accept any parameters and returns type of boolean. The function should returns boolean true if all the given transactions are valid otherwise return false. The transactions of some card are valid if there are no 2 transactions with this card occurs in less than 3 minutes between each of them. Please make sure to validate card_number and validate the used_at_time_24h variable which represents when this transaction occurs today in 24h format. Use regular expression in the solution.



 */

#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <regex>

struct Transaction {
	std::string card_number;
	std::string used_at_time_24h;

	bool IsValidVisaCardNumber() {
		const std::regex pattern("^4[0-9]{12}(?:[0-9]{3})?$");

		return !card_number.empty() && regex_match(card_number, pattern);
	}

	bool IsValidTime() {
		if (used_at_time_24h[2] != ':') {
			return false;
		}

		used_at_time_24h[2] = ' ';

		std::stringstream ss;
		ss << used_at_time_24h;

		int hours, minutes;
		ss >> hours;
		ss >> minutes;

		return hours <= 23 && hours >= 0 && minutes <= 59 && minutes >= 0;
	}

	bool IsValidData() {
		return IsValidVisaCardNumber() && IsValidTime();
	}
};

int ConvertTimeToMinutes(std::string valid_time_in_24_h) {
	valid_time_in_24_h[2] = ' ';

	std::stringstream ss;
	ss << valid_time_in_24_h;

	int hours, minutes;
	ss >> hours;
	ss >> minutes;

	return hours * 60 + minutes;
}

bool CardBlockGuardMiddleware(std::vector<Transaction> transactions) {
	std::map<std::string, std::vector<int>> group_by_card_number;
	for (Transaction &transaction : transactions) {
		if (!transaction.IsValidData()) {
			throw std::invalid_argument("Invalid input");
		}
		group_by_card_number[transaction.card_number].push_back(ConvertTimeToMinutes(transaction.used_at_time_24h));
	}

	for (const std::pair<std::string, std::vector<int>> &pair : group_by_card_number) {

		std::vector<int> times = pair.second;

		sort(times.begin(), times.end());

		for (int i = 1; i < times.size(); i++) {
			if (times[i] - times[i - 1] < 3) {
				return true;
			}
		}
	}

	return false;
}

#include <cassert>
int main() {
	// TEST
	std::vector<Transaction> input = { Transaction { card_number: "4444111111111", used_at_time_24h: "13:10" } };
	assert(CardBlockGuardMiddleware(input) == false);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111111111", used_at_time_24h: "13:10" } };
	assert(CardBlockGuardMiddleware(input) == false);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111111111", used_at_time_24h: "13:10" }, Transaction { card_number: "4444111111111", used_at_time_24h: "13:11" } };
	assert(CardBlockGuardMiddleware(input) == true);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111112222", used_at_time_24h: "13:10" }, Transaction { card_number: "4444111111111", used_at_time_24h: "13:11" } };
	assert(CardBlockGuardMiddleware(input) == false);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111111111", used_at_time_24h: "13:10" }, Transaction { card_number: "4444111111111", used_at_time_24h: "13:13" } };
	assert(CardBlockGuardMiddleware(input) == false);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111111111", used_at_time_24h: "13:10" }, Transaction { card_number: "4444111111111", used_at_time_24h: "13:13" }, Transaction { card_number
			: "4444111111111", used_at_time_24h: "13:09" } };
	assert(CardBlockGuardMiddleware(input) == true);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111111111", used_at_time_24h: "00:00" }, Transaction { card_number: "4444111111111", used_at_time_24h: "23:59" } };
	assert(CardBlockGuardMiddleware(input) == false);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111111111", used_at_time_24h: "13:10" }, Transaction { card_number: "4444111111111", used_at_time_24h: "13:13" }, Transaction { card_number
			: "4444111111111", used_at_time_24h: "03:09" }, Transaction { card_number: "4444111111133", used_at_time_24h: "13:10" }, Transaction { card_number: "4444111111144", used_at_time_24h
			: "13:10" } };
	assert(CardBlockGuardMiddleware(input) == false);
	// TEST_END

	// TEST
	input = { };
	assert(CardBlockGuardMiddleware(input) == false);
	// TEST_END

	// TEST
	input = { Transaction { card_number: "444411111111", used_at_time_24h: "13:10" } };
	try {
		assert(CardBlockGuardMiddleware(input) == true);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input = { Transaction { card_number: "4444111111111", used_at_time_24h: "33:10" } };
	try {
		assert(CardBlockGuardMiddleware(input) == true);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

}
