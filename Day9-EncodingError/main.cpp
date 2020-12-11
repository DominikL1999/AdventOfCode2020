#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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

pair<int, int> smallest_and_largest(vector<int>& numbers, pair<size_t, size_t> range) {
    int smallest = INT_MAX;
    int biggest = INT_MIN;
    for (size_t i = range.first; i <= range.second; i++) {
        smallest = std::min(smallest, numbers[i]);
        biggest = std::max(biggest, numbers[i]);
    }

    return {smallest, biggest};
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
    int mistake = numbers[mistake_pos];
    int solution = 0;

    size_t step_size = 2;
    while (solution == 0) {
        int sum = 0;
        for (size_t i = 0; i < step_size; i++)
            sum += numbers[i];
        if (sum == mistake) {
            pair sol = smallest_and_largest(numbers, {0, step_size - 1});
            solution = sol.first + sol.second;
            break;
        }

        for (size_t i = 1; i <= numbers.size() - step_size; i++) {
            sum -= numbers[i - 1];
            sum += numbers[i + step_size - 1];
            if (sum == mistake) {
                pair sol = smallest_and_largest(numbers, {i, i + step_size - 1});
                solution = sol.first + sol.second;
                break;
            }
        }

        step_size++;
    }

    // write output
    cout << "solution: " << solution << endl;
}