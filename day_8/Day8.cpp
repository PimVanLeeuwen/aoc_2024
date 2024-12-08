#include "Day8.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <set>
#include <sstream>

using namespace std;

pair<int, int> find_antinode(const pair<int, int> &a, const pair<int, int> &b, const int q) {
    return {a.first + q*(b.first - a.first), a.second + q*(b.second - a.second)};
}

void Day8::execute(const vector<string> &lines) {

    map<char, vector<pair<int, int>>> map_frequencies;

    for (int y = 0; y < lines.size(); ++y) {
        for (int x = 0; x < lines[0].size(); ++x) {
            if (lines[y][x] != '.' && map_frequencies.find(lines[y][x]) == map_frequencies.end()) { map_frequencies[lines[y][x]] = {{x, y}}; }
            else if (lines[y][x] != '.') { map_frequencies[lines[y][x]].emplace_back(x, y); }
        }
    }

    set<pair<int, int>> anti_nodes = {};
    set<pair<int, int>> anti_nodes_2 = {};

    for (const auto &[frequency, locations] : map_frequencies) {
        for (const auto &a : locations) {
            for (const auto &b :locations) {
                if (a == b) continue;
                int q = 1;
                pair<int, int> ant = find_antinode(a, b, q);
                while (ant.first >= 0 && ant.first < lines.size() && ant.second >= 0 && ant.second < lines.size()) {
                    if (q == 2) anti_nodes.insert(ant);
                    anti_nodes_2.insert(ant);
                    ant = find_antinode(a, b, ++q);
                }
            }
        }
    }

    cout << "Part 1: " << anti_nodes.size() << endl;
    cout << "Part 2: " << anti_nodes_2.size() << endl;
}
