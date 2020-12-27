#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::vector;
using std::string;
using std::pair;
using std::getline;
using std::cout;
using std::endl;

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    vector<size_t> numbers;
    while (input.good()) {
        string substr;
        getline(input, substr, ',');
        numbers.push_back(stoi(substr));
    }

    // do some calculating
    for (size_t i = numbers.size(); i < 2020; i++) {
        size_t last_spoken_number = numbers[numbers.size() - 1];
        size_t last_spoken_pos = SIZE_MAX;
        for (size_t j = numbers.size() - 2; j != SIZE_MAX; j--) {
            if (numbers[j] == last_spoken_number) {
                last_spoken_pos = j; 
                break;
            }
        }
        if (last_spoken_pos == SIZE_MAX) numbers.push_back(0);
        else numbers.push_back(numbers.size() - 1 - last_spoken_pos);
    }

    // write output
    cout << "last number: " << numbers[numbers.size() - 1] << endl;
}