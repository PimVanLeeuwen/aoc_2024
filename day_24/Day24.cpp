#include "Day24.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <sstream>

using namespace std;

struct Problem {
    int x;
    int y;
};

long do_wires(map<string, bool> wires, set<pair<pair<string, string>, pair<string, string>>> mapping) {
    long output = 0;

    while (mapping.size() > 1) {
        set<pair<pair<string, string>, pair<string, string>>> new_mapping;
        for (auto &m : mapping) {
            if (wires.find(m.first.first) != wires.end() && wires.find(m.first.second) != wires.end()) {
                if (m.second.first == "XOR") wires[m.second.second] = wires[m.first.first] ^ wires[m.first.second];
                if (m.second.first == "OR") wires[m.second.second] = wires[m.first.first] || wires[m.first.second];
                if (m.second.first == "AND") wires[m.second.second] = wires[m.first.first] && wires[m.first.second];
            } else {
                new_mapping.insert(m);
            }
        }

        mapping = new_mapping;
    }

    string part_1_bit;
    for (const auto&[wire, val] : wires) {
        if (wire[0] == 'z' && val) part_1_bit += '1';
        else if (wire[0] == 'z') part_1_bit += '0';
    }

    reverse(part_1_bit.begin(), part_1_bit.end());

    for (const char c : part_1_bit) output = (output << 1) | (c - '0');

    return output;
}

string to_binary(long n) {
    string r;
    while(n!=0) {
        r = (n%2==0 ?"0":"1")+r;
        n/=2;
    }
    return r;
}

map<string, bool> gen_wires() {
    map<string, bool> wires;

    for (int i = 0; i < 45; i++) {
        int x = rand() % 2;
        int y = rand() % 2;
        if (i < 10) {
            wires["x0" + to_string(i)] = x;
            wires["y0" + to_string(i)] = y;
        } else {
            wires["x" + to_string(i)] = x;
            wires["y" + to_string(i)] = y;
        }
    }

    return wires;
}

set<string> test_output(const map<string, bool>& wires, const long z) {
    string x_str, y_str;
    long x = 0, y = 0;

    for (const auto &[wire, val] : wires) {
        if (wire[0] == 'x' && val) x_str += '1';
        if (wire[0] == 'x' && !val) x_str += '0';
        if (wire[0] == 'y' && val) y_str += '1';
        if (wire[0] == 'y' && !val) y_str += '0';
    }

    reverse(x_str.begin(), x_str.end());
    reverse(y_str.begin(), y_str.end());

    for (const char c : x_str) x = (x << 1) | (c - '0');
    for (const char c : y_str) y = (y << 1) | (c - '0');

    string z_expected = to_binary(z);
    reverse(z_expected.begin(), z_expected.end());

    string z_actual = to_binary(x+y);
    reverse(z_actual.begin(), z_actual.end());

    cout << z_expected << endl;
    cout << z_actual << endl;

    set<string> output;

    for (int i = 0; i < z_expected.size(); i++) {
        if (z_expected[i] != z_actual[i]) output.insert("z" + to_string(i));
    }

    return output;
}

void Day24::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;

    map<string, bool> wires;
    set<pair<pair<string, string>, pair<string, string>>> mapping;
    bool input_part_1 = true;

    for (const auto &line: lines) {
        if (line.empty()) {
            input_part_1 = false;
        } else if (input_part_1) {
            wires[line.substr(0, 3)] = line[5] - '0';
        } else {
            // convert into a string stream to split on token
            stringstream ss(line);
            string token;

            // put the points in here
            vector<string> parts;

            // separate line
            while (getline(ss, token, ' ')) parts.push_back(token);

            mapping.insert({{parts[0], parts[2]}, {parts[1], parts[4]}});
        }
    }

    part_1 = do_wires(wires, mapping);

    set<string> faulty = test_output(wires, part_1);

    for (int i = 0; i < 1000; i++) {
        map<string, bool> test_wires_1 = gen_wires();
        long part_2_test_1 = do_wires(test_wires_1, mapping);
        set<string> faulty_new = test_output(test_wires_1, part_2_test_1);
        for (string s : faulty_new) faulty.insert(s);
    }

    for (string s : faulty) cout << s << endl;




    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}