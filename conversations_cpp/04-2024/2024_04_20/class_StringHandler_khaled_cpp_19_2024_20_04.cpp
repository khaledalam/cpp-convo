/***
 * Prompt:




 khaled_cpp_19_2024_20_04: 6a02980a-9bb8-458d-a243-ce77cbc1891f


 class_StringHandler_khaled_cpp_19_2024_20_04





 Create a C++ class named StringHandler, this class will include a method named Searcher. This method will accept 2 inputs of type Node called root and std::string called str. Node is like a tree of characters, it's a struct type that contains variable called character of type char and list of pointers of type std::vector<Node*> called next, character hold alphabetic  character and list of pointer pointing to nullptr or another Node struct. This method should return boolean true if we can find the str characters in the root list otherwise return false. Please don't forget to validate the characters, and consider that the characters are case sensitive and if some Node equals nullptr that means this Node is the last Node of the list.


 */

#include <stdexcept>
#include <string>
#include <vector>

struct Node {
    char character;
    std::vector<Node*> next;
};

class StringHandler {
public:
    bool Searcher(Node *root, std::string str) {
        if (!isalpha(root->character)) {
            throw std::invalid_argument("invalid character");
        }

        if (root->character == str[0]) {
            str = str.erase(0, 1);
        }

        for (Node *node : root->next) {
            return (str.length() < 1) || this->Searcher(node, str);
        }

        return false;
    }
};

#include <cassert>
int main() {
    StringHandler string_handler;

    // TEST
    Node *input1 = new Node { character: 'a', next: { new Node { character: 'b', next: { new Node { character: 'c', next: { nullptr } } } } } };
    std::string input2 = "abc";
    bool output = true;
    assert(string_handler.Searcher(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = nullptr;
    input1 = new Node { character: 'a', next: { new Node { character: 'b', next: { nullptr } } } };
    input2 = "ac";
    output = false;
    assert(string_handler.Searcher(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = new Node { character: 'a', next: { new Node { character: 'b', next: { nullptr } }, new Node { character: 'c', next: { nullptr } } } };
    input2 = "ac";
    output = true;
    assert(string_handler.Searcher(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = nullptr;
    input1 = new Node { character: 'a', next: { nullptr } };
    input2 = "a";
    output = true;
    assert(string_handler.Searcher(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = nullptr;
    input2 = "a";
    output = false;
    assert(string_handler.Searcher(input1, input2) == output);
    // TEST_END

    // TEST
    input1 = nullptr;
    input2 = "";
    try {
        string_handler.Searcher(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    input1 = nullptr;
    input2 = "5";
    try {
        string_handler.Searcher(input1, input2);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
