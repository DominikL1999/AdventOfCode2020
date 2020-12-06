#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::ifstream;
using std::vector;
using std::string;
using std::getline;
using std::cout;
using std::endl;

bool contains(string s, char c) {
    return s.find(c) < s.size();
}

size_t get_yeses(vector<string> group) {
    int count = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        bool is_in_all = true;
        for (string s : group) {
            if (!contains(s, c)) {
                is_in_all = false;
                break;
            }
        }
        if (is_in_all) count++;
    }
    return count;
}

int main() {
    // parse input

    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");
    string line;
    vector<vector<string>> groups;
    groups.push_back(vector<string>());

    while (getline(input, line)) {
        if (line == "") {
            // do something with this
            groups.push_back(vector<string>());
        }
        else {
            groups[groups.size() - 1].push_back(line);
        }
    }

    // do some calculating
    size_t sum = 0;
    for (vector<string> group : groups) {
        size_t yeses = get_yeses(group);
        sum += yeses;
    }
 
    // write output
    cout << "solution: " << sum << endl;
}