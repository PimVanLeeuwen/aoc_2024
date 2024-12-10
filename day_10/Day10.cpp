#include "Day10.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <map>
#include <ostream>
#include <set>

using namespace std;

pair<int, int> amount_trailheads(vector<vector<int>>& trails, int y, int x) {
    deque<pair<int,int>> q = {{x,y}};
    set<pair<int,int>> visited;

    int trailheads = 0;

    while (!q.empty()) {
        auto [x_n, y_n] = q.front();
        q.pop_front();

        if (trails[y_n][x_n] == 9) { trailheads++; visited.insert({x_n, y_n}); continue; }

        if (x_n - 1 >= 0 && trails[y_n][x_n - 1] == trails[y_n][x_n] + 1) { q.emplace_back(x_n - 1, y_n); }
        if (x_n + 1 < trails[0].size() && trails[y_n][x_n + 1] == trails[y_n][x_n] + 1) { q.emplace_back(x_n + 1, y_n); }
        if (y_n - 1 >= 0 && trails[y_n - 1][x_n] == trails[y_n][x_n] + 1) { q.emplace_back(x_n, y_n - 1); }
        if (y_n + 1 < trails.size() && trails[y_n + 1][x_n] == trails[y_n][x_n] + 1) { q.emplace_back(x_n, y_n + 1); }
    }

    return {visited.size(), trailheads};

}

void Day10::execute(const vector<string> &lines) {

    vector<vector<int>> trail_map;

    int part_1 = 0;
    int part_2 = 0;

    for (const auto &line: lines) {
        // put the points in here
        vector<int> points;
        for (const char c : line) points.push_back(c - '0');
        trail_map.push_back(points);
    }

    for (int y = 0; y < trail_map.size(); y++) {
        for (int x = 0; x < trail_map[y].size(); x++) {
            if (trail_map[y][x] == 0) {
                auto [part_1_trails, part_2_trails] = amount_trailheads(trail_map, y, x);
                part_1 += part_1_trails; part_2 += part_2_trails;
            }
        }
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
