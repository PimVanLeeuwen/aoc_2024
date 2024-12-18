#include "Day18.h"

#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <memory>
#include <queue>
#include <set>

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

vector<pair<int, int>> neighbours = {
    {1,0},
    {-1,0},
    {0,1},
    {0,-1},
};


constexpr int SIZE = 70;
// constexpr int SIZE = 6;

int solve_map(set<pair<int, int>> c) {
    const WalkPoint start = {0,0, 0, {}};

    priority_queue<WalkPoint, vector<WalkPoint>, ComparePoints> pq; pq.push(start);
    map<pair<int,int>, int> visited;
    set<pair<int,int>> visited_set;

    while (!pq.empty()) {
        auto [x, y, distance, history] = pq.top(); pq.pop();
        history.emplace_back(x, y);
        visited_set.insert({x,y});

        if (x == SIZE && y == SIZE) return distance;

        for (auto [d_x, d_y] : neighbours) {
            if (c.find({x + d_x, y + d_y}) == c.end() &&
                x + d_x >= 0 && x + d_x <= SIZE && y + d_y >= 0 && y + d_y <= SIZE &&
                (visited_set.find({x + d_x, y + d_y}) == visited_set.end())) {
                pq.push(WalkPoint{x + d_x, y + d_y, distance + 1, history});
                visited_set.insert({x + d_x, y + d_y});
            }
        }

    }
    return -1;
}

void Day18::execute(const vector<string> &lines) {

    vector<pair<int, int>> corrupted;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line);
        string token;

        // put the points in here
        vector<int> map_line;

        // separate line
        while (getline(ss, token, ',')) { map_line.push_back(stoi(token)); }

        corrupted.emplace_back(map_line[0], map_line[1]);
    }

    set<pair<int, int>> corrupted_set;

    for (int i = 0; i < 1024; i++) corrupted_set.insert(corrupted[i]);

    cout << "Part 1: " << solve_map(corrupted_set) << endl;

    for (int i = 1024; i < 2500; i++) corrupted_set.insert(corrupted[i]);
    int index = 2500;

    while (solve_map(corrupted_set) > 0) corrupted_set.insert(corrupted[index++]);

    cout << "Part 2: " << corrupted[index-1].first << "," << corrupted[index-1].second << endl;
}