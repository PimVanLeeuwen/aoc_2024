#include "Day19.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

long can_design(const string& towel, const vector<string>& towels) {
    // Dynamic programming vector that is 1 longer than the towel (since you can always make an empty one)
    vector<long> dp(towel.length() + 1, 0); dp[0] = 1;

    // In this we will keep track with the thought "if I can make this smaller towel in x ways and can go from there
    // to a larger towel in y ways, then I can make the larger in x*y ways".
    for (int i = 1; i <= towel.length(); ++i) {
        for (const string& t : towels) {
            if (i >= t.length() && towel.substr(i - t.length(), t.length()) == t) dp[i] += dp[i - t.length()];
        }
    }

    // return the amount of ways that we can make the full towel
    return dp[towel.length()];
}

void Day19::execute(const vector<string> &lines) {

    // keep track of solutions part 1 and part 2
    long part_1 = 0, part_2 = 0;

    // basis for converting lines
    vector<string> towels; stringstream ss(lines[0]); string token;

    // convert the first line to the possible towels
    while (getline(ss, token, ',')) token.erase(remove(token.begin(), token.end(), ' '),
        token.end()); towels.push_back(token);

    // convert the other lines to a vector
    vector designs(lines.begin()+2, lines.end());

    // for each towel check the number of ways to make them
    // for part 1, just count if possible, for part 2, also keep track of the amount of ways
    for (const string& t : designs) {
        if (const long number_of_compositions = can_design(t, designs); number_of_compositions > 0) part_1++;
        part_2 += can_design(t, towels);
    }

    // print the results
    cout << "Part 1: " << part_1 << endl << "Part 2: " << part_2 << endl;
}