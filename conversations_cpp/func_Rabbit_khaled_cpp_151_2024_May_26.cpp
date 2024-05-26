/***






 khaled_cpp_151_2024_May_26: 564a2b9c-491f-462a-aa02-973d311a3085

 func_Rabbit_khaled_cpp_151_2024_May_26
 




Create a C++ function called Rabbit that takes 3 inputs of type long long int called males, female, and target.

Rabbits are known for their fast breeding. Starting with a small population of some male and female rabbits we have to figure out how long it will take for them to outnumber humans 2:1. 

Every month a fertile female will have 14 offspring (5 males and 9 females). A female rabbit is fertile when it has reached the age of 4 months, they never stop being fertile. Rabbits die at the age of 8 years (96 months). 

The initial rabbits will always be 2 months old and fertile females will always produce 14 offspring (5 male, 9 female). Every month that passes things should be done in this order:

- Fertile female reproduce (so 7 years & 11 months old will reproduce)
- Rabbits age (except newborn) (and rabbits reaching 8 years will die, the 7 years & 11 months old will die)


For example, if males are 2 and females are 4 and the target is 1000000000 the output should be 32

This function should return a number of type int that represents the number of months to hit the target.






*/

#include <iostream>
#include <stdexcept>
#include <string>

int Rabbit(long long int male, long long int female, long long int target) {
    const int inital_batch_age = 2;
    const int ages = 96;
    const int age_alive_limit = 95;
    const int age_fertile_begin = 4;
    const int new_males_rate = 5;
    const int new_females_rate = 9;

    if (female < 0 || male < 0 || ((male + female) < target && female == 0)) {
        throw std::invalid_argument("not allowed");
    }

    int month = 0;
    long long int females[ages] = {0};
    long long int males[ages] = {0};

    females[inital_batch_age] = female;
    males[inital_batch_age] = male;

    while (true) {
        long int alive_rabbits = 0;

        for (int idx = age_alive_limit; idx >= 0 && alive_rabbits < target; idx--) {

            long int newBornFemale = 0;
            long int newBornMale = 0;
            if (idx > age_fertile_begin) {
                newBornFemale = females[idx] * new_females_rate;
                newBornMale = females[idx] * new_males_rate;
            }

            alive_rabbits += females[idx] + males[idx];

            const int next_gen = idx + 1;
            females[next_gen] = females[idx];
            males[next_gen] = males[idx];
            females[idx] = 0;
            males[idx] = 0;

            females[0] += newBornFemale;
            males[0] += newBornMale;
        }

        if (alive_rabbits >= target) {
            return month;
        }

        month++;
    }
}

#include <cassert>
int main() {
    // TEST
    assert(Rabbit(2, 4, 6) == 0);
    // TEST_END

    // TEST
    assert(Rabbit(2, 4, 1000000000) == 32);
    // TEST_END

    // TEST
    assert(Rabbit(2, 4, 15000000000) == 36);
    // TEST_END

    // TEST
    try {
        Rabbit(5, 0, 6);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

     // TEST
    try {
        Rabbit(-1, 2, 6);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}