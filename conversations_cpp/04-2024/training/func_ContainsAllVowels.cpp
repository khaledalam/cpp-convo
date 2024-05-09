/*
 *
 * Create a C++ function named TransposeAndFlatten that transposes a given matrix and then flattens it into a single vector.
 * The function should accept a vector<vector<int>> representing the matrix. It should also return a vector<int> containing the transposed and flattened data.
 *  Please note that this matrix is not necessarily square,
 *  but please remember to ensure that the function handles empty matrices and non-rectangular matrices by throwing an exception.
 *
 *
 *
 * Prompt:
 *
 * Create a C++ function named ContainsAllVowels that check if a given sentence contains all vowel letters or not.
 * The function should accept a string representing the sentence. It should return a boolean true or false.
 * Note that vowel letters are a, e, i, o, u. The given sentence can be empty and can contains digits, uppercase and lowercase letters.
 */

//#include <bits/stdc++.h>
//using namespace std;
#include <string>
#include <map>
#include <cassert>

bool ContainsAllVowels(const std::string &sentence) {
	std::map<char, int> vowelsMarker;
	for (const char &ch : { 'a', 'e', 'i', 'o', 'u' }) {
		vowelsMarker[ch] = 1;
	}

	for (const char &ch : sentence) {
		vowelsMarker[tolower(ch)] = 0;
	}

	for (const char &ch : { 'a', 'e', 'i', 'o', 'u' }) {
		if (vowelsMarker[ch] == 1) {
			return false;
		}
	}

	return true;
}

int main() {

//	throw invalid_argument("fsa");

// Function Signature:
// bool ContainsAllVowels(const std::string &sentence)

// Docstring (Optional):
// This function takes a sentence represented as a string, checks if this sentence contains all vowel letters or not.

// TEST
	assert(ContainsAllVowels(" ") == false);
	// TEST_END

	// TEST
	assert(ContainsAllVowels("123") == false);
	// TEST_END

	// TEST
	assert(ContainsAllVowels("AEIOU") == true);
	// TEST_END

	// TEST
	assert(ContainsAllVowels("aeioU") == true);
	// TEST_END

	// TEST
	assert(
			ContainsAllVowels(
					"This sentence COntains all vowel letters for sure.")
					== true);
	// TEST_END

	// TEST
	assert(
			ContainsAllVowels(
					"This sentence does not contains all vowel letters.")
					== false);
	// TEST_END

}
