/***


 khaled_cpp_211_2024_June_09: d4a17a50-82b1-4dfa-b4ad-c306db4084f0

 func_EulerTotient_khaled_cpp_211_2024_June_09


*/

/*

Design me a C++ function called EulerTotient that takes an integer num. The function should return an integer representing the value of Euler's Totient function φ(n), which is the number of integers up to num that are coprime with num. Please don't forget to validate the input.


*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

int EulerTotient(int num) {
    if (num <= 0) {
        throw std::invalid_argument("num should be greater than 0");
    }

    int result = num;
    for (int iii = 2; iii * iii <= num; ++iii) {
        if (num % iii == 0) {
            while (num % iii == 0) {
                num /= iii;
            }
            result -= result / iii;
        }
    }
    if (num > 1) {
        result -= result / num;
    }

    return result;
}

#include <cassert>
int main() {
    // TEST
    int result1 = EulerTotient(9);
    assert(result1 == 6);
    // TEST_END

    // TEST
    int result2 = EulerTotient(10);
    assert(result2 == 4);
    // TEST_END

    // TEST
    int result3 = EulerTotient(13);
    assert(result3 == 12);
    // TEST_END

    // TEST
    int result4 = EulerTotient(1);
    assert(result4 == 1);
    // TEST_END

    // TEST
    try {
        EulerTotient(0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
