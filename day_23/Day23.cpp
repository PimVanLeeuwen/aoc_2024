#include "Day23.h"

#include <algorithm>
#include <climits>
#include <iostream>
#include <sstream>
#include <map>
#include <ostream>
#include <set>

using namespace std;

struct Problem {
    int x;
    int y;
};

void Day23::execute(const vector<string> &lines) {

    set<pair<string, string>> connections;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        stringstream ss(line);
        string token;

        // put the points in here
        string computer_a = line.substr(0,2);
        string computer_b = line.substr(3,2);

        connections.insert(make_pair(computer_a, computer_b));
    }

    set<string> computers;

    for (const auto& [a, b]: connections) { computers.insert(a); computers.insert(b); }

    set<set<string>> part_1;

    for (const string& comp : computers) {
        if (comp[0] != 't') continue;
        set<string> connected_computers;
        for (const auto& [a, b]: connections) {
            if (a == comp) connected_computers.insert(b);
            if (b == comp) connected_computers.insert(a);
        }

        for (const string& c_1: connected_computers) {
            for (const string& c_2: connected_computers) {
                if (connections.find(make_pair(c_1, c_2)) != connections.end() || connections.find(make_pair(c_2, c_1)) != connections.end()) {
                    part_1.insert({comp, c_1, c_2});
                }
            }
        }
    }

    cout << "Part 1: " << part_1.size() << endl;

    set<string> part_2 = {};

    for (const string& comp: computers) {
        set<string> part_2_set = { comp };
        for (const string& comp_2: computers) {
            bool connects_to_all = true;
            for (const string& set_computer: part_2_set) {
                if (connections.find(make_pair(set_computer, comp_2)) == connections.end() && connections.find(make_pair(comp_2, set_computer)) == connections.end()) {
                    connects_to_all = false; break;
                }
            }
            if (connects_to_all) part_2_set.insert(comp_2);
        }

        if (part_2_set.size() > part_2.size()) part_2 = part_2_set;
    }



    cout << "Part 2: ";
    for (const string& comp: part_2)  cout << comp << ",";

}
