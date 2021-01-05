#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>

using std::ifstream;
using std::vector;
using std::map;
using std::string;
using std::pair;
using std::getline;
using std::cout;
using std::endl;

const size_t NUMBER_OF_ROUNDS = 1000000;

template<typename K, typename V>
bool contains(const map<K, V>& map, K key) {
    return map.find(key) != map.end();
}

void make_line() {
    cout << "------------------------------" << endl;
}

// returns the next number to be said
size_t say_number(map<size_t, pair<size_t, size_t>>& last_said, size_t number, size_t pos) {

    // step 1: get next_number

    size_t next_number;
    pair<size_t, size_t>& p = last_said[number];
    if (p.first == SIZE_MAX) {
        next_number = 0;
    } else {
        next_number = p.second - p.first;
    }

    // step 2: update last_said
    auto it = last_said.find(next_number);
    if (it == last_said.end()) {
        last_said.insert({next_number, {SIZE_MAX, pos}});
    } else {
        it->second.first = it->second.second;
        it->second.second = pos;
    }

    // step 3: return next_number
    return next_number;
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");

    map<size_t, pair<size_t, size_t>> last_said;
    size_t pos = 0;
    size_t number;
    while (input.good()) {
        string substr;
        getline(input, substr, ',');
        number = stoi(substr);

        last_said[number] = {SIZE_MAX, pos};
        pos++;
    }
    
    // do some calculating
    for (; pos < NUMBER_OF_ROUNDS; pos++) {
        number = say_number(last_said, number, pos);
    }

    // write output
    cout << "last number: " << number << endl;
}