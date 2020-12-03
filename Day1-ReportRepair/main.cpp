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
    vector<int> numbers;
    int number;

    // ifstream input("input/test-input.txt");
    ifstream input("input/input.txt");
    while (input >> number) {
        numbers.push_back(number);
    }

    // do some calculating
    int result = -1;
    for (size_t i = 0; i < numbers.size(); i++) {
        for (size_t j = i + 1; j < numbers.size(); j++) {
            for (size_t k = j + 1; k < numbers.size(); k++) {
                if (numbers[i] + numbers[j] + numbers[k] == 2020) {
                    result = numbers[i] * numbers[j] * numbers[k];
                }
            }
            if (result != -1) break;
        }
        if (result != -1) break;
    }

    // write output
    cout << result << endl;
}