#include "Day2.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <vector>
using namespace std;

void Day2::execute(const vector<string>& lines) {
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
