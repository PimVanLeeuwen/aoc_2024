#include "Day17.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>

using namespace std;

long combo_operand(const int num, const long A, const long B, const long C) {
    switch (num) {
        case 0:
            return 0;
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
        default:
            throw runtime_error("Should not occur");
    }
}

vector<int> run_program(long long A, long B, long C, const vector<int> &program, const bool part_2) {
    vector<int> output;

    int pointer = 0;

    while (pointer <= program.size() - 1) {
        switch (program[pointer]) {
            case 0:
                A = A / static_cast<long long>(pow(2, combo_operand(program[pointer+1], A, B, C)));
            break;
            case 1:
                B = B ^ program[pointer+1];
            break;
            case 2:
                B = combo_operand(program[pointer+1], A, B, C) % 8;
            break;
            case 3:
                if (A != 0) { pointer = program[pointer+1]; continue; }
            break;
            case 4:
                B = B ^ C;
            break;
            case 5:
                output.push_back(static_cast<int>(combo_operand(program[pointer+1], A, B, C) % 8));
                if (part_2) {for (int i = 0; i < output.size(); i++) if (output[i] != program[i]) return {0};}
            break;
            case 6:
                B = A / static_cast<long>(pow(2, combo_operand(program[pointer+1], A, B, C)));
            break;
            case 7:
                C = A / static_cast<long>(pow(2, combo_operand(program[pointer+1], A, B, C)));
            break;
            default:
                throw runtime_error("invalid operation");
        }

        pointer += 2;
    }

    return output;
}

void Day17::execute(const vector<string> &lines) {

    constexpr long A = 66752888;
    constexpr long B = 0;
    constexpr long C = 0;
    const vector<int> program = {2,4,1,7,7,5,1,7,0,3,4,1,5,5,3,0};

    vector<int> output = run_program(A, B, C, program, false);

    cout << "Part 1: ";
    for (const int i : output) cout << i << ",";
    cout << endl;

    vector<long long> A_new = {56745518629787, 56745518629789, 56745518633883, 56745518633885, 56745518637979, 56745518637981};
    int pointer_new = 0;
    vector<int> output_new = run_program(A_new[0], B, C, program, true);
    vector<int> small_program(program.begin(), program.begin() + 13);

    while (output_new != program) {
        output_new = run_program(A_new[pointer_new], B, C, program, false);
        vector<int> small_output(output_new.begin(), output_new.begin() + 13);
        if (small_output == small_program) cout << A_new[pointer_new] << " - " << output_new.size() << endl;
        if (small_output == small_program && pointer_new == 5) cout << endl;
        if (output_new == program) cout << "BINGO" << A_new[pointer_new] << " - " << output_new.size() << endl;


        pointer_new++;
        if (pointer_new == 6) {
            pointer_new = 0;
            for (long long &a : A_new) {
                a += 4194304;
            }
        }
    }



    cout << "Part 2: " << A_new[pointer_new] << endl;
}
