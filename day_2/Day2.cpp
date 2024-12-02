#include "Day2.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;


bool is_increasing(const vector<int>& array) {
    for (int i = 1; i < array.size(); i++) {
        if (array[i] <= array[i - 1]) {
            return false;
        }
    }

    return true;
}

bool is_decreasing(const vector<int>& array) {
    for (int i = 1; i < array.size(); i++) {
        if (array[i] >= array[i - 1]) {
            return false;
        }
    }

    return true;
}

bool differ_most_3(const vector<int>& array) {
    for (int i = 1; i < array.size(); i++) {
        if (!(abs(array[i] - array[i - 1]) <= 3 && abs(array[i] - array[i - 1]) >= 1)) {
            return false;
        }
    }

    return true;
}

bool is_safe(const vector<int>& array) {
    return (is_increasing(array) || is_decreasing(array)) && differ_most_3(array);
}

void Day2::execute(const vector<string>& lines) {

    int part_1 = 0;
    int part_2 = 0;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line);
        string token;

        // put the points in here
        vector<int> levels;

        // separate line
        while (getline(ss, token, ' ')) { levels.push_back(stoi(token)); }

        // check if the report is safe
        if (is_safe(levels)) { part_1++; part_2++; continue; }

        // check all the options for removing one element
        for (int i = 0; i < levels.size(); i++) {
            vector<int> new_levels = levels;
            new_levels.erase(new_levels.begin() + i);
            if (is_safe(new_levels)) {
                part_2++; break;
            }
        }
    }


    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
