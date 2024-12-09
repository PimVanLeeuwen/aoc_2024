#include "Day9.h"

#include <algorithm>
#include <deque>
#include <iostream>
#include <sstream>
#include <ostream>
#include <set>
#include <utility>

using namespace std;

bool can_compact(const vector<int>& v) {
    bool saw_free = false;
    for (const auto i : v) {
        if (i == -1) saw_free = true;
        else if (saw_free) return true;
    }
    return false;
}

void Day9::execute(const vector<string> &lines) {
    vector<int> filesystem;

    int id = 0;
    for (int i = 0; i < lines[0].size(); i++) {
        const int size = lines[0][i] - '0';
        if (i % 2 == 0) {
            for (int j = 0; j < size; j++) filesystem.push_back(id);
            id++;
        } else {
            for (int j = 0; j < size; j++) filesystem.push_back(-1);
        }
    }

    vector<int> filesystem_2 = filesystem;

    while (can_compact(filesystem)) {
        int empty = 0;
        while (filesystem[empty] != -1) empty++;

        int occupied = filesystem.size()-1;
        while (filesystem[occupied] == -1) occupied--;

        filesystem[empty] = filesystem[occupied];
        filesystem[occupied] = -1;
    }

    long part_1 = 0;
    for (int i = 0; i < filesystem.size(); i++) { if (filesystem[i] != -1) part_1 += i*filesystem[i]; }
    cout << "Part 1: " << part_1 << endl;

    int max_id = *max_element(filesystem_2.begin(), filesystem_2.end());

    while (max_id > 0) {
        // to move block
        const int i = find(filesystem_2.begin(), filesystem_2.end(), max_id) - filesystem_2.begin();
        int l = 1;
        while (filesystem_2[i+l-1] == max_id) l++;
        l--;

        // find all free blocks
        for (int j = 0; j < i; j++) {
            if (filesystem_2[j] == -1) {
                int l_2 = 1;
                while (j+l_2-1 < filesystem_2.size() && filesystem_2[j+l_2-1] == -1) l_2++;
                l_2--;

                // move block
                if (l_2 >= l) {
                    for (int k = j; k - j < l; k++) filesystem_2[k] = max_id;
                    for (int k = i; k - i < l; k++) filesystem_2[k] = -1;
                    break;
                }
            }
        }
        max_id--;
    }

    long part_2 = 0;
    for (int i = 0; i < filesystem_2.size(); i++) { if (filesystem_2[i] != -1) part_2 += i*filesystem_2[i]; }
    cout << "Part 2: " << part_2 << endl;




}


