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

bool is_mask(string line) {
    return line.substr(0, 6) == "mask =";
}

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

vector<bitset<36>> get_bit_variations(bitset<36> bits, vector<size_t> floating_positions) {
    if (floating_positions.empty()) return {bits};

    size_t pos = floating_positions[floating_positions.size() - 1];
    floating_positions.pop_back();

    bits.set(35 - pos, false);
    vector<bitset<36>> set1 = get_bit_variations(bits, floating_positions);
    bits.set(35 - pos, true);
    vector<bitset<36>> set2 = get_bit_variations(bits, floating_positions);

    set1.insert(set1.end(), set2.begin(), set2.end());

    return set1;
}

void update_memory(map<unsigned long long, unsigned long long>& mem, string mask, pair<unsigned long long, unsigned long long> assignment) {
    vector<unsigned long long> addresses;
    bitset<36> bits(assignment.first); // initialize bitset with the 36 least significant bits of address
    vector<size_t> floating_positions; // the positions in the mask, which contain an 'X'

    for (size_t i = 0; i < 36; i++) {
        if (mask[i] == '1') bits.set(35 - i, true);
        else if (mask[i] == 'X') floating_positions.push_back(i);
        else continue;
    }

    auto variations = get_bit_variations(bits, floating_positions);
    for (auto variation : variations)
        mem[variation.to_ullong()] = assignment.second;
}

int main() {
    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");

    string line;
    string mask;
    
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