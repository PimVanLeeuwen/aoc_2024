#include "Day16.h"

#include <iostream>
#include <map>
#include <sstream>
#include <math.h>
#include <ostream>
#include <queue>
#include <set>

using namespace std;

struct Point {
    int x;
    int y;
    pair<int, int> dir;
    int score;
    vector<pair<int, int>> history;
};

struct ComparePoints {
    bool operator()(const Point& p1, const Point& p2) const {
        return p1.score > p2.score; // Min-heap: lowest score at the top
    }
};

vector<pair<int, int>> dirs = {
    {1,0},
    {-1,0},
    {0,1},
    {0,-1},
};

void Day16::execute(const vector<string> &lines) {
    vector<vector<char>> maze;
    const Point start = {1, static_cast<int>(lines.size() - 2), {1,0}, 0, {}};

    long part_1 = INT32_MAX;
    for (const auto &line: lines) {
        vector<char> maze_line;
        for (char c : line) maze_line.push_back(c);
        maze.push_back(maze_line);
    }

    priority_queue<Point, vector<Point>, ComparePoints> pq; pq.push(start);
    map<pair<pair<int,int>, pair<int, int>>, int> visited;
    set<pair<int, int>> best_nodes;

    while (!pq.empty()) {
        // pop lowest score
        auto [x, y, dir, score, history] = pq.top(); pq.pop();

        // if already worse than best path we stop (for part 2)
        if (score > part_1) break;

        // keep track of best score per point-dir combination, no going to worse
        visited[{{x, y}, dir}] = score;
        // keep history
        history.emplace_back(x, y);

        if (maze[y][x] == 'E') {
            part_1 = score;
            for (const auto p : history) best_nodes.insert(p);
            continue;
        }

        for (auto [d_x, d_y] : dirs) {
            int rotation_points = 0;
            if (d_x != dir.first && d_y != dir.second) rotation_points += 1000;
            else if ((d_x == dir.first && d_y != dir.second) || (d_x != dir.first && d_y == dir.second)) continue;

            if ((maze[y + d_y][x + d_x] == '.' || maze[y + d_y][x + d_x] == 'E')
                && (visited.find({{x + d_x, y + d_y}, {d_x, d_y}}) == visited.end() ||
                    score + 1 + rotation_points < visited[{{x + d_x, y + d_y}, {d_x, d_y}}])) {
                pq.push(Point{x + d_x, y + d_y, {d_x, d_y}, score + 1 + rotation_points, history});
            }
        }
    }


    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << best_nodes.size() << endl;
}