#include "Day14.h"

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <set>
#include <sstream>
#include <valarray>

using namespace std;

constexpr int WIDTH = 101;
constexpr int HEIGHT = 103;
constexpr int PART_1_TIME = 100;


struct Guard {
    int x;
    int y;
    int v_x;
    int v_y;
};

void move_guard(Guard &g) {
    // cout << "Start: " << g.x << "-" << g.y << " (" << g.v_x << ", " << g.v_y << ")" << endl;
    g.x = (g.x + g.v_x) % WIDTH; if (g.x < 0) g.x += WIDTH;
    g.y = (g.y + g.v_y) % HEIGHT; if (g.y < 0) g.y += HEIGHT;
    // cout << "End: " << g.x << "-" << g.y << endl;

}

void count_guard(vector<int> &q, const Guard &g) {
    // cout <<WIDTH/2 << endl;
    if (g.x < WIDTH/2 && g.y < HEIGHT/2) q[0]++;
    if (g.x > WIDTH/2 && g.y > HEIGHT/2) q[3]++;
    if (g.x > WIDTH/2 && g.y < HEIGHT/2) q[1]++;
    if (g.x < WIDTH/2 && g.y > HEIGHT/2) q[2]++;
    // cout << g.x << " " << g.y << endl;
}

int distance_to_first(const vector<Guard> &guards) {
    const int ref_x = guards[0].x;
    const int ref_y = guards[0].y;

    int total_distance = 0;

    set<pair<int, int>> pos;
    for (auto &g : guards) {
        total_distance = abs(g.x - ref_x) + abs(g.y - ref_y);
    }

    return total_distance;
}

void display_guards(vector<Guard> &guards) {
    set<pair<int, int>> pos;
    for (auto &g : guards) {
        pos.insert({g.x, g.y});
    }

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++ ) {
            if (pos.find({x,y}) != pos.end()) cout << '#';
            else cout << '.';
        }
        cout << endl;
    }
    cout << endl;
}

void Day14::execute(const vector<string> &lines) {

    vector<Guard> guards;

    for (const auto &line: lines) {
        string number_string = "";
        vector<int> numbers;

        for (const auto &c : line) {
            if (isdigit(c) || c == '-') number_string += c;
            else if (!number_string.empty()) {numbers.push_back(stoi(number_string)); number_string = "";}
        }

        guards.push_back(Guard{numbers[0], numbers[1], numbers[2], stoi(number_string)});
    }

    double min_score = INT32_MAX;
    vector<int> quadrants = {0,0,0,0};
    int score;

    for (int i = 0; i < PART_1_TIME; i++) {
        for (auto &g : guards) {
            move_guard(g);
        }

        quadrants = {0,0,0,0};
        score = 0;
        for (auto &g : guards) {
            count_guard(quadrants, g);
        }
        score = quadrants[0]*quadrants[1]*quadrants[2]*quadrants[3];

        if (score < min_score) {
            display_guards(guards);
            min_score = score;
        }
    }

    quadrants = {0,0,0,0};
    int part_1 = 0;
    for (auto &g : guards) {
        count_guard(quadrants, g);
    }
    part_1 = quadrants[0]*quadrants[1]*quadrants[2]*quadrants[3];

    for (int i = 0; i < 10000; i++) {
        for (auto &g : guards) {
            move_guard(g);
        }

        quadrants = {0,0,0,0};
        score = 0;
        for (auto &g : guards) {
            count_guard(quadrants, g);
        }
        score = quadrants[0]*quadrants[1]*quadrants[2]*quadrants[3];

        if (score < min_score) {
            cout << "Part 2: " << PART_1_TIME + i + 1 << endl;
            display_guards(guards);
            min_score = score;
        }
    }

    cout << "Part 1: " << part_1 << endl;
}
