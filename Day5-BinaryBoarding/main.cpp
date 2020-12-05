#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

using std::ifstream;
using std::vector;
using std::string;
using std::getline;
using std::cout;
using std::endl;

int get_binary_value(string data, char zero_value, char one_value) {
    string value_string;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == zero_value) value_string.push_back('1');
        else if (data[i] == one_value) value_string.push_back('0');
        else assert(false);
    }

    int value = stoi(value_string, nullptr, 2);
    return value;
}

int get_id(string boarding_pass) {
    assert(boarding_pass.size() == 10);
    int row = get_binary_value(boarding_pass.substr(0, 7), 'B', 'F');
    int col = get_binary_value(boarding_pass.substr(7, 3), 'R', 'L');

    return row * 8 + col;
}

int main() {
    // parse input

    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");

    vector<string> boarding_passes;
    string line;
    while (getline(input, line)) {
        boarding_passes.push_back(line);
    }

    // do some calculating
    vector<int> ids;
    for (string pass : boarding_passes) {
        int id = get_id(pass);
        ids.push_back(id);
    }
    sort(ids.begin(), ids.end());

    int prev_id = ids[0];
    int my_id;
    for (size_t i = 1; i < ids.size(); i++) {
        if (prev_id + 2 != ids[i]) {
            prev_id = ids[i];
        }
        else {
            my_id = prev_id + 1;
            break;
        }
    }

    // write output
    cout << "my seat id: " << my_id << endl;
}