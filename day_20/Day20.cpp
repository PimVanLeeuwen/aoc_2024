#include "Day20.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>

using namespace std;

struct WalkPoint {
    int x;
    int y;
    int distance;
    vector<pair<int, int>> history;
};

struct ComparePoints {
    bool operator()(const WalkPoint& p1, const WalkPoint& p2) const {
        return p1.distance > p2.distance; // Min-heap: lowest score at the top
    }
};

vector<pair<int, int>> neighbours_20 = {
    {1,0},
    {-1,0},
    {0,1},
    {0,-1},
};

void Day20::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;
    vector<vector<char>> problem_set;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line);
        string token;
        // put the points in here
        vector<char> problem_line;
        for (char c : line) problem_line.push_back(c);
        problem_set.push_back(problem_line);
    }

    // find the starting point
    int x_start = -1, y_start = -1;

    for (int y = 0; y < problem_set.size(); y++) {
        for (int x = 0; x < problem_set[0].size(); x++) {
            if (problem_set[y][x] == 'S') {x_start = x; y_start = y; break;}
        }
        if (x_start >= 0) break;
    }

    // set the starting point object
    if (x_start == -1) throw runtime_error("No start found");
    const WalkPoint start = {x_start,y_start, 0, {}};

    // create prio queue
    priority_queue<WalkPoint, vector<WalkPoint>, ComparePoints> pq; pq.push(start);

    // keep track of what we have seen
    set<pair<int,int>> visited_set;
    vector<pair<int, int>> path;

    // bfs to find quickest non-cheat solution and store path
    while (!pq.empty()) {
        auto [x, y, distance, history] = pq.top(); pq.pop();
        history.emplace_back(x, y);
        visited_set.insert({x,y});

        if (problem_set[y][x] == 'E') {path = history; break; }

        for (auto [d_x, d_y] : neighbours_20) {
            if (x + d_x >= 0 && x + d_x < problem_set[0].size() && y + d_y >= 0 && y + d_y < problem_set.size() &&
                visited_set.find({x + d_x, y + d_y}) == visited_set.end()) {
                if (problem_set[y + d_y][x + d_x] == '.' || problem_set[y + d_y][x + d_x] == 'E') {
                    pq.push(WalkPoint{x + d_x, y + d_y, distance + 1, history});
                }
            }
        }
    }

    // For every point in the path we check if we can take a shortcut that saves 100 (or more) steps
    for (int i = 0; i < path.size(); i++) {
        for (int j = i + 101; j < path.size(); j++) {
            const int dist = abs(path[i].first - path[j].first) + abs(path[i].second - path[j].second);
            if (dist <= 2 && (j-i-dist) >= 100) part_1++;
            if (dist <= 20 && (j-i-dist) >= 100) part_2++; // make sure the cheat is one step
        }
    }


    cout << "Part 1: " << part_1 << endl << "Part 2: " << part_2 << endl;
}

