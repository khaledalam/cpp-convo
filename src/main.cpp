/***
 * Prompt:




 khaled_cpp_104-2024_May_14:


ID: PI-0272-00202-2
Category: Math


Write a function that accepts a string representing a coin toss pattern (e.g., 'HHTTHHTT') and calculates the probability of obtaining that pattern within n tosses. The output should be an exact fraction. The function should raise a ValueError if the pattern is not valid.


 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


#include <cassert>
int main() {
    WeddingGuestList wedding_guest_list;

    // TEST
    assert(wedding_guest_list.CountNumberOfGuests() == 0);
    // TEST_END

    // TEST
    wedding_guest_list.AddInvitation(Invitations{.name = "test", .num_of_people = 2, .is_attending = true});
    assert(wedding_guest_list.CountNumberOfGuests() == 2);
    // TEST_END

    // TEST
    wedding_guest_list.AddInvitation(Invitations{.name = "test a", .num_of_people = 2, .is_attending = true});
    assert(wedding_guest_list.CountNumberOfGuests() == 4);
    // TEST_END

    // TEST
    wedding_guest_list.AddInvitation(Invitations{.name = "AB", .num_of_people = 1, .is_attending = true});
    assert(wedding_guest_list.CountNumberOfGuests() == 5);
    // TEST_END

    // TEST
    wedding_guest_list.AddInvitation(Invitations{.name = "ABcd", .num_of_people = 1, .is_attending = false});
    assert(wedding_guest_list.CountNumberOfGuests() == 5);
    // TEST_END

    // TEST
    try {
        wedding_guest_list.AddInvitation(Invitations{.name = "test A", .num_of_people = 3, .is_attending = true});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        wedding_guest_list.AddInvitation(Invitations{.name = "", .num_of_people = 3, .is_attending = true});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        wedding_guest_list.AddInvitation(Invitations{.name = "abc", .num_of_people = -1, .is_attending = true});
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    // TEST_END
}
