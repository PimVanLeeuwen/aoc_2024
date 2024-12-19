#include "Day19.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

long can_design(const string& towel, const vector<string>& towels) {
    vector<long> dp(towel.length() + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= towel.length(); ++i) {
        for (const string& t : towels) {
            if (i >= t.length() && towel.substr(i - t.length(), t.length()) == t) {
                dp[i] += dp[i - t.length()];
            }
        }
    }
    return dp[towel.length()];
}

void Day19::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;

    vector<string> towels;

    stringstream ss(lines[0]); string token;

    // separate line
    while (getline(ss, token, ',')) {
        token.erase(remove(token.begin(), token.end(), ' '), token.end()); towels.push_back(token);
    }

    vector designs(lines.begin()+2, lines.end());

    for (const string& t : designs) {
        if (can_design(t, towels) > 0) part_1++;
        part_2 += can_design(t, towels);
    }


    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}