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

/* Parsing */

long long parse_id(string s) {
    if (s == "x") return -1;
    else return stoll(s);
}

vector<long long> parse_bus_ids(string line, char delim) {
    vector<long long> bus_ids;

    size_t pos;
    while ((pos = line.find(delim)) != string::npos) {
        bus_ids.push_back(parse_id(line.substr(0, pos)));
        line.erase(0, pos + 1);
    }
    bus_ids.push_back(parse_id(line));

    return bus_ids;
}

/* Solution (327300950120029) */

bool is_divisible_by(long long a, long long b) {
    return (a / b) * b == a;
}

bool check_solution(pair<long long, long long>& solution, vector<long long>& bus_ids, size_t up_to) {
    // assert(solution.first < solution.second);
    for (size_t i = 0; i <= up_to; i++) {
        if (!is_divisible_by(solution.first +  i, bus_ids[i])) {
            cout << "ERROR:" << endl;
            cout << "solution.first: " << solution.first << endl;
            cout << "i: " << i << endl;
            cout << "id: " << bus_ids[i] << endl;
            return false;
        }
    }

    return true;
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    getline(input, line); // skip first line
    getline(input, line);

    vector<long long> bus_ids = parse_bus_ids(line, ',');

    // do some calculating

    pair<long long, long long> solution{0, bus_ids[0]};

    for (long long i = 1; i < (long long)bus_ids.size(); i++) {
        long long id = bus_ids[i];
        long long j = 1;
        while (!is_divisible_by(solution.first + j * solution.second + i, id))
            j++;
        solution.first = solution.first + j * solution.second;
        j = 1;

        // find solution.second
        while (!is_divisible_by(solution.first + j * solution.second + i, id))
            j++;
        solution.second = solution.first + j * solution.second - solution.first;
        // cout << "solution: " << solution.first << " " << solution.second << endl;

        assert(check_solution(solution, bus_ids, i));
    }

    if (solution.first > solution.second)
        solution.first = solution.first % solution.second;

    // write output
    cout << "solution: " << solution.first << endl;
}