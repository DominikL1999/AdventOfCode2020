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

bool can_be_sum_of(vector<int>& sum_numbers, int n) {
    for (auto it1 = sum_numbers.begin(); it1 != sum_numbers.end(); it1++) {
        for (auto it2 = sum_numbers.begin()++; it2 != sum_numbers.end(); it2++) {
            if (*it1 + *it2 == n) return true;
        }
    }
    return false;
}

void test_numbers(vector<int>& numbers, size_t preamble_size, size_t& mistake_pos) {
    vector<int> sum_numbers;
    for (size_t i = 0; i < preamble_size; i++)
        sum_numbers.push_back(numbers[i]);
    for (size_t i = preamble_size; i < numbers.size(); i++) {
        if (!can_be_sum_of(sum_numbers, numbers[i])) {
            mistake_pos = i;
            break;
        }
        sum_numbers.erase(sum_numbers.begin());
        sum_numbers.push_back(numbers[i]);
    }
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    
    vector<int> numbers;
    int number;
    while (input >> number) numbers.push_back(number);

    // do some calculating
    size_t mistake_pos;
    test_numbers(numbers, 25, mistake_pos);

    // write output
    cout << "solution: " << numbers[mistake_pos] << endl;
}