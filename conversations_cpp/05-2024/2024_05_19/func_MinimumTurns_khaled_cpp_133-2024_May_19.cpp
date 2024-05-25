/***
 * Prompt:




 khaled_cpp_133-2024_May_19: 6bf5c07b-4ebe-4d84-aab6-f5e14a0e0112

 func_MinimumTurns_khaled_cpp_133-2024_May_19


Create a C++ function called MinimumTurns that takes two non-empty inputs (std::string current, std::string target). Both inputs should contain only digits characters and both lengths should be equal. This function should calculate the smallest number of turns it takes to transform the lock from the current combination to the target combination and return a number of type int that represents the minimum number of turns. Note that in 1 turn you change e.g. "2" to "3" or "1", and "3" to "2" or "4", and "0" to "9" or "1" and so on. Please don't forget to validate the input.



 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

struct Lock {
    int data;
    Lock *next, *back;

    Lock(int data) { this->data = data; }

    Lock *ResetPosition(int num) {
        Lock *lock = this;
        while (lock->data != num) {
            lock = lock->next;
        }
        return lock;
    }
};

int MinimumTurns(std::string current, std::string target) {

    if (current.empty()) {
        throw std::invalid_argument("current must not be empty");
    }

    if (target.empty()) {
        throw std::invalid_argument("target must not be empty");
    }

    if (target.length() != current.length()) {
        throw std::invalid_argument("target and current must be with same length");
    }

    Lock *first_lock = new Lock(0);
    Lock *lock = first_lock;
    for (int idx = 1; idx <= 9; idx++) {
        Lock *newLock = new Lock(idx);
        lock->next = newLock;
        newLock->back = lock;
        lock = lock->next;
    }
    first_lock->back = lock;
    lock->next = first_lock;

    int result = 0;

    for (int i = 0; i < current.size(); i++) {

        if (!isdigit(current[i]) || !isdigit(target[i])) {
            throw std::invalid_argument("only digits are allowed");
        }

        int curr = static_cast<int>(current[i] - '0');
        int targ = static_cast<int>(target[i] - '0');

        lock = lock->ResetPosition(curr);

        int count_forward = 0;
        while (lock->data != targ) {
            lock = lock->next;
            count_forward++;
        }

        lock = lock->ResetPosition(curr);

        int count_backward = 0;
        while (lock->data != targ) {
            lock = lock->back;
            count_backward++;
        }

        result += count_forward < count_backward ? count_forward : count_backward;
    }

    lock = first_lock;
    do {
        Lock *to_delete = lock;
        lock = lock->next;
        delete to_delete;
    } while (lock != first_lock);

    return result;
}

#include <cassert>
int main() {
    // TEST
    assert((MinimumTurns("2", "3") == 1));
    // TEST_END

    // TEST
    assert((MinimumTurns("2", "2") == 0));
    // TEST_END

    // TEST
    assert((MinimumTurns("3", "2") == 1));
    // TEST_END

    // TEST
    assert((MinimumTurns("1", "9") == 2));
    // TEST_END

    // TEST
    assert((MinimumTurns("0", "9") == 1));
    // TEST_END

    // TEST
    assert((MinimumTurns("4089", "6672") == 10));
    // TEST_END

    // TEST
    assert((MinimumTurns("11111", "11000") == 3));
    // TEST_END

    // TEST
    assert((MinimumTurns("239", "498") == 7));
    // TEST_END

    // TEST
    try {
        MinimumTurns("", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinimumTurns("34", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinimumTurns("3", "");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinimumTurns("", "");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        MinimumTurns("@", "1");
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}