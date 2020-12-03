#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::vector;
using std::string;
using std::getline;
using std::cout;
using std::endl;

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
    size_t line_length = geology[0].size();
    int tree_encounters = 0;
    for (size_t x, y = 0; y < geology.size(); x = (x + 3) % line_length, y++) {
        if (geology[y][x] == '#') tree_encounters++;
        else if (geology[y][x] == '.') continue;
        else return 1;
    }

    // write output
    cout << "tree encounters: " << tree_encounters << endl;
}