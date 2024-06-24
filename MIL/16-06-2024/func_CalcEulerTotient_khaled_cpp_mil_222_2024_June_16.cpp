/***


 khaled_cpp_mil_222_2024_June_16: 7ed97d5c-7139-4ff0-a752-a381a29d2ecd

 func_CalcEulerTotient_khaled_cpp_mil_222_2024_June_16
 


*/

/*




Design me a C++ function called CalcEulerTotient that takes an integer num. The function should return an integer representing the value of Euler's Totient function φ(n), which is the number of integers up to num that are coprime with num.




*/

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

int CalcEulerTotient(int num) {
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
    int result1 = CalcEulerTotient(9);
    assert(result1 == 6);
    // TEST_END

    // TEST
    int result2 = CalcEulerTotient(10);
    assert(result2 == 4);
    // TEST_END

    // TEST
    int result3 = CalcEulerTotient(13);
    assert(result3 == 12);
    // TEST_END

    // TEST
    int result4 = CalcEulerTotient(1);
    assert(result4 == 1);
    // TEST_END

    // TEST
    try {
        CalcEulerTotient(0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
