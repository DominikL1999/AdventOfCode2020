#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using std::ifstream;
using std::vector;
using std::string;
using std::pair;
using std::getline;
using std::cin;
using std::cout;
using std::endl;

long long get_paths(vector<int>& adapters, vector<long long>& paths, size_t node) {
    if (node == adapters.size() - 1) return 1;
    
    long long sum = 0;
    for (size_t i = 1; i <= 3 && node + i < adapters.size(); i++) {
        size_t pos = node + i;
        if (adapters[pos] - adapters[node] <= 3) {
            if (paths[pos] == -1) {
                paths[pos] = get_paths(adapters, paths, pos);
            }
            sum += paths[pos];
        }
        else break;
    }
    return sum;
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input-small.txt");
    // ifstream input("input/test-input-large.txt");
    vector<int> adapters;
    int adapter;
    adapters.push_back(0);
    while (input >> adapter) {
        adapters.push_back(adapter);
    }

    std::sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters[adapters.size() - 1] + 3); // add built-in adapter

    // do some calculating

    vector<long long> paths = vector<long long>(adapters.size(), -1);
    long long path_count = get_paths(adapters, paths, 0);

    // write output
    cout << "number of paths: " << path_count << endl;
}