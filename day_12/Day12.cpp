#include "Day12.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

struct Problem {
    int x;
    int y;
};

pair<int, int> fence_cost(vector<vector<char>>& plots, int y, int x) {
    int perimeter = 0;
    int lines = 0;
    const char current_plot = plots[y][x];

    deque<pair<int, int>> q = {{x, y}};
    set<pair<int, int>> plot_points;
    set<pair<int, int>> perimeter_points;

    while (!q.empty()) {
        int x_point = q.front().first;
        int y_point = q.front().second;
        q.pop_front();
        plot_points.insert({x_point, y_point});

        if (y_point > 0 && plots[y_point-1][x_point] == current_plot && plot_points.find({x_point, y_point-1}) == plot_points.end() && find(q.begin(), q.end(), make_pair(x_point, y_point-1)) == q.end()) {q.emplace_back(x_point, y_point-1);}
        if (x_point > 0 && plots[y_point][x_point-1] == current_plot && plot_points.find({x_point-1, y_point}) == plot_points.end() && find(q.begin(), q.end(), make_pair(x_point-1, y_point)) == q.end()) {q.emplace_back(x_point-1, y_point);}
        if (y_point < plots.size() - 1 && plots[y_point+1][x_point] == current_plot && plot_points.find({x_point, y_point+1}) == plot_points.end() && find(q.begin(), q.end(), make_pair(x_point, y_point+1)) == q.end()) {q.emplace_back(x_point, y_point+1);}
        if (x_point < plots[0].size() - 1 && plots[y_point][x_point+1] == current_plot && plot_points.find({x_point+1, y_point})  == plot_points.end() && find(q.begin(), q.end(), make_pair(x_point+1, y_point)) == q.end()) {q.emplace_back(x_point+1, y_point);}
    }

    // add perimeter
    for (const auto [x, y] : plot_points) {
        if (plot_points.find({x-1, y}) == plot_points.end()) {perimeter++; perimeter_points.insert({x-1, y});}
        if (plot_points.find({x+1, y}) == plot_points.end()) {perimeter++; perimeter_points.insert({x+1, y});}
        if (plot_points.find({x, y-1}) == plot_points.end()) {perimeter++; perimeter_points.insert({x, y-1});}
        if (plot_points.find({x, y+1}) == plot_points.end()) {perimeter++; perimeter_points.insert({x, y+1});}
        plots[y][x] = '.';
    }

    // for part 2 find all corners for the lines
    for (const auto [x, y] : plot_points) {
        if (plot_points.find({x-1, y}) == plot_points.end() && plot_points.find({x, y-1}) == plot_points.end()) {lines++;}
        if (plot_points.find({x-1, y}) == plot_points.end() && plot_points.find({x, y+1}) == plot_points.end()) {lines++;}
        if (plot_points.find({x, y-1}) == plot_points.end() && plot_points.find({x+1, y}) == plot_points.end()) {lines++;}
        if (plot_points.find({x, y+1}) == plot_points.end() && plot_points.find({x+1, y}) == plot_points.end()) {lines++;}
        if (plot_points.find({x-1, y}) != plot_points.end() && plot_points.find({x, y-1}) != plot_points.end() && plot_points.find({x-1, y-1}) == plot_points.end() ) {lines++;}
        if (plot_points.find({x-1, y}) != plot_points.end() && plot_points.find({x, y+1}) != plot_points.end() && plot_points.find({x-1, y+1}) == plot_points.end() ) {lines++;}
        if (plot_points.find({x, y-1}) != plot_points.end() && plot_points.find({x+1, y}) != plot_points.end() && plot_points.find({x+1, y-1}) == plot_points.end()) {lines++;}
        if (plot_points.find({x, y+1}) != plot_points.end() && plot_points.find({x+1, y}) != plot_points.end() && plot_points.find({x+1, y+1}) == plot_points.end()) {lines++;}
    }

    return {perimeter*plot_points.size(), lines*plot_points.size()};

}

void Day12::execute(const vector<string> &lines) {

    long part_1 = 0;
    long part_2 = 0;

    vector<vector<char>> plots;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        vector<char> line_plot;
        for (const auto &c: line) {line_plot.push_back(c);}
        plots.push_back(line_plot);
    }

    for (int y = 0; y < plots.size(); ++y) {
        for (int x = 0; x < plots[y].size(); ++x) {
            if (plots[y][x] != '.') {
                auto [p_1, p_2] = fence_cost(plots, y, x);
                part_1 += p_1;
                part_2 += p_2;
            }
        }
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}