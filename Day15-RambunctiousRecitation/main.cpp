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
        pair<size_t, size_t>& p = last_said[number];
        if (p.first == SIZE_MAX) {
            number = 0;
        } else {
            number = p.second - p.first;
        }

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