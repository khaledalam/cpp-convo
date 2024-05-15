/***
 * Prompt:




 khaled_cpp_103-2024_May_14: dede242c-004f-45a7-85da-fe5a35f9c209

class_WeddingGuestList_khaled_cpp_103-2024_May_14



ID: PI-0908-00028-7
Category: Lifestyle


I need to make a wedding guest list. Help me create a class WeddingGuestList, which has a list of Invitations. Invitations is a class with
properties such as: name (std::string) non-empty string, num_of_people (int) zero or positive number, is_attending (bool). The
WeddingGuestList has 2 main functions, AddInvitation and CountNumberOfGuests. For AddInvitation, we accept an Invitation as input and output
nothing. This function should add the invitation to the list of invitations on the wedding list. Return an error if a user tries to input a
name that is already on the list. The name is case-insensitive, so "Adam Smith" and "adam smith" would be considered as the same person,
thus returning an error. CountNumberOfGuests has no inputs and returns an int, totaling the amount of guests from all the invitations that
have confirmed that they're attending. If they're not attending the wedding, don't include them in the total number of guests.




 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Invitations {
  public:
    std::string name;
    int num_of_people;
    bool is_attending;
};

class WeddingGuestList {
  public:
    std::vector<Invitations> invitations;

    void AddInvitation(const Invitations &invitation) {
        std::string new_name = invitation.name;

        if (new_name.length() < 1) {
            throw std::invalid_argument("invitation name can't be empty");
        }

        if (invitation.num_of_people < 0) {
            throw std::invalid_argument("invitation num_of_people can't be less than 0");
        }

        for (char &character : new_name) {
            character = tolower(character);
        }

        for (const Invitations &inv : invitations) {
            std::string name_lower = inv.name;
            for (char &character : name_lower) {
                character = tolower(character);
            }
            if (name_lower == new_name) {
                throw std::invalid_argument("can't add invitation with existed name");
            }
        }

        invitations.push_back(invitation);
    }

    int CountNumberOfGuests() {
        int confirmed = 0;
        for (const Invitations &inv : invitations) {
            if (inv.is_attending) {
                confirmed += inv.num_of_people;
            }
        }
        return confirmed;
    }
};

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
