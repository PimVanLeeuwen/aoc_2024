#include "Day14.h"

#include <algorithm>
#include <iostream>
#include <limits.h>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void Day14::execute(const vector<string> &lines) {
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
