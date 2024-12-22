#include "Day22.h"

#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

struct Buyer {
    vector<long> price_history;
    vector<int> actual_price_history;
    map<tuple<int, int, int, int>, int> price_map;
};

void price_change(Buyer &b) {
    long new_price = b.price_history[b.price_history.size()-1];
    new_price = ((new_price * 64) ^ new_price) % 16777216;
    new_price = ((new_price / 32) ^ new_price) % 16777216;
    new_price = ((new_price * 2048) ^ new_price) % 16777216;

    b.price_history.push_back(new_price);

    const string actual_price = to_string(new_price);
    const int actual_price_int = actual_price[actual_price.size()-1] - '0';
    b.actual_price_history.push_back(actual_price_int);

    if (b.actual_price_history.size() > 4) {
        const tuple<int, int, int, int> change = make_tuple(
            b.actual_price_history[b.actual_price_history.size()-5] - b.actual_price_history[b.actual_price_history.size()-4],
            b.actual_price_history[b.actual_price_history.size()-4] - b.actual_price_history[b.actual_price_history.size()-3],
            b.actual_price_history[b.actual_price_history.size()-3] - b.actual_price_history[b.actual_price_history.size()-2],
            b.actual_price_history[b.actual_price_history.size()-2] - b.actual_price_history[b.actual_price_history.size()-1]
            );
        if (b.price_map.find(change) == b.price_map.end()) b.price_map[change] = actual_price_int;
    }
}

void Day22::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;

    // PART 1

    vector<Buyer> buyers; buyers.reserve(lines.size());
    for (const auto &line: lines) buyers.push_back(Buyer{{stoi(line)}, {line[line.size()-1] - '0'}});

    for (int i = 0; i < 2000; i++) for (Buyer &b : buyers) price_change(b);

    for (const auto &[price_history, actual_price_history, price_map]: buyers) part_1 += price_history[price_history.size()-1];

    cout << "Part 1: " << part_1 << endl;

    // PART 2

    set<tuple<int, int, int, int>> price_map_options;

    // gather all tuple options
    for (const auto &[price_history, actual_price_history, price_map]: buyers) {
        for (const auto&[history, price] : price_map) {
            price_map_options.insert(history);
        }
    }

    // check which one gives most bananas
    for (const auto& option : price_map_options) {
        long banana = 0;
        for (const auto &[price_history, actual_price_history, price_map]: buyers) {
            if (price_map.find(option) != price_map.end()) {
                banana += price_map.at(option);
            }
        }
        part_2 = max(part_2, banana);
    }

    cout << "Part 2: " << part_2 << endl;
}