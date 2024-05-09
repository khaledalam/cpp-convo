/***
 * Prompt:




 khaled_cpp_32_2024_21_04: ef97310a-a428-44fa-906e-b7ff20f1e786



 Create a C++ class named Cacher that represents a caching mechanism with member of std::vector<std::string> called memory and member max_limit of type int that refers to the maximum size of the caching memory. Default value of max_limit is 3. This class will contain 2 methods, first method called Insert that will accept an input of type std::string which represent the value that we want to insert into the caching memory and return nothing of type void, the second method called GetLowest that accept no parameters and return the first shortest length value of type std::string. Please note that when try to insert a new unique value and the memory reached the max limit you need to remove the first lowest length value to add the new value after the last lowest length value that is less the new value. We shouldn't add same value in memory twice, Also consider that values are case sensitive. Note that max_limit can't be zero or negative, you can add more helper methods to the class if you want and don't forget to validate inputs.


 */

#include <stdexcept>
#include <string>
#include <map>
#include <algorithm>
#include <vector>

class Cacher {
private:
    int max_limit = 3;
    std::vector<std::string> memory;
public:
    void SetMaxLimit(int new_limit) {
        if (new_limit < 1) {
            throw std::invalid_argument("Invalid memory size");
        }

        max_limit = new_limit;
    }
    void Insert(std::string value) {

        const std::vector<std::string>::iterator search_pos = std::find(memory.begin(), memory.end(), value);
        if (search_pos != memory.end()) {
            return;
        }

        while ((int)memory.size() >= max_limit) {
            Pop();
        }

        std::vector<std::string>::iterator it = memory.begin();
        bool inserted = false;
        while (it != memory.end()) {
            if ((*it).length() > value.length()) {
                inserted = true;
                memory.insert(it, value);
                break;
            }
            it++;
        }
        if (!inserted) {
            memory.push_back(value);
        }
    }
    void Pop() {
        memory.erase(memory.begin());
    }
    std::string GetLowest() {
        if (!memory.empty()) {
            return *memory.begin();
        }
        return std::string("");
    }
    std::string GetHighest() {
        return memory.back();
    }
    std::vector<std::string> GetMemory() {
        return memory;
    }
    void Clear() {
        memory.clear();
    }
};

#include <cassert>
int main() {
    Cacher cacher;

    // TEST
    cacher.Insert(std::string("ABC"));
    cacher.Insert(std::string("ABCD"));
    cacher.Insert(std::string("ABCDE"));
    cacher.Insert(std::string("ABCDEF"));
    assert(cacher.GetLowest() == std::string("ABCD"));
    assert(cacher.GetHighest() == std::string("ABCDEF"));
    assert((cacher.GetMemory() == std::vector<std::string> { std::string("ABCD"), std::string("ABCDE"), std::string("ABCDEF") }));
    //TEST_END

    // TEST
    cacher.Clear();
    cacher.Insert(std::string("ABC"));
    cacher.Insert(std::string("ABCD"));
    cacher.Insert(std::string("ABCDE"));
    cacher.Insert(std::string("ABCDE"));
    assert(cacher.GetLowest() == std::string("ABC"));
    assert(cacher.GetHighest() == std::string("ABCDE"));
    assert((cacher.GetMemory() == std::vector<std::string> { std::string("ABC"), std::string("ABCD"), std::string("ABCDE") }));
    //TEST_END

    // TEST
    cacher.Clear();
    cacher.Insert(std::string("ABCDEF"));
    assert(cacher.GetLowest() == std::string("ABCDEF"));
    assert(cacher.GetHighest() == std::string("ABCDEF"));
    assert((cacher.GetMemory() == std::vector<std::string> { std::string("ABCDEF") }));
    //TEST_END

    // TEST
    cacher.Clear();
    cacher.Insert(std::string("AB"));
    cacher.Insert(std::string("aB"));
    cacher.Insert(std::string("AB"));
    cacher.Insert(std::string("Ab"));
    cacher.Insert(std::string("ab"));
    assert(cacher.GetLowest() == std::string("aB"));
    assert(cacher.GetHighest() == std::string("ab"));
    assert((cacher.GetMemory() == std::vector<std::string> { std::string("aB"), std::string("Ab"), std::string("ab") }));
    //TEST_END

    // TEST
    cacher.Clear();
    cacher.Insert(std::string("123"));
    cacher.Insert(std::string("1234"));
    cacher.Insert(std::string(""));
    assert(cacher.GetLowest() == std::string(""));
    assert(cacher.GetHighest() == std::string("1234"));
    cacher.Insert(std::string("12"));
    assert(cacher.GetLowest() == std::string("12"));
    assert((cacher.GetMemory() == std::vector<std::string> { std::string("12"), std::string("123"), std::string("1234") }));
    //TEST_END

    // TEST
    cacher.Clear();
    assert(cacher.GetLowest() == std::string());
    assert(cacher.GetHighest() == std::string());
    assert((cacher.GetMemory() == std::vector<std::string> { }));
    //TEST_END

    // TEST
    cacher.Clear();
    assert(cacher.GetLowest() == std::string());
    assert(cacher.GetHighest() == std::string());
    assert((cacher.GetMemory() == std::vector<std::string> { }));
    //TEST_END

    // TEST
    cacher.Clear();
    cacher.SetMaxLimit(1);
    cacher.Insert(std::string("12"));
    cacher.Insert(std::string("123"));

    assert(cacher.GetLowest() == std::string("123"));
    assert(cacher.GetHighest() == std::string("123"));
    assert((cacher.GetMemory() == std::vector<std::string> { std::string("123") }));
    //TEST_END

    // TEST
    try {
        cacher.SetMaxLimit(0);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    //TEST_END

    // TEST
    try {
        cacher.SetMaxLimit(-1);
        assert(false);
    } catch (const std::exception &e) {
        assert(true);
    }
    //TEST_END
}

