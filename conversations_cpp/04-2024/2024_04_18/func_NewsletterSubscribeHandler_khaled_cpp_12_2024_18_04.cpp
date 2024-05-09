/***
 * Prompt:




 khaled_cpp_12_2024_18_04: 141a971d-c3e1-4d92-9ebd-8afd7b7a3c07






 Design me a C++ function named NewsletterSubscribeHandler which accept two inputs, first input called job of type std::vector<User> where User is a struct type that contains a valid_email member as type of std::string and need_to_unsubscribe member as type of boolean, second input called emails_db of type std::vector<std::string>. The first input list represents a sequence of subscribe and/or un-subscribe operations. The second input which contains the current subscribed emails in the database. The function should return another list of type std::vector<std::string> that represents the new emails_db after performing the job operations. Please note that if need_to_unsubscribe member is true that means user need to perform ub-subscribe action otherwise means that user need to perform subscribe action.



 */

#include <string>
#include <vector>
#include <map>

struct User {
	std::string valid_email;
	bool need_to_unsubscribe;
};

std::vector<std::string> NewsletterSubscribeHandler(std::vector<User> job, std::vector<std::string> emails_db) {
	std::map<std::string, bool> marker;
	std::vector<std::string> new_emails_db;

	for (const std::string &email : emails_db) {
		marker[email] = true;
	}

	for (const User &person : job) {
		marker[person.valid_email] = !person.need_to_unsubscribe;
	}

	for (const std::pair<std::string, bool> item : marker) {
		if (item.second) {
			new_emails_db.push_back(item.first);
		}
	}

	return new_emails_db;
}

#include <cassert>
int main() {
	// TEST
	std::vector<User> input1 { User { valid_email: std::string("test2@example.com"), need_to_unsubscribe: false } };
	std::vector<std::string> input2 { std::string("test@example.com") };
	std::vector<std::string> output { std::string("test2@example.com"), std::string("test@example.com") };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { User { valid_email: std::string("test@example.com"), need_to_unsubscribe: true } };
	input2 = { std::string("test@example.com") };
	output = { };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { User { valid_email: std::string("test@example.xyz"), need_to_unsubscribe: true } };
	input2 = { std::string("test@example.com") };
	output = { std::string("test@example.com") };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { User { valid_email: std::string("test@example.com"), need_to_unsubscribe: false } };
	input2 = { };
	output = { std::string("test@example.com") };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { User { valid_email: std::string("test@example.com"), need_to_unsubscribe: true }, User { valid_email: std::string("test@example.com"), need_to_unsubscribe: false } };
	input2 = { std::string("test@example.com") };
	output = { std::string("test@example.com") };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { User { valid_email: std::string("test@example.com"), need_to_unsubscribe: false }, User { valid_email: std::string("test@example.com"), need_to_unsubscribe: true } };
	input2 = { std::string("test@example.com") };
	output = { };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { User { valid_email: std::string("test@example.com"), need_to_unsubscribe: true }, User { valid_email: std::string("abc@example.com"), need_to_unsubscribe: true } };
	input2 = { };
	output = { };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = { };
	input2 = { std::string("test@example.com") };
	output = { std::string("test@example.com") };
	assert(NewsletterSubscribeHandler(input1, input2) == output);
	// TEST_END
}
