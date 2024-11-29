//
// Created by pimvanleeuwen on 11/29/24.
//

#include "Day25.h"
#include <iostream>
#include <sstream>

using namespace std;

void Day25::execute(const vector<string> &lines) {
    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line);
        string token;

        // put the points in here
        vector<string> points;

        // separate line
        while (getline(ss, token, ',')) { points.push_back(token); }
    }

    cout << "TODO IMPLEMENT" << endl;
}
