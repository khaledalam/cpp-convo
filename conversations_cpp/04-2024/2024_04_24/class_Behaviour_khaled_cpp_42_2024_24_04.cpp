/***
 * Prompt:





 khaled_cpp_42_2024_24_04: f4cc2a12-1c56-40b5-80b1-bfb572774b01

 class_Behaviour_khaled_cpp_42_2024_24_04

 Design a C++ class called Behaviour which contains a function called UB, it accepts an input of type std::vector<Instruction> where Instruction is a struct type that contains "name" member of type std::string and "address_index" member of type int which refers to the index in the memory that we want to perform the action on it and it should be zero or positive number. Instruction name should be one of these 3 values "add", "remove" and "shrink". Action "add" means append 1 element to the memory of address address_index and if this address is not existed append a new empty std::vector<int> to that memory index and set the address_index to this position of the memory, action "remove" means remove last element from the memory of address address_index and if the memory of address address_index is empty already throw an invalid_argument exception, action "shrink" will shrink the memory of address address_index to its actual size to make sure this memory of address address_index has no UB if it's empty. To give you an idea about an example of UB when we empty some container after adding some values into it, the memory address of first item of this container still hold the old value although the container size is 0 but the container capacity is still not 0, so accessing first element of the container after empty the whole container will cause UB "Undefined Behaviour" if we are in the same scope, because go outside scope will already auto destroy the container, so shrink_to_fit will make the capacity 0 if the size is 0. UB method should return boolean true if after performing the input instructions, the memory has no UB at all otherwise return false. Please don't forget to validate the inputs.


 */

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>

struct Instruction {
	std::string name;
	int address_index;
};

class Behaviour {
private:
	std::vector<std::vector<int>> memory;
public:
	bool UB(std::vector<Instruction> instructions) {
		for (Instruction &instruction : instructions) {
			if (instruction.address_index >= memory.size()) {
				instruction.address_index = (int) memory.size();
				memory.push_back(std::vector<int>());
			}

			if (instruction.name != "add" && instruction.name != "remove" && instruction.name != "shrink") {
				throw std::invalid_argument("Invalid input");
			}

			if (instruction.address_index < 0) {
				throw std::invalid_argument("Invalid input");
			}

			if (instruction.name == "add") {
				memory[instruction.address_index].push_back(1);
			} else if (instruction.name == "remove") {
				if (memory[instruction.address_index].empty()) {
					throw std::invalid_argument("Invalid input");
				}
				memory[instruction.address_index].pop_back();
			} else {
				memory[instruction.address_index].shrink_to_fit();
			}
		}

		for (const std::vector<int> &item : memory) {
			if (item.empty() && item.capacity()) {
				return false;
			}
		}

		return true;
	}
	void MemoryReset() {
		memory.clear();
		memory.shrink_to_fit();
	}
};

#include <cassert>
int main(int argc, const char *argv[]) {
	Behaviour behaviour;

	// TEST
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 0 } }) == false));
	assert((behaviour.UB( { Instruction { .name = "shrink", .address_index = 0 } }) == true));
	// TEST_END

	// TEST
	behaviour.MemoryReset();
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 0 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 0 } }) == false));
	assert((behaviour.UB( { Instruction { .name = "shrink", .address_index = 0 } }) == true));
	// TEST_END

	// TEST
	behaviour.MemoryReset();
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 1 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 0 } }) == false));
	assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 1 } }) == false));
	assert((behaviour.UB( { Instruction { .name = "shrink", .address_index = 0 } }) == false));
	assert((behaviour.UB( { Instruction { .name = "shrink", .address_index = 1 } }) == true));
	// TEST_END

	// TEST
	behaviour.MemoryReset();
	assert((behaviour.UB( { }) == true));
	// TEST_END

	// TEST
	behaviour.MemoryReset();
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 1 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
	assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 1 } }) == false));
	assert((behaviour.UB( { Instruction { .name = "shrink", .address_index = 0 } }) == false));
	assert((behaviour.UB( { Instruction { .name = "shrink", .address_index = 1 } }) == true));
	// TEST_END

	// TEST
	try {
		behaviour.MemoryReset();
		assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
		assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 } }) == true));
		assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 0 } }) == true));
		assert((behaviour.UB( { Instruction { .name = "remove", .address_index = 0 } }) == false));
		assert((behaviour.UB( { Instruction { .name = "shrink", .address_index = 0 } }) == true));
	} catch (const std::exception &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

// TEST
	try {
		behaviour.MemoryReset();
		assert((behaviour.UB( { Instruction { .name = "ADD", .address_index = 0 } }) == true));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		behaviour.MemoryReset();
		assert((behaviour.UB( { Instruction { .name = "add", .address_index = 0 }, Instruction { .name = "remove", .address_index = 2 } }) == false));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		behaviour.MemoryReset();
		assert((behaviour.UB( { Instruction { .name = "clear", .address_index = 0 } }) == true));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END

	// TEST
	try {
		behaviour.MemoryReset();
		assert((behaviour.UB( { Instruction { .name = "add", .address_index = -10 } }) == true));
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "Invalid input");
	}
	// TEST_END
}

