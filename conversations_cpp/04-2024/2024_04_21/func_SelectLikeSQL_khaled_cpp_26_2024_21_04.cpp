/***
 * Prompt:




 khaled_cpp_26_2024_21_04: a9226e2f-4f06-42b8-bb51-3e24c71267ee


 func_SelectLikeSQL_khaled_cpp_26_2024_21_04


 Write me a C++ function named SelectLikeSQL that accepts two inputs called query and persons. First input of type std::string which represents the query consists of 5 parts in lower or upper case. first part is word "select", second part should be "*", third part should be word "where", fourth part should be the left operand which can be "position", "ago" or "rank", fifth part should be the operator which can be ">", "<" or "==", last part is the comparing condition value. Second input of type std::vector<Person> where Person is a struct type that contains 3 integer members "position", "age" and "rank". The function should returns another result list of Persons of type std::vector<Person> where the condition in the query applied to the result list. Please don't forget to validate the inputs.



 */

#include <string>
#include <sstream>
#include <vector>

struct Person {
	int position;
	int age;
	int rank;

	bool operator ==(const Person &another) const {
		return position == another.position && age == another.age && rank == another.rank;
	}
};

std::vector<Person> SelectLikeSQL(std::string query, std::vector<Person> persons) {
	std::vector<Person> result;

	if (std::count(query.begin(), query.end(), ' ') != 5) {
		throw std::invalid_argument("Invalid input");
	}

	std::stringstream ss;
	ss << query;
	std::string temp_string, left, op, right;

	ss >> temp_string;
	for (char &ch : temp_string) {
		ch = tolower(ch);
	}

	if (temp_string != "select") {
		throw std::invalid_argument("Invalid input");
	}

	ss >> temp_string;

	if (temp_string != "*") {
		throw std::invalid_argument("Invalid input");
	}

	ss >> temp_string;
	for (char &ch : temp_string) {
		ch = tolower(ch);
	}

	if (temp_string != "where") {
		throw std::invalid_argument("Invalid input");
	}

	ss >> temp_string;
	for (char &ch : temp_string) {
		ch = tolower(ch);
	}
	left = temp_string;

	if (left != "position" && left != "age" && left != "rank") {
		throw std::invalid_argument("Invalid input");
	}

	ss >> temp_string;
	op = temp_string;
	if (op != ">" && op != "<" && op != "==") {
		throw std::invalid_argument("Invalid input");
	}

	ss >> temp_string;
	right = temp_string;
	if (right.empty() || !std::all_of(right.begin(), right.end(), ::isdigit)) {
		throw std::invalid_argument("Invalid input");
	}

	int value = stoi(temp_string);

	for (const Person &person : persons) {
		if (left == "position") {
			if (op == ">") {
				if (person.position > value) {
					result.push_back(person);
				}
			} else if (op == "<") {
				if (person.position < value) {
					result.push_back(person);
				}
			} else {
				if (person.position == value) {
					result.push_back(person);
				}
			}
		} else if (left == "age") {
			if (op == ">") {
				if (person.age > value) {
					result.push_back(person);
				}
			} else if (op == "<") {
				if (person.age < value) {
					result.push_back(person);
				}
			} else {
				if (person.age == value) {
					result.push_back(person);
				}
			}
		} else {
			if (op == ">") {
				if (person.rank > value) {
					result.push_back(person);
				}
			} else if (op == "<") {
				if (person.rank < value) {
					result.push_back(person);
				}
			} else {
				if (person.rank == value) {
					result.push_back(person);
				}
			}
		}
	}

	return result;
}

#include <cassert>
int main() {
	// TEST
	std::string input1 = std::string("SELECT * WHERE age > 10");
	std::vector<Person> input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	std::vector<Person> output = { Person { position: 1, age: 15, rank: 3 } };
	assert(SelectLikeSQL(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("SELECT * WHERE Age < 10");
	input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	output = { };
	assert(SelectLikeSQL(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("SELECT * WHERE age == 10");
	input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 10, rank: 3 } };
	assert(SelectLikeSQL(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("SELECT * where rank > 0");
	input2 = { Person { position: 1, age: 15, rank: 0 }, Person { position: 1, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 10, rank: 3 } };
	assert(SelectLikeSQL(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("SELECT * WHERE position < 18");
	input2 = { Person { position: 1, age: 15, rank: 0 }, Person { position: 19, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 15, rank: 0 } };
	assert(SelectLikeSQL(input1, input2) == output);
	// TEST_END

	// TEST
	input1 = std::string("SELECT * WHERE age <> 10");
	input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 10, rank: 3 } };
	try {
		assert(SelectLikeSQL(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("SELECT *WHERE age > 10");
	input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 10, rank: 3 } };
	try {
		assert(SelectLikeSQL(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("SELECT * when age > 10");
	input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 10, rank: 3 } };
	try {
		assert(SelectLikeSQL(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("");
	input2 = { };
	output = { };
	try {
		assert(SelectLikeSQL(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("SELECT * WHERE name == test");
	input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 10, rank: 3 } };
	try {
		assert(SelectLikeSQL(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	input1 = std::string("SELECT * WHERE ago > 10.6");
	input2 = { Person { position: 1, age: 15, rank: 3 }, Person { position: 1, age: 10, rank: 3 } };
	output = { Person { position: 1, age: 10, rank: 3 } };
	try {
		assert(SelectLikeSQL(input1, input2) == output);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}
