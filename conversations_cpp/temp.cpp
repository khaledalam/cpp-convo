class Solution {
public:
    string frequencySort(string s) {

        std::map<char, int> mapper;
        std::vector<pair<char, int>> vec;
        for (const char &ch : s) {
            mapper[ch]++;
        }

        for (const auto &mp : mapper) {
            vec.push_back( { mp.first, mp.second });
        }

        std::sort(vec.begin(), vec.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b) {
            return a.second > b.second;
        });

        std::string result = "";
        for (auto it : vec) {
            result += std::string(it.second, it.first);
        }

        return result;
    }
};

// raaeaedere => eeeeaaarrd

std::regex reg("^(?!.*_).*\.(" + allowed_types + " )$");

std::smatch smatcher;

return std::regex_search(new_file_name.begin(), new_file_name.end(), reg);
