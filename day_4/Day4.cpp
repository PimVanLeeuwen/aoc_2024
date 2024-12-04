#include "Day4.h"

#include <iostream>
#include <sstream>

using namespace std;

int has_xmas(const vector<vector<char>> &map, const int x, const int y) {
    if (map[y][x] != 'X') return 0;

    int result = 0;

    // look into all directions
    if (x < map[y].size() - 3 && map[y][x+1] == 'M' && map[y][x+2] == 'A' && map[y][x+3] == 'S') result++;
    if (y < map.size() - 3 && map[y+1][x] == 'M' && map[y+2][x] == 'A' && map[y+3][x] == 'S') result++;
    if (y > 2 && map[y-1][x] == 'M' && map[y-2][x] == 'A' && map[y-3][x] == 'S') result++;
    if (x > 2 && map[y][x-1] == 'M' && map[y][x-2] == 'A' && map[y][x-3] == 'S') result++;
    if (x > 2 && y > 2 && map[y-1][x-1] == 'M' && map[y-2][x-2] == 'A' && map[y-3][x-3] == 'S') result++;
    if (x < map[y].size() - 3 && y < map.size() - 3 && map[y+1][x+1] == 'M' && map[y+2][x+2] == 'A' && map[y+3][x+3] == 'S') result++;
    if (x > 2 && y < map.size() - 3 && map[y+1][x-1] == 'M' && map[y+2][x-2] == 'A' && map[y+3][x-3] == 'S') result++;
    if (x < map[y].size() - 3 && y > 2 && map[y-1][x+1] == 'M' && map[y-2][x+2] == 'A' && map[y-3][x+3] == 'S') result++;

    return result;
}

int has_mas(const vector<vector<char>> &map, const int x, const int y) {
    if (map[y][x] != 'A') return 0;
    if (x == 0 || y == 0 || x == map.size() - 1 || y == map.size() - 1) return 0;

    int result = 0;

    // look for all possible crosses around this A
    if (map[y-1][x-1] == 'M' && map[y-1][x+1] == 'M' && map[y+1][x-1] == 'S' && map[y+1][x+1] == 'S') result++;
    if (map[y-1][x-1] == 'S' && map[y-1][x+1] == 'M' && map[y+1][x-1] == 'S' && map[y+1][x+1] == 'M') result++;
    if (map[y-1][x-1] == 'S' && map[y-1][x+1] == 'S' && map[y+1][x-1] == 'M' && map[y+1][x+1] == 'M') result++;
    if (map[y-1][x-1] == 'M' && map[y-1][x+1] == 'S' && map[y+1][x-1] == 'M' && map[y+1][x+1] == 'S') result++;

    return result;
}

void Day4::execute(const vector<string> &lines) {

    vector<vector<char>> map;

    long part_1 = 0;
    long part_2 = 0;

    for (const auto &line: lines) {
        // put the points in here
        vector<char> line_map;

        // separate line
        for (const auto &c: line) { line_map.push_back(c); }

        map.push_back(line_map);
    }

    for (int y = 0; y < map.size(); ++y) {
        for (int x = 0; x < map[y].size(); ++x) {
            part_1 += has_xmas(map, x, y);
            part_2 += has_mas(map, x, y);
        }
    }



    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
