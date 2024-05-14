/***
 * Prompt:




 khaled_cpp_94-2024_May_11: 142eb395-e806-4e93-95a5-7168d53565c7

 func_CanBuyBook_khaled_cpp_94-2024_May_11

 
 Create me a C++ function called CanBuyBook which accepts three inputs, the first input is a non-empty list called books of type std::vector<Book> where Book is a struct that contains 2 members called name of type std::string and available_quantity of type int, second input called transactions of type std::vector<Transaction> where Transaction is a struct that contains 2 members called book_name of type std::string and quantity of type int, third input called book_want_to_buy of type std::string which represent the name of the book that we want to buy. Input books represent list of initial books that we have in the store and transactions input represents the purchases. This function should return a Boolean true if we can buy the book_want_to_buy after the second input transactions occurs otherwise return false. Please note that any book name can consist of any type of character including spaces and special characters and can't be empty string also book available_quantity can be less negative, zero, or positive number, and transaction quantity can't be less than 1.




 */

#include <algorithm>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

struct Book {
    std::string name;
    int available_quantity;
};

struct Transaction {
    std::string book_name;
    int quantity;
};

bool CanBuyBook(const std::vector<Book> &books, const std::vector<Transaction> &transactions, const std::string &book_want_to_buy) {
    if (books.empty()) {
        throw std::invalid_argument("books can't be empty");
    }

    if (transactions.empty()) {
        throw std::invalid_argument("transactions can't be empty");
    }

    if (book_want_to_buy.length() < 1) {
        throw std::invalid_argument("book_want_to_buy name can't be empty");
    }

    std::map<std::string, int> map_available;

    for (const Book &book : books) {
        if (book.name.length() < 1) {
            throw std::invalid_argument("book name can't be empty");
        }

        map_available[book.name] = book.available_quantity;
    }

    for (const Transaction &transaction : transactions) {
        if (transaction.book_name.length() < 1) {
            throw std::invalid_argument("transaction book_name can't be empty");
        }
        if (transaction.quantity < 1) {
            throw std::invalid_argument("transaction quantity can't be less than 1");
        }

        map_available[transaction.book_name] -= transaction.quantity;
    }

    if (map_available.find(book_want_to_buy) == map_available.end()) {
        return false;
    }

    return map_available[book_want_to_buy] > 0;
}

#include <cassert>
int main() {
    // TEST
    assert(CanBuyBook({{"Test", 2}, {"Again", 1}}, {{"Test", 1}}, "Test") == true);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"Test", 1}, {"Again", 1}}, {{"Test", 1}}, "Test") == false);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A B", 5}, {"Again", 1}}, {{"A B", 1}}, "A B") == true);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A B", 5}, {"Again", 1}}, {{"A B", 1}}, "A b") == false);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A", 2}, {"B", 1}}, {{"A", 1}}, "A") == true);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A@b#", 2}, {"Again", 1}}, {{"A@b#", 1}}, "test") == false);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A@b#", 2}, {"Again", 1}}, {{"A@b#", 1}}, "test") == false);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A@b#", 2}, {"Again", 1}, {"SD", 50}}, {{"SD", 11}}, "SD") == true);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A@b#", 0}, {"Again", 1}, {"SD", 50}}, {{"A@b#", 11}}, "A@B#") == false);
    // TEST_END

    // TEST
    assert(CanBuyBook({{"A@b#", -3}, {"Again", 1}}, {{"A@b#", 11}}, "A@B#") == false);
    // TEST_END

    // TEST
    try {
        CanBuyBook({}, {{"Test", 1}}, "Test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanBuyBook({{"test", 1}}, {}, "Test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanBuyBook({{"Test", 1}}, {{"Test", 1}}, "");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanBuyBook({{"", 1}}, {{"Test", 1}}, "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanBuyBook({{"tes", 1}}, {{"", 1}}, "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        CanBuyBook({{"fsdfds", 1}}, {{"Test", -1}}, "test");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
