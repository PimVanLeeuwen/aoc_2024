#include "Day21.h"

#include <iostream>
#include <sstream>
#include <ostream>
#include <deque>
#include <map>
#include <queue>

using namespace std;

long hash_function(const int y, const int x, const int n_y, const int n_x, const int nr_of_robots) {
    long result = y;
    result *= 4;
    result += x;
    result *= 4;
    result += n_y;
    result *= 4;
    result += n_x;
    result *= 30;
    result += nr_of_robots;
    return result;
}

map<long, long> memo;

long cheapest_dir_pad(int y, int x, int des_y, int des_x, int nr_of_robots);

// find the cheapest robot for a string of presses
long cheapest_robot(const std::string& presses, const int nr_of_robots) {
    if (nr_of_robots == 1) return static_cast<long>(presses.length());

    long result = 0;
    const string padConfig = "X^A<v>";

    int y = 0; int x = 2;

    for (int i = 0; i < presses.length(); i++) {
        for (int n_y = 0; n_y < 2; n_y++) {
            for (int n_x = 0; n_x < 3; n_x++) {
                if (padConfig[n_y * 3 + n_x] == presses[i]) {
                    result += cheapest_dir_pad(y, x, n_y, n_x, nr_of_robots);
                    y = n_y; x = n_x;
                }
            }
        }
    }
    return result;
}

long cheapest_dir_pad(const int y, const int x, const int des_y, const int des_x, const int nr_of_robots) {
    const long h = hash_function(y, x, des_y, des_x, nr_of_robots);
    if (const auto it = memo.find(h); it != memo.end()) return it->second;

    long answer = INT64_MAX;

    deque<tuple<int, int, string>> q; q.emplace_back(x, y, "");

    while (!q.empty()) {
        auto [n_x, n_y, history] = q.front(); q.pop_front();
        if (n_y == des_y && n_x == des_x) {
            long rec = cheapest_robot(history + "A", nr_of_robots-1);
            answer = min(answer, rec);
        } else if (!(n_y == 0 && n_x == 0)) {
            if (n_y < des_y) q.emplace_back( n_x,n_y + 1,history + "v" );
            else if (n_y > des_y) q.emplace_back( n_x,n_y - 1, history + "^" );
            if (n_x < des_x) q.emplace_back( n_x + 1,n_y, history + ">" );
            else if (n_x > des_x) q.emplace_back( n_x - 1,n_y, history + "<" );
        }
    }

    memo[h] = answer; return answer;
}

long move(const int y, const int x, const int des_y, const int des_x, const int nr_of_robots) {
    vector<vector<char>> output;
    deque<tuple<int, int, string>> q; q.emplace_back(x, y, "");

    long answer = INT64_MAX;

    while (!q.empty()) {
        auto [n_x, n_y, history] = q.front(); q.pop_front();

        if (n_x == des_x && n_y == des_y) {
            long rec = cheapest_robot(history + "A", nr_of_robots);
            answer = min(answer, rec);
        } else if (!(n_x == 0 && n_y == 3)) {
            if (n_y < des_y) q.emplace_back( n_x,n_y + 1,history + "v");
            else if (n_y > des_y) q.emplace_back( n_x,n_y - 1, history + "^" );
            if (n_x < des_x) q.emplace_back( n_x + 1, n_y, history + ">" );
            else if (n_x > des_x) q.emplace_back( n_x - 1, n_y, history + "<" );
        }
    }

    return answer;
}

void Day21::execute(const vector<string> &lines) {

    long part_1 = 0, part_2 = 0;

    for (const auto &line: lines) {
        // convert to number
        string s; for (const char c : line) s += c;
        stringstream ss(s);
        int code;
        ss >> code;

        long result = 0;
        string padConfig = "789456123X0A";

        int y = 3, x = 2;

        for (const char i : line) {
            for (int n_y = 0; n_y < 4; n_y++) {
                for (int n_x = 0; n_x < 3; n_x++) {
                    if (padConfig[n_y * 3 + n_x] == i) {
                        result += move(y, x, n_y, n_x, 3);
                        y = n_y;
                        x = n_x;
                    }
                }
            }
        }

        part_1 += result * code;

        // part 2
        result = 0;
        y = 3; x = 2;

        for (const char i : line) {
            for (int n_y = 0; n_y < 4; n_y++) {
                for (int n_x = 0; n_x < 3; n_x++) {
                    if (padConfig[n_y * 3 + n_x] == i) {
                        result += move(y, x, n_y, n_x, 26);
                        y = n_y; x = n_x;
                    }
                }
            }
        }

        part_2 += result * code;
    }

    cout << "Part 1: " << part_1 << endl << "Part 2: " << part_2 << endl;
}