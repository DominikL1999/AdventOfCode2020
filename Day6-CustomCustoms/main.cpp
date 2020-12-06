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

size_t get_yeses(string s) {
    sort(s.begin(), s.end());
    auto stream = std::unique(s.begin(), s.end());
    s.resize(std::distance(s.begin(), stream));
    return s.size();
}

int main() {
    // parse input

    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");
    string line;
    vector<string> groups;
    groups.push_back("");

    while (getline(input, line)) {
        if (line == "") {
            // do something with this
            groups.push_back("");
        }
        else {
            groups[groups.size() - 1] += line;
        }
    }

    // do some calculating
    size_t sum = 0;
    for (string group : groups) {
        size_t yeses = get_yeses(group);
        sum += yeses;
    }
 
    // write output
    cout << "solution: " << sum << endl;
}