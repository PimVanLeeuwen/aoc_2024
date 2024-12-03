#include "Day3.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <sstream>
#include <iostream>
using namespace std;

void Day3::execute(const vector<string>& lines) {

    long part_1 = 0;
    bool do_part_2 = true;
    long part_2 = 0;

    for (const auto &line: lines) {
        // convert into a string stream to split on token
        for (int i = 0; i < line.size(); i++) {
            // first part valid
            if (line.substr(i, 4) == "mul(") {
                // int numbers
                int counter = i+4; int a = 0; int b = 0;
                // string reps
                string a_string, b_string;
                // check if format matches
                while (counter < line.size()) {
                    if (isdigit(line[counter]) && a == 0) {
                        a_string += line[counter++];
                    } else if (isdigit(line[counter])) {
                        b_string += line[counter++];
                    } else if (line[counter] == ',') {
                        a = stoi(a_string);
                        counter++;
                    } else if (line[counter] == ')') {
                        b = stoi(b_string);
                        part_1 += (a * b);
                        // if part 2 do that as well
                        if (do_part_2) part_2 += (a * b);
                        break;
                    } else { break; }
                }
            } else if (line.substr(i, 4) == "do()") {
                do_part_2 = true; // match do()
            } else if (line.substr(i, 7) == "don't()") {
                do_part_2 = false; // match dont
            }
        }
    }

    cout << "Part 1: " << part_1 << endl;
    cout << "Part 2: " << part_2 << endl;
}