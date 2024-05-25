/***
 * Prompt:




 khaled_cpp_131-2024_May_19: 8f1bf9fc-748b-4a2d-afad-5b1e2645f5ed

 func_Jose_khaled_cpp_131-2024_May_19

Create a C++ function called Jose that takes two input numbers of type int, both inputs can't be less than 1. The first input called n_soldiers represents the number of soldiers, the second input called interval represents the interval at which they are killed. 

Back in Roman times, There were 41 soldiers arranged in a circle. Every third soldier is to be killed by their captors, continuing around the circle until only one soldier remains. He is to be freed. Assuming you would like to stay alive, at what position in the circle would you stand? 

This function should return another number of type int that represents the position of the fortunate survivor. Please don't forget to validate the input.



 */

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct Soldier {
    int position = 0;
    bool alive = true;
    Soldier *next = nullptr;

    Soldier(int pos) { this->position = pos; }

    Soldier *kill(int interval) {
        int count = 1;
        Soldier *soldierToKill = this;
        while (count < interval) {
            soldierToKill = soldierToKill->next;
            count = (soldierToKill->alive) ? count + 1 : count;
        }
        soldierToKill->alive = false;

        Soldier *nextAlive = soldierToKill->next;
        while (!nextAlive->alive) {
            nextAlive = nextAlive->next;
        }

        return nextAlive;
    }
};

int Jose(int n_soldiers, int interval) {
    if (n_soldiers < 1) {
        throw std::invalid_argument("n_soldiers cannot be less than 1");
    }

    if (interval < 1) {
        throw std::invalid_argument("interval cannot be less than 1");
    }

    int survivorPosition;

    Soldier *firstSoldier = new Soldier(1);
    Soldier *soldier = firstSoldier;
    for (int i = 2; i <= n_soldiers; i++) {
        soldier->next = new Soldier(i);
        soldier = soldier->next;
    }
    soldier->next = firstSoldier;

    soldier = firstSoldier;
    int kills = 0;
    while (++kills <= n_soldiers - 1) {
        soldier = soldier->kill(interval);
    }

    survivorPosition = soldier->position;

    soldier = firstSoldier;
    do {
        Soldier *toDelete = soldier;
        soldier = soldier->next;
        delete toDelete;
    } while (soldier != firstSoldier);

    return survivorPosition;
}

#include <cassert>
int main() {
    // TEST
    assert((Jose(41, 3) == 31));
    // TEST_END

    // TEST
    assert((Jose(35, 11) == 18));
    // TEST_END

    // TEST
    assert((Jose(2, 2) == 1));
    // TEST_END

    // TEST
    assert((Jose(11, 1) == 11));
    // TEST_END

    // TEST
    assert((Jose(5, 2) == 3));
    // TEST_END

    // TEST
    try {
        Jose(0, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Jose(-1, 1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Jose(1, 0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        Jose(1, -4);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_EN
}