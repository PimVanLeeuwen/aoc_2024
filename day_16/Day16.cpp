#include "Day16.h"

#include <climits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <math.h>
#include <numeric>
#include <ostream>
#include <stdexcept>

using namespace std;

void Day16::execute(const vector<string> &lines) {
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