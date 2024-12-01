#include "Day1.h"

#include <algorithm>
#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

void Day1::execute(const vector<string>& lines) {
    vector<int> left;
    vector<int> right;

    // get input
    for (const auto &line: lines) {
        left.push_back(stoi(line.substr(0, 5)));
        right.push_back(stoi(line.substr(7, 6)));
    }

    // sort both vectors
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // do part 1
    long part_1 = 0;
    for (int i = 0; i < left.size(); i++) { part_1 += abs(left[i]-right[i]); }
    cout << "Part 1: " << part_1 << endl;

    // do part 2
    long part_2 = 0;
    for (int i = 0; i < left.size(); i++) {
        int times = 0;
        for (int j = 0; j < right.size(); j++) { if (right[j] == left[i]) times++; }
        part_2 += left[i]*times;
    }
    cout << "Part 2: " << part_2 << endl;
}

