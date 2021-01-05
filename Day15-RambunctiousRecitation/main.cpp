#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cassert>

using std::ifstream;
using std::vector;
using std::unordered_map;
using std::string;
using std::pair;
using std::getline;
using std::cout;
using std::endl;

const size_t NUMBER_OF_ROUNDS = 30000000;
const size_t INITIAL_BUCKET_COUNT = 1000000;

template<typename K, typename V>
bool contains(const unordered_map<K, V>& map, K key) {
    return map.find(key) != map.end();
}

void make_line() {
    cout << "------------------------------" << endl;
}

// returns the next number to be said
size_t say_number(unordered_map<size_t, pair<size_t, size_t>>& last_said, size_t number, size_t pos) {
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

    unordered_map<size_t, pair<size_t, size_t>> last_said{INITIAL_BUCKET_COUNT};
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
        // number = say_number(last_said, number, pos);
        
        // step 1: get next_number
        pair<size_t, size_t>& p = last_said[number];
        if (p.first == SIZE_MAX) {
            number = 0;
        } else {
            number = p.second - p.first;
        }

        // step 2: update last_said
        auto it = last_said.find(number);
        if (it == last_said.end()) {
            last_said.insert({number, {SIZE_MAX, pos}});
        } else {
            it->second.first = it->second.second;
            it->second.second = pos;
        }
    }

    // write output
    cout << "last number: " << number << endl;
}