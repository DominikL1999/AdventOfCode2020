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
    int a;
    int b;
    char c;
};

bool isValid(Policy p, string s) {
    return (s[p.a - 1] == p.c) + (s[p.b - 1] == p.c) == 1;
}

int main() {
    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");

    int number_of_valid = 0;
    string line;
    while (std::getline(input, line)) {
        Policy p;
        char s[MAX_LENGTH_STRING];

        int ret = std::sscanf(line.c_str(), "%i-%i %c: %s", &p.a, &p.b, &p.c, s);
        assert(ret == 4);

        string str = s;

        if (isValid(p, str)) number_of_valid++;
    }

    // write output
    cout << "number of valid policies: " << number_of_valid << endl;

    return 0;
}