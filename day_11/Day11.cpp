#include "Day11.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

using namespace std;

map<long, long> move(const map<long, long> stones) {
    map<long, long> output;

    for (const auto [stone, amount] : stones) {
        if (stone == 0) {
            output[1] += amount;
        } else if (to_string(stone).size() % 2 == 0) {
            output[stoi(to_string(stone).substr(0, to_string(stone).size() / 2))] += amount;
            output[stoi(to_string(stone).substr(to_string(stone).size() / 2, to_string(stone).size() / 2))] += amount;
        } else {
            output[stone*2024] += amount;
        }
    }

    return output;
}

void Day11::execute(const vector<string> &lines) {

    constexpr int MOVES = 25;
    constexpr int MOVES_2 = 50;

    map<long, long> stones;

    stringstream ss(lines[0]);
    string token;

    // separate line
    while (getline(ss, token, ' ')) stones[stoi(token)] = 1;

    for (int i = 0; i < MOVES; i++) stones = move(stones);

    long part_1 = 0;
    for (const auto [stone, amount] : stones) part_1 += amount;
    cout << "Part 1: " << part_1 << endl;

    for (int i = 0; i < MOVES_2; i++) stones = move(stones);
    
    long part_2 = 0;
    for (const auto [stone, amount] : stones) part_2 += amount;
    cout << "Part 2: " << part_2 << endl;
}
