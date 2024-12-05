#include "Day5.h"

#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

void Day5::execute(const vector<string> &lines) {
    bool update = false;
    map<int, vector<int>> order_map;

    long part_1 = 0;
    long part_2 = 0;

    for (const auto &line: lines) {
        if (line.empty()) { update = true; continue; }

        if (!update) {
            int left = stoi(line.substr(0, 2));
            int right = stoi(line.substr(3, 2));

            if (order_map.find(left) == order_map.end()) order_map[left] = {right};
            else order_map[left].push_back(right);
        } else {
            vector<int> update_line;

            // convert into a string stream to split on token
            stringstream ss(line); string token;

            // separate line
            while (getline(ss, token, ',')) { update_line.push_back(stoi(token)); }

            bool correct = true;
            for (int i = 0; i < update_line.size(); i++) {

                for (const auto &should_after: order_map[update_line[i]]) {
                    if (const auto index = std::distance(update_line.begin(),
                        find(update_line.begin(), update_line.end(), should_after)); index < i) {
                        correct = false;
                        const int val = update_line[i];
                        update_line[i] = update_line[index];
                        update_line[index] = val;
                        i = 0;
                    }

                }
            }

            if (correct) part_1 += update_line[(update_line.size()/2)];
            else part_2 += update_line[(update_line.size()/2)];
        }

    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}
