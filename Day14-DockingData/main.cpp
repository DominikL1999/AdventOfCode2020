#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <map>

using std::ifstream;
using std::vector;
using std::map;
using std::string;
using std::bitset;
using std::pair;
using std::getline;
using std::cout;
using std::endl;

string parse_mask(string line) {
    return line.substr(7, 36);
}

pair<unsigned long long, unsigned long long> parse_assignment(string line) {
    size_t pos = line.find(']');
    unsigned long long mem_pos = stoull(line.substr(4, pos - 4));

    pos = line.find('=');
    unsigned long long value = stoull(line.substr(pos + 1));
    
    return {mem_pos, value};
}

bool is_mask(string line) {
    return line.substr(0, 6) == "mask =";
}

unsigned long long modify_value(unsigned long long value, string mask) {
    bitset<36>bits(value);

    for (size_t i = 0; i < 36; i++) {
        if (mask[i] == '1') bits.set(35 - i, true);
        else if (mask[i] == '0') bits.set(35 - i, false);
        else continue;
    }

    return bits.to_ullong();
}

void update_memory(map<unsigned long long, unsigned long long>& mem, string mask, pair<unsigned long long, unsigned long long> assignment) {
    mem[assignment.first] = modify_value(assignment.second, mask);
}

int main() {
    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");

    string line;
    // get mask
    string mask;
    getline(input, line);
    mask = parse_mask(line);

    map<unsigned long long, unsigned long long> mem;

    while (getline(input, line)) {
        if (is_mask(line)) {
            mask = parse_mask(line);
        }
        else {
            auto assignment = parse_assignment(line);
            update_memory(mem, mask, assignment);
        }
    }

    // write output
    unsigned long long sum = 0;
    for (auto pair : mem) {
        sum += pair.second;
    }
    cout << "sum: " << sum << endl;
}