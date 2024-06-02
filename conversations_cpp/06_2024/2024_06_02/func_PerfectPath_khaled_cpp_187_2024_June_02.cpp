/***






 khaled_cpp_187_2024_June_02: de4b19f1-f4d6-40be-8264-748694525dd9

 func_PerfectPath_khaled_cpp_187_2024_June_02


Design a C++ function called PerfectPath that takes two inputs: a graph represented as an adjacency list of type
std::vector<std::vector<std::pair<int, int>>> and a starting node of type int. This function should return a vector of
integers representing the shortest distance from the starting node to each node in the graph using Dijkstra's algorithm.
Please don't forget to validate the input.


*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<int> PerfectPath(const std::vector<std::vector<std::pair<int, int>>> &graph, int start) {
    if (graph.empty()) {
        throw std::invalid_argument("graph cannot be empty");
    }
    if (start < 0 || start >= graph.size()) {
        throw std::invalid_argument("start node is out of bounds");
    }

    const int inf = 1e9;
    std::vector<int> dist(graph.size(), inf);
    dist[start] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pqq;
    pqq.push({0, start});

    while (!pqq.empty()) {
        int uuu = pqq.top().second;
        int ddd = pqq.top().first;
        pqq.pop();

        if (ddd > dist[uuu])
            continue;

        for (const auto &neighbor : graph[uuu]) {
            int vvv = neighbor.first;
            int weight = neighbor.second;

            if (dist[uuu] + weight < dist[vvv]) {
                dist[vvv] = dist[uuu] + weight;
                pqq.push({dist[vvv], vvv});
            }
        }
    }

    return dist;
}

#include <cassert>
int main() {
    std::vector<std::vector<std::pair<int, int>>> graph = {{{1, 4}, {2, 1}}, {{3, 1}}, {{1, 2}, {3, 5}}, {}};

    // TEST
    assert((PerfectPath(graph, 0) == std::vector<int>{0, 3, 1, 4}));
    // TEST_END

    // TEST
    assert((PerfectPath(graph, 2) == std::vector<int>{(int)1e9, 2, 0, 3}));
    // TEST_END

    // TEST
    try {
        PerfectPath({}, 0);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END

    // TEST
    try {
        PerfectPath(graph, 4);
        assert(false);
    } catch (const std::invalid_argument &e) {
        assert(true);
    }
    // TEST_END
}
