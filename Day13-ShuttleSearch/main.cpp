#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::vector;
using std::string;
using std::pair;
using std::getline;
using std::cout;
using std::endl;

vector<string> split(string line, char delim) {
    vector<string> bus_strings;

    size_t pos;
    while ((pos = line.find(delim)) != string::npos) {
        bus_strings.push_back(line.substr(0, pos));
        line.erase(0, pos + 1);
    }
    bus_strings.push_back(line);

    return bus_strings;
}

int get_waiting_time(int estimate, int id) {
    return id - estimate % id;
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    getline(input, line);
    int estimate = stoi(line);
    vector<int> buses;
    getline(input, line);
    vector<string> bus_strings = split(line, ',');
    for (auto bus_string : bus_strings)
        if (bus_string != "x")
            buses.push_back(stoi(bus_string));

    // do some calculating
    int min_waiting_id = 0;
    int min_waiting_time = INT32_MAX;
    for (auto id : buses) {
        int waiting_time = get_waiting_time(estimate, id);
        if (waiting_time < min_waiting_time) {
            min_waiting_id = id;
            min_waiting_time = waiting_time;
        }
    }

    // write output
    cout << "solution: " << min_waiting_id * min_waiting_time << endl;
}