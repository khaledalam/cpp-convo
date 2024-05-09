/*
 *
 * e3027e18-1de1-4b4e-9411-1b470bd38fe8
 *
 * Prompt:
 *
 * Design a C++ function named IsValidSoftwareVersion that accepts one input parameter of string type consist of digits and lowercase letters only.
 * This input is expected to represent a software version string. The function should returns boolean of true if the input string is a valid software version otherwise returns false.
 * Please consider that the valid pattern or the scheme of a valid software version consists of prefix of small letter "v" and three-part version numbers separated by dot,
 * also remember each part of version number should be between 0 and 99. Note that 00, 01, 02 and so on are invalid as part version number.
 *
 *
 */

// Function Signature:
// bool IsValidSoftwareVersion(std::string software_version)
#include <cassert>
#include <string>
#include <sstream>

bool IsValidSoftwareVersion(std::string software_version) {
	if (software_version.length() < 1 || software_version[0] != 'v') {
		return false;
	}

	int dots = 0;
	for (char &ch : software_version) {
		if (ch == '.') {
			dots++, ch = ' ';
		}
	}

	if (dots != 2) {
		return false;
	}

	software_version[0] = ' ';

	std::stringstream ss;
	ss << software_version;
	std::string temp_string;

	while (ss >> temp_string) {
		if (temp_string.length() < 1 || temp_string.length() > 2 || (temp_string.length() == 2 && temp_string[0] == '0')) {
			return false;
		}
	}

	return true;
}

int main() {
	// TEST
	assert(IsValidSoftwareVersion("v1.0.0") == true);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("v1.99.0") == true);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("v1.999.0") == false);
	// TEST_END
	// TEST
	assert(IsValidSoftwareVersion("h1.9.0") == false);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("") == false);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("v1.04") == false);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("v1.40.0") == true);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("v1.000.0") == false);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("v1.0") == false);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("V1.0.3") == false);
	// TEST_END

	// TEST
	assert(IsValidSoftwareVersion("v0.0.0") == true);
	// TEST_END
}
