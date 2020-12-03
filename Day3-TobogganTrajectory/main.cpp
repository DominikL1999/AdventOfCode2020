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

long long check_slope(vector<vector<char>> geology, size_t xDiff, size_t yDiff) {
    size_t line_length = geology[0].size();
    long long tree_encounters = 0;
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

    // do some calculating
    long long tree_encounters_1 = check_slope(geology, 1, 1);
    long long tree_encounters_2 = check_slope(geology, 3, 1);
    long long tree_encounters_3 = check_slope(geology, 5, 1);
    long long tree_encounters_4 = check_slope(geology, 7, 1);
    long long tree_encounters_5 = check_slope(geology, 1, 2);
    long long result = tree_encounters_1 * tree_encounters_2 * tree_encounters_3 * tree_encounters_4 * tree_encounters_5;

    // write output
    cout << "tree encounters: " << result << endl;
}