#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    // parse input
    vector<int> numbers;
    int number;

    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");
    while (input >> number) {
        numbers.push_back(number);
    }

    // do some calculating

    // write output
    cout << "Hello, world!" << endl;
}