#include "Day15.h"

#include <deque>
#include <iostream>
#include <limits.h>
#include <map>
#include <ostream>
#include <sstream>
#include <queue>
#include <set>

using namespace std;

map<char, pair<int, int>> move_to_coor = {
    {'>', {1, 0}},
    {'<', {-1, 0}},
    {'v', {0, 1}},
    {'^', {0, -1}},
};


pair<int, int> move(vector<vector<char>> &map, int x_robot, int y_robot, char m) {
    auto [m_x, m_y] = move_to_coor[m];
    const bool vertical = m == 'v' || m == '^';

    int step_size = 1;

    if (!vertical) {
        while (map[y_robot][x_robot + step_size*m_x] != '#' &&
                map[y_robot][x_robot + step_size*m_x] != '.') step_size++;

        if (map[y_robot][x_robot + step_size*m_x] == '#') return {x_robot, y_robot};

        if (map[y_robot][x_robot + step_size*m_x] == '.') {
            while (step_size > 0) {
                map[y_robot][x_robot + step_size*m_x] = map[y_robot][x_robot + (step_size-1)*m_x];
                map[y_robot][x_robot + (step_size-1)*m_x] = '.';
                step_size--;
            }
        }

        return {x_robot + m_x, y_robot + m_y};
    }


    // check vertical
    vector<set<pair<int, int>>> boxes = {{{x_robot, y_robot}}};
    bool wall_found = false;

    while (true) {
        // in this case we are done
        bool local_empty = true;
        for (auto [b_x, b_y] : boxes[step_size-1]) {
            if (map[b_y + m_y][b_x] == '#') wall_found = true;
            if (map[b_y + m_y][b_x] != '.') local_empty = false;
        }
        if (wall_found || local_empty) break;

        // new line of stuff
        set<pair<int, int>> new_boxes;

        for (auto [b_x, b_y] : boxes[step_size-1]) {
            if (map[b_y + m_y][b_x] == '[') {
                new_boxes.insert({b_x, b_y + m_y});
                new_boxes.insert({b_x + 1, b_y + m_y});
            }
            if (map[b_y + m_y][b_x] == 'O') {
                new_boxes.insert({b_x, b_y + m_y});
            }
            if (map[b_y + m_y][b_x] == ']') {
                new_boxes.insert({b_x, b_y + m_y});
                new_boxes.insert({b_x - 1, b_y + m_y});
            }
        }

        boxes.push_back(new_boxes);
        step_size++;
    }

    // cannot move vertically
   if (wall_found) return {x_robot, y_robot};

    // move boxes vertically
    while (step_size > 0) {
        for (pair<int, int> box : boxes[step_size-1]) {
            map[box.second + m_y][box.first] = map[box.second][box.first];
            map[box.second][box.first] = '.';
        }
        step_size--;
    }

    return {x_robot, y_robot + m_y};



}

int count_score(const vector<vector<char>> &map) {
    int score = 0;
    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            if (map[y][x] == 'O' || map[y][x] == '[') score += (y*100 + x);
        }
    }
    return score;
}

void Day15::execute(const vector<string> &lines) {

    vector<vector<char>> map_robots;
    vector<vector<char>> map_robots_2;
    vector<char> moves;
    bool draw_map = true;

    for (const auto &line: lines) {
        if (line.empty()) draw_map = false;
        if (draw_map) {
            vector<char> map_line;
            vector<char> map_line_2;
            for (const char c : line) {
                map_line.push_back(c);
                if (c == '#' || c == '.') { map_line_2.push_back(c); map_line_2.push_back(c);}
                if (c == 'O') { map_line_2.push_back('['); map_line_2.push_back(']');}
                if (c == '@') { map_line_2.push_back(c); map_line_2.push_back('.');}
            }
            map_robots.push_back(map_line);
            map_robots_2.push_back(map_line_2);
        }
        if (!draw_map) for (const char c : line) moves.push_back(c);
    }

    int x_robot = -1, y_robot = -1;

    for (int y = 0; y < map_robots.size(); y++) {
        for (int x = 0; x < map_robots[y].size(); x++) {
            if (map_robots[y][x] == '@') { x_robot = x; y_robot = y; }
        }
    }

    for (const char c : moves) {
        const auto [x_robot_new, y_robot_new] = move(map_robots, x_robot, y_robot, c);
        x_robot = x_robot_new; y_robot = y_robot_new;
    }

    x_robot = -1, y_robot = -1;

    for (int y = 0; y < map_robots_2.size(); y++) {
        for (int x = 0; x < map_robots_2[y].size(); x++) {
            if (map_robots_2[y][x] == '@') { x_robot = x; y_robot = y; }
        }
    }

    for (const char c : moves) {
        const auto [x_robot_new, y_robot_new] = move(map_robots_2, x_robot, y_robot, c);
        x_robot = x_robot_new; y_robot = y_robot_new;
    }

    cout << "Part 1: " << count_score(map_robots) << endl;
    cout << "Part 2: " << count_score(map_robots_2) << endl;
}
