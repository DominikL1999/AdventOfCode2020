#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

using std::ifstream;
using std::vector;
using std::string;
using std::pair;
using std::getline;
using std::cout;
using std::endl;

struct Solution {
    long long start;
    long long repeat_every;
};

/* Parsing */
bool parse_id(string s, long long & id) {
    if (s == "x") {
        return false;
    }
    else {
        id = stoll(s);
        return true;
    }
}

vector<pair<long long, long long>> parse_ids_and_offsets(string line, char delim) {
    vector<pair<long long, long long>> ids_and_offsets;

    size_t pos;
    long long dist = 0;
    while ((pos = line.find(delim)) != string::npos) {
        long long id;
        bool parse_success = parse_id(line.substr(0, pos), id);
        if (parse_success) ids_and_offsets.push_back({id, dist});
        line.erase(0, pos + 1);
        dist++;
    }
    long long id;
    if (parse_id(line, id)) ids_and_offsets.push_back({id, dist});

    return ids_and_offsets;
}

/* Solution */

bool is_divisible_by(long long a, long long b) {
    return (a / b) * b == a;
}

long long find_first(long long start, long long repeat_every, long long id, long long offset) {
    long long cur = 0;
    while (!is_divisible_by(start + repeat_every * cur + offset, id)) cur++;

    return start + repeat_every * cur;
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    getline(input, line); // skip first line
    getline(input, line);

    vector<pair<long long, long long>> ids_and_offsets = parse_ids_and_offsets(line, ',');

    // do some calculating

    // init solution
    Solution solution{0, 1};

    for (auto pair : ids_and_offsets) {
        auto id = pair.first;
        auto offset = pair.second;

        long long first_instance = find_first(solution.start, solution.repeat_every, id, offset);
        long long second_instance = find_first(first_instance + solution.repeat_every, solution.repeat_every, id, offset);

        solution.start = first_instance;
        solution.repeat_every = second_instance - first_instance;
    }

    // write output
    cout << "solution: " << solution.start << endl;
}