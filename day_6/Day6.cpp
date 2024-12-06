#include "Day6.h"

#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void Day6::execute(const vector<string> &lines) {

    map<char, pair<int, int>> map_diff = {
        {'^', {0, -1}},
        {'>', {1, 0}},
        {'<', {-1, 0}},
        {'v', {0, 1}},
    };

    map<char, char> map_turn = {
        {'^', '>'},
        {'>', 'v'},
        {'<', '^'},
        {'v', '<'},
    };

    vector<vector<char>> map_guard;
    set<pair<int, int>> visited;

    for (const auto &line: lines) {
        // put the points in here
        vector<char> line_guard;

        for (const auto &c: line) {line_guard.push_back(c);}

        map_guard.push_back(line_guard);
    }

    int guard_x = 36; int guard_y = 52;
    vector<vector<char>> map_now = map_guard;

    while (true) {
        // keep track of unique visited locations
        visited.insert({guard_x, guard_y});

        // move
        const int x_diff = map_diff[map_now[guard_y][guard_x]].first;
        const int y_diff = map_diff[map_now[guard_y][guard_x]].second;

        // out of the map
        if (!(guard_x + x_diff >= 0 && guard_y + y_diff >= 0 && guard_x + x_diff < map_now[0].size() &&
            guard_y + y_diff < map_now.size())) break;

        // turn
        if (map_now[guard_y + y_diff][guard_x + x_diff] == '#') {
            map_now[guard_y][guard_x] = map_turn[map_now[guard_y][guard_x]];
        } else {
            map_now[guard_y + y_diff][guard_x + x_diff] = map_now[guard_y][guard_x];
            map_now[guard_y][guard_x] = '.';
            guard_x += x_diff;
            guard_y += y_diff;
        }
    }

    cout << "Part 1: " << visited.size() << endl;

    // PART 2

    int part_2 = 0;
    
    for (const auto [obstacle_x, obstacle_y] : visited) {
        guard_x = 36; guard_y = 52;
        if (obstacle_y == guard_y && obstacle_x == guard_x) continue;

        // copy map
        map_now = map_guard;

        // keep path for loops
        set<pair<char, pair<int, int>>> path_guard;

        while (true) {
            // if you have a loop break
            if (path_guard.find(make_pair<char, pair<int,int>>(move(map_now[guard_y][guard_x]),
                make_pair<int, int>(move(guard_x), move(guard_y)))) != path_guard.end()) {
                part_2++; break;
            }

            // keep track of path
            path_guard.insert({map_now[guard_y][guard_x], {guard_x, guard_y}});

            // move
            const int x_diff = map_diff[map_now[guard_y][guard_x]].first;
            const int y_diff = map_diff[map_now[guard_y][guard_x]].second;

            // out of the map
            if (!(guard_x + x_diff >= 0 && guard_y + y_diff >= 0 && guard_x + x_diff < map_now[0].size() &&
                guard_y + y_diff < map_now.size())) break;

            // turn
            if (map_now[guard_y + y_diff][guard_x + x_diff] == '#' || (guard_y + y_diff == obstacle_y && guard_x + x_diff == obstacle_x)) {
                map_now[guard_y][guard_x] = map_turn[map_now[guard_y][guard_x]];
            } else {
                map_now[guard_y + y_diff][guard_x + x_diff] = map_now[guard_y][guard_x];
                map_now[guard_y][guard_x] = '.';
                guard_x += x_diff;
                guard_y += y_diff;
            }
        }
    }





    cout << "Part 2: " << part_2 << endl;
}
