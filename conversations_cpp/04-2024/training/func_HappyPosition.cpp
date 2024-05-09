#define ALIGNOF(...) alignof(__VA_ARGS__)
/*
 *c0ec49e4-6735-4968-925f-b72bb90ba20c
 *
 *
 * Prompt:
 *
 * I need a C++ function named HappyPosition that accepts one input called track of type string.
 * The input consists of only dot "." and hash "#" symbols.
 * Note that the hash symbol represents a block, please also note that the input can contains multiple blocks and can has no blocks at all.
 * This function should returns boolean false if there is any block located at an even position otherwise return true.
 * Try to use recursion in your solution and take in your consideration that index of first character in the input is 1 not 0 (1-based), Last note please don't forget to validate the allowed characters in the input.

 *
 */

#include <cassert>
#include <string>

bool IsInvalidTrack(const std::string &track, int idx) {
	if (idx >= track.length()) {
		return false;
	}
	return (track[idx] != '.' && track[idx] != '#') or (track[idx] == '#' && (((idx + 1) & 1) == 0)) or IsInvalidTrack(track, idx + 1);
}

bool HappyPosition(std::string track) {
	return !IsInvalidTrack(track, 0);
}

int main() {
	// TEST
	assert(HappyPosition("..#") == true);
	// TEST_END

	// TEST
	assert(HappyPosition(".#.") == false);
	// TEST_END

	// TEST
	assert(HappyPosition("#") == true);
	// TEST_END

	// TEST
	assert(HappyPosition("..#K") == false);
	// TEST_END

	// TEST
	assert(HappyPosition("....") == true);
	// TEST_END

	// TEST
	assert(HappyPosition("##") == false);
	// TEST_END
	// TEST
	assert(HappyPosition("#.#") == true);
	// TEST_END
}
