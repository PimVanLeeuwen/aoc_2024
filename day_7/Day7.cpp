#include "Day7.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <limits.h>
#include <sstream>

using namespace std;

bool can_make(const long test_value, deque<long> input) {
    if (input.size() == 1) { return input[0] == test_value; }

    const long num = input.front(); input.pop_front();
    deque<long> deque_mul = input; deque_mul[0] *= num;
    deque<long> deque_add = input; deque_add[0] += num;

    return can_make(test_value, deque_mul) || can_make(test_value, deque_add);
}

bool can_make_2(const long test_value, deque<long> input) {
    if (input.size() == 1) { return input[0] == test_value; }

    const long num = input.front(); input.pop_front();
    deque<long> deque_mul = input; deque_mul[0] *= num;
    deque<long> deque_add = input; deque_add[0] += num;
    deque<long> deque_concat = input; string num_string = to_string(num); num_string += to_string(deque_concat[0]); deque_concat[0] = stol(num_string);

    return can_make_2(test_value, deque_mul) || can_make_2(test_value, deque_add) || can_make_2(test_value, deque_concat);
}

void Day7::execute(const vector<string> &lines) {

    long part_1 = 0;
    long part_2 = 0;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line);
        string token;

        // put the points in here
        deque<long> input;
        long test_value = -1;

        // separate line
        while (getline(ss, token, ' ')) {
            if (test_value == -1) { test_value = stol(token); }
            else input.push_back(stol(token));
        }

        if (can_make(test_value, input)) { part_1 += test_value; }
        if (can_make_2(test_value, input)) { part_2 += test_value; }
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
