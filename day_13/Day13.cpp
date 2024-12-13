#include "Day13.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include"z3++.h"

using namespace std;

struct Problem {
    int A_x;
    int A_y;
    int B_x;
    int B_y;
    int x;
    int y;
};

void Day13::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;
    int A_x = 0;
    int A_y = 0;
    int B_x = 0;
    int B_y = 0;

    vector<Problem> problems;

    for (const auto &line: lines) {
        if (line.empty()) continue;
        // convert into a string stream to split on token
        stringstream ss(line);
        string token;

        // put the points in here
        vector<string> points;

        // separate line
        while (getline(ss, token, ' ')) { points.push_back(token); }

        if (A_x == 0) {
            A_x = stoi(points[2].substr(2, points[2].length() - 2));
            A_y = stoi(points[3].substr(2, points[2].length() - 2));
        } else if (B_x == 0) {
            B_x = stoi(points[2].substr(2, points[2].length() - 2));
            B_y = stoi(points[3].substr(2, points[2].length() - 2));
        } else {
            Problem p{};
            p.x = stoi(points[1].substr(2, points[2].length() - 2));
            p.y = stoi(points[2].substr(2, points[2].length() - 2));
            p.A_x = A_x; A_x = 0;
            p.A_y = A_y; A_y = 0;
            p.B_x = B_x; B_x = 0;
            p.B_y = B_y; B_y = 0;
            problems.push_back(p);
        }
    }

    for (const auto &[A_x, A_y, B_x, B_y, x, y]: problems) {

        z3::context c;

        z3::expr A_x_e = c.int_const("A_x");
        z3::expr B_x_e = c.int_const("B_x");
        z3::expr A_y_e = c.int_const("A_Y");
        z3::expr B_y_e = c.int_const("B_y");
        z3::expr V_a_e = c.int_const("V_a");
        z3::expr V_b_e = c.int_const("V_b");
        z3::expr score = c.int_const("score");
        z3::expr y_e = c.int_const("y");
        z3::expr x_e = c.int_const("x");

        z3::optimize s(c);

        // assigning variables
        s.add(A_x_e == A_x && B_x_e == B_x);
        s.add(A_y_e == A_y && B_y_e == B_y);
        s.add(y_e == y && x_e == x);

        s.add(A_x_e*V_a_e + B_x_e*V_b_e == x_e);
        s.add(A_y_e*V_a_e + B_y_e*V_b_e == y_e);

        s.add(score == V_a_e * 3 + V_b_e);

        s.minimize(score);

        if (s.check() == z3::sat) {
            const z3::model m = s.get_model();

            part_1 += m.eval(score).get_numeral_int();
        }
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: Switched to Python because Z3 in C++ does not work for longs" << endl;
}
