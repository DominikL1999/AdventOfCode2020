#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;

const int MAX_LENGTH_STRING = 100;

struct Policy {
    int lb;
    int ub;
    char c;
};

bool isValid(Policy p, string s) {
    int sum = 0;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == p.c) sum++;
    }
    return p.lb <= sum && p.ub >= sum;
}

int main() {
    // parse input

    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");

    int number_of_valid = 0;
    string line;
    while (std::getline(input, line)) {
        Policy p;
        char s[MAX_LENGTH_STRING];

        int ret = std::sscanf(line.c_str(), "%i-%i %c: %s", &p.lb, &p.ub, &p.c, s);
        assert(ret == 4);

        string str = s;

        if (isValid(p, str)) number_of_valid++;
    }

    // write output
    cout << "number of valid policies: " << number_of_valid << endl;

    return 0;
}