#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using std::ifstream;
using std::vector;
using std::string;
using std::getline;
using std::cout;
using std::endl;

int check_slope(vector<vector<char>> geology, size_t xDiff, size_t yDiff) {
    size_t line_length = geology[0].size();
    int tree_encounters = 0;
    for (size_t x = 0, y = 0; y < geology.size(); x = (x + xDiff) % line_length, y += yDiff) {
        if (geology[y][x] == '#') tree_encounters++;
        else if (geology[y][x] == '.') continue;
        else {
            cout << "returning -1..." << endl;
            return -1;
        }
    }

    return tree_encounters;
}

int main() {
    // parse input

    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");
    vector<vector<char>> geology;

    string line;
    while (getline(input, line)) {
        geology.push_back(vector(line.begin(), line.end()));
    }

    int tree_encounters = check_slope(geology, 3, 1);

    // do some calculating

    // write output
    cout << "tree encounters: " << tree_encounters << endl;
}