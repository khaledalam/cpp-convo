/***






 khaled_cpp_150_-2024_May_26: 1d588fef-3a8e-43cc-9bba-61a1bf7b8a6f

 func_EncryptData_khaled_cpp_150_-2024_May_26

Create two C++ functions, the first function is called EncryptData which takes 2 non-empty inputs of type std::sting called
plain_text and key, second function called DecryptData which takes 2 non-empty inputs of type std::sting called
encrypted_text and key.

These 2 methods should help with encrypting and decrypting text using the Vigenère cipher method.

For example, if the encrypting key is "rag" and the plain text is "Meet me in the same place at ten am"
The encrypted text should be "Dekk mk zn zye yrmk glgte gk tke as"
The decrypted text should be "Meet me in the same place at ten am"

The first function should return another text of type std::string which is the encryption of the plain_text input using
Vigenère cipher. The second function should return another text of type std::string which is the description of the
encrypted_text input using Vigenère cipher.

Please don't forget to validate the input.


*/

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string EncryptData(std::string plain_text, std::string key) {
    if (plain_text.empty()) {
        throw std::invalid_argument("plain_text can't be empty");
    }

    if (key.empty()) {
        throw std::invalid_argument("key can't be empty");
    }

    std::stringstream encrypted_stream;
    unsigned int text_len = plain_text.length(), key_len = key.length(), char_index = 0, shift_len = 0;

    for (unsigned int i = 0; i < text_len; ++i) {
        if (isalpha(plain_text[i])) {
            char key_reference_value = (isupper(key[char_index % key_len])) ? 'A' : 'a';

            char reference_value = (isupper(plain_text[i])) ? 'A' : 'a';
            shift_len = key[char_index % key_len] - key_reference_value;
            encrypted_stream << char(((plain_text[i] - reference_value + shift_len) % 26) + reference_value);
            ++char_index;
        } else {
            encrypted_stream << plain_text[i];
        }
    }

    return encrypted_stream.str();
}

std::string DecryptData(std::string encrypted_text, std::string key) {
    if (encrypted_text.empty()) {
        throw std::invalid_argument("encrypted_text can't be empty");
    }

    if (key.empty()) {
        throw std::invalid_argument("key can't be empty");
    }

    std::stringstream decrypted_stream;
    unsigned int text_len = encrypted_text.length(), key_len = key.length(), char_index = 0, shift_len = 0;

    for (unsigned int idx = 0; idx < text_len; ++idx) {
        if (isalpha(encrypted_text[idx])) {
            char key_reference_value = (isupper(key[char_index % key_len])) ? 'A' : 'a';

            char reference_value = (isupper(encrypted_text[idx])) ? 'A' : 'a';

            shift_len = key[char_index % key_len] - key_reference_value;
            decrypted_stream << char((((encrypted_text[idx] - reference_value) + (26 - shift_len)) % 26) +
                                     reference_value);
            ++char_index;
        } else {
            decrypted_stream << encrypted_text[idx];
        }
    }

    return decrypted_stream.str();
}

#include <cassert>
int main() {
    // TEST
    assert(EncryptData("Meet me in the same place at ten am", "rag") == "Dekk mk zn zye yrmk glgte gk tke as");
    assert(DecryptData("Dekk mk zn zye yrmk glgte gk tke as", "rag") == "Meet me in the same place at ten am");
    // TEST_END

    // TEST
    assert(EncryptData("#$12", "rag") == "#$12");
    assert(DecryptData("#$12", "rag") == "#$12");
    // TEST_END

    // TEST
    assert(EncryptData(" ", "rag") == " ");
    assert(DecryptData(" ", "rag") == " ");
    // TEST_END

    // TEST
    try {
        EncryptData("", "test");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        EncryptData("test", "");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        DecryptData("test", "");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        DecryptData("", "test");
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}