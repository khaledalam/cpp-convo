/***
 * Prompt:





 khaled_cpp_45_2024_25_04: b8be2428-a119-4539-b1e8-74c776659419


 func_MessageBroker_khaled_cpp_45_2024_25_04

 Write me a C++ function called MessageBroker, it will accept one input called options of type std::vector<Message> where Message is a struct type that contains int member called destination and long long member called timestamp, both values of destination and timestamp should be zero or positive. This function should sort the messages of each destination based on the lowest timestamp and return list of pairs of type std::map<int, std::vector<Message>> where first argument refers to the destination and second argument refers to the sorted messages list. Use lambda function in the solution and don't forget to validate the input.


 */

#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

struct Message {
	int destination;
	long long timestamp;

	bool operator ==(const Message &another) const {
		return destination == another.destination && timestamp == another.timestamp;
	}

	bool operator <(const Message &another) const {
		return timestamp < another.timestamp;
	}

	bool IsValid() {
		return destination >= 0 && timestamp >= 0;
	}
};

std::map<int, std::vector<Message>> MessageBroker(std::vector<Message> options) {
	std::map<int, std::vector<Message>> destinations;

	std::vector<Message>::iterator it = options.begin();

	while (it != options.end()) {
		if (!it->IsValid()) {
			throw std::invalid_argument("Invalid input");
		}

		destinations[(*it).destination].push_back((*it));

		it++;
	}

	for (std::pair<const int, std::vector<Message> > &destination : destinations) {
		std::vector<Message> &destination_messages = destination.second;

		sort(destination_messages.begin(), destination_messages.end(), [](const Message &a, const Message &b) {
			return a < b;
		});
	}

	return destinations;
}

#include <cassert>
int main(int argc, const char *argv[]) {
	// TEST
	assert((MessageBroker( { Message { .destination = 0, .timestamp = 1234 } }) == std::map<int, std::vector<Message>> { { 0, { Message { .destination = 0, .timestamp = 1234 } } } }));
	// TEST_END

	// TEST
	assert((MessageBroker( { Message { .destination = 0, .timestamp = 1234 }, Message { .destination = 0, .timestamp = 1 } }) == std::map<int, std::vector<Message>> { { 0, { Message { .destination = 0, .timestamp = 1 }, Message { .destination = 0, .timestamp = 1234 } } } }));
	// TEST_END

	// TEST
	assert((MessageBroker( { Message { .destination = 0, .timestamp = 1234 }, Message { .destination = 0, .timestamp = 1 }, Message { .destination = 1, .timestamp = 1 } }) == std::map<int, std::vector<Message>> { { 0, { Message { .destination = 0, .timestamp = 1 }, Message { .destination = 0,
			.timestamp = 1234 } } }, { 1, { Message { .destination = 1, .timestamp = 1 } } } }));
	// TEST_END

	// TEST
	try {
		assert((MessageBroker( { Message { .destination = -1, .timestamp = 1234 } }) == std::map<int, std::vector<Message>> { { 1, { Message { .destination = 1, .timestamp = 1 } } } }));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert((MessageBroker( { Message { .destination = 1, .timestamp = -1234 } }) == std::map<int, std::vector<Message>> { { 1, { Message { .destination = 1, .timestamp = 1 } } } }));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		assert((MessageBroker( { Message { .destination = 0, .timestamp = 1234 }, Message { .destination = 1, .timestamp = 1 }, Message { .destination = 1, .timestamp = -1 } }) == std::map<int, std::vector<Message>> { { 0, { Message { .destination = 0, .timestamp = 1 }, Message { .destination = 0,
				.timestamp = 1234 } } }, { 1, { Message { .destination = 1, .timestamp = 1 } } } }));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

