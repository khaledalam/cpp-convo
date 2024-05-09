/***
 * Prompt:




 khaled_cpp_17_2024_19_04: 8a205571-473c-408f-b157-61790e5cabc7


 func_SoftwareUpgrader_khaled_cpp_17_2024_19_04




 Design me a C++ function named SoftwareUpgrader that accepts two inputs both of them of type std::vector<Software> where Software is a struct type that contains a string member called name and 3 integer members called major, minor and patch. First input called recent_softwares which contains list of Software struct which represents the recent versions of the softwares. Second input called installed_softwares which contains list of the current installed softwares. The function should return list of outdated softwares of type std::vector<Software>. Please note that Software is outdated if its recent version higher than the current installed one. Don't forget to validate that recent softwares list always higher than the installed ones, Last note if some software has no recent versions that means this software is not outdated.



 */

#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

struct Software {
	std::string name;
	int major, minor, patch;

	bool operator ==(const Software &another) const {
		return name == another.name && major == another.major && minor == another.minor && patch == another.patch;
	}
};

bool ValidateVersionsComparison(const Software &before, const Software &after) {
	if (before.major > after.major) {
		return false;
	}

	if (before.major == after.major) {
		if (before.minor > after.minor) {
			return false;
		} else if (before.minor == after.minor && before.patch > after.patch) {
			return false;
		}
	}

	return true;
}

std::vector<Software> SoftwareUpgrader(std::vector<Software> recent_softwares, std::vector<Software> installed_softwares) {
	std::vector<Software> outdated;
	std::map<std::string, Software> recent_mapper;

	for (const Software &software : recent_softwares) {
		recent_mapper[software.name] = software;
	}

	for (const Software &software : installed_softwares) {

		if (recent_mapper.find(software.name) != recent_mapper.end() && !ValidateVersionsComparison(software, recent_mapper[software.name])) {
			throw std::invalid_argument("invalid software name");
		}

		if (!ValidateVersionsComparison(recent_mapper[software.name], software)) {
			outdated.push_back(software);
		}
	}

	return outdated;
}

#include <cassert>
int main() {
	// TEST
	std::vector<Software> input_1 = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	std::vector<Software> input_2 = { Software { name: "skype", major: 0, minor: 1, patch: 0 } };
	std::vector<Software> output = { Software { name: "skype", major: 0, minor: 1, patch: 0 } };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 1, minor: 1, patch: 0 } };
	input_2 = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	output = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 1, minor: 0, patch: 1 } };
	input_2 = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	output = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 1, minor: 0, patch: 0 }, Software { name: std::string("yahoo"), major: 4, minor: 2, patch: 0 } };
	input_2 = { Software { name: "skype", major: 1, minor: 0, patch: 0 }, Software { name: std::string("yahoo"), major: 4, minor: 1, patch: 0 } };
	output = { Software { name: "yahoo", major: 4, minor: 1, patch: 0 } };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 1, minor: 0, patch: 1 }, Software { name: std::string("yahoo"), major: 4, minor: 2, patch: 0 }, Software { name: std::string("facebook"), major: 1, minor: 5, patch: 0 } };
	input_2 = { Software { name: "skype", major: 1, minor: 0, patch: 0 }, Software { name: std::string("yahoo"), major: 4, minor: 1, patch: 0 } };
	output = { Software { name: "skype", major: 1, minor: 0, patch: 0 }, Software { name: std::string("yahoo"), major: 4, minor: 1, patch: 0 } };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { };
	input_2 = { };
	output = { };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { };
	input_2 = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	output = { };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 0, minor: 0, patch: 1 }, Software { name: std::string("yahoo"), major: 4, minor: 2, patch: 0 } };
	input_2 = { Software { name: "skype", major: 0, minor: 0, patch: 0 } };
	output = { Software { name: "skype", major: 0, minor: 0, patch: 0 } };
	assert(SoftwareUpgrader(input_1, input_2) == output);
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	input_2 = { Software { name: "skype", major: 4, minor: 1, patch: 0 } };
	try {
		SoftwareUpgrader(input_1, input_2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "invalid software name");
	}
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	input_2 = { Software { name: "skype", major: 1, minor: 1, patch: 0 } };
	try {
		SoftwareUpgrader(input_1, input_2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "invalid software name");
	}
	// TEST_END

	// TEST
	input_1 = { Software { name: "skype", major: 1, minor: 0, patch: 0 } };
	input_2 = { Software { name: "skype", major: 1, minor: 0, patch: 1 } };
	try {
		SoftwareUpgrader(input_1, input_2);
		assert(false);
	} catch (const std::invalid_argument &e) {
		assert(std::string(e.what()) == "invalid software name");
	}
	// TEST_END
}
