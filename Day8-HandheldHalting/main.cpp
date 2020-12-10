#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <cassert>

using std::ifstream;
using std::vector;
using std::set;
using std::string;
using std::pair;
using std::getline;
using std::cout;
using std::endl;

enum Command {Acc, Jmp, Nop};

pair<Command, int> parse_command(string line) {
    size_t pos = line.find(' ');
    string s1 = line.substr(0, pos);
    string s2 = line.substr(pos + 1);

    Command cmd;
    if (s1 == "acc") cmd = Acc;
    else if (s1 == "jmp") cmd = Jmp;
    else cmd = Nop;

    return {cmd, stoi(s2)};
}

template<typename T>
bool contains(set<T>set, T val) {
    return set.find(val) != set.end();
}

bool try_run(vector<pair<Command, int>>& program, int* acc) {
    *acc = 0;
    int cmd = 0;
    set<int> cmds;

    // do some calculating
    while (cmd < static_cast<int>(program.size())) {
        if (contains(cmds, cmd)) return false;
        cmds.insert(cmd);

        if (program[cmd].first == Acc) {
            *acc = *acc + program[cmd].second;
            cmd++;
        }
        else if (program[cmd].first == Jmp) {
            cmd += program[cmd].second;
        }
        else { // Nop
            cmd++;
        }
    }

    return cmd == static_cast<int>(program.size());
}

void flip_command(Command* cmd) {
    if (*cmd == Jmp) *cmd = Nop;
    else if (*cmd == Nop) *cmd = Jmp;
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    vector<pair<Command, int>> program;
    while (getline(input, line)) {
        pair<Command, int> parsed_command = parse_command(line);
        program.push_back(parsed_command);
    }

    // do some calculating

    int prev_changed = -1;
    int acc;
    for (int cmd = 0; cmd < static_cast<int>(program.size()); cmd++) {
        if (program[cmd].first == Acc) continue;
        else {
            if (prev_changed != -1)
                flip_command(&program[prev_changed].first);

            flip_command(&program[cmd].first);
            prev_changed = cmd;
            
            if (try_run(program, &acc)) break;
        }
    }

    // write output
    cout << "acc: " << acc << endl;
}