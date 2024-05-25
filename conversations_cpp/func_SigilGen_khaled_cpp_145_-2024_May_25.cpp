/***
 * Prompt:




 khaled_cpp_145_-2024_May_25: 62236094-19ea-4c09-ae45-34c58b563442

 func_SigilGen_khaled_cpp_145_-2024_May_25



Create a C++ function called SigilGen that takes an input called text that should contain only alpha characters and spaces. The function should create a sigil by writing out a specific desire (e.g. "I HAVE WONDERFUL FRIENDS WHO LOVE ME"), remove all vowels, remove any duplicate letters (keeping the last occurrence), and then design a glyph from what remains, so for the above example after removing the duplicate letters should be "AUFRINDSWHLOVME" and after removing all vowels, leaving us with final output which is "FRNDSWHLVM". This function should return another text of type std::string which does not contain any spaces and be in uppercase. Please note that for duplicate letters the last one is kept and don't forget to validate the input.




.


 */

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

std::string SigilGen(std::string text) {
  if (text.empty()) {
    throw std::invalid_argument("text can't be empty");
  }

  const auto IsVowel = [&](char character) {
    return (character == 'a' || character == 'e' || character == 'i' ||
            character == 'o' || character == 'u')
               ? true
               : false;
  };

  std::string result;

  std::map<char, bool> r_map;

  for (int idx = text.size() - 1; idx >= 0; idx--) {

    if (!std::isalpha(text[idx]) && text[idx] != ' ') {
      throw std::invalid_argument("only allow alpha characters and spaces");
    }

    char character = std::tolower(text[idx]);

    if (!(IsVowel(character) || character == ' ' ||
          r_map.find(character) != r_map.end())) {
      r_map[character] = true;

      result += toupper(character);
    }
  }

  std::reverse(result.begin(), result.end());

  return result;
}

#include <cassert>
int main() {
  // TEST
  assert(SigilGen("i am healthy") == "MLTHY");
  // TEST_END

  // TEST
  assert(SigilGen(" ") == "");
  // TEST_END

  // TEST
  assert(SigilGen("I FOUND MY SOULMATE") == "FNDYSLMT");
  // TEST_END

  // TEST
  assert(SigilGen("I have a job I enjoy and it pays well") == "HVBJNDTPYSWL");
  // TEST_END

  // TEST
  try {
    SigilGen("");
    assert(false);
  } catch (const std::exception &e) {
    assert(true);
  }
  // TEST_END

  // TEST
  try {
    SigilGen("$@");
    assert(false);
  } catch (const std::exception &e) {
    assert(true);
  }
  // TEST_END
}