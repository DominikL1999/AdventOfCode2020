#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::ostream;
using std::vector;
using std::string;
using std::pair;
using std::getline;
using std::cout;
using std::cin;
using std::endl;

enum SeatState { Floor, Empty, Occupied };

using WaitingArea = vector<vector<SeatState>>;

ostream &operator<<(ostream& output, SeatState seat_state) {
    if (seat_state == Floor) output << '.';
    else if (seat_state == Empty) output << 'L';
    else output << '#';
    return output;
}

ostream &operator<<(ostream& output, WaitingArea wa) {
    for (auto row : wa) {
        for (auto seat_state : row)
            output << seat_state;
        output << endl;
    }
    return output;
}

SeatState parse_seat(char c) {
    if (c == '.') return Floor;
    else if (c == 'L') return Empty;
    else return Occupied;
}

bool in_bounds(size_t lb, size_t ub, size_t val) {
    return lb <= val && val <= ub;
}

int n_of_occ_surrounding_seats(WaitingArea& wa, size_t i, size_t j) {
    int n_occupied = 0;
    for (size_t i_ = 0; i_ <= 2; i_++)
        for (size_t j_ = 0; j_ <= 2; j_++) {
            size_t i_cur = i + i_ - 1;
            size_t j_cur = j + j_ - 1;
            if (!(in_bounds(0, wa.size() - 1, i_cur) && in_bounds(0, wa[0].size() - 1, j_cur))) continue;
            else if (i_ == 1 && j_ == 1) continue;
            else if (wa[i_cur][j_cur] == Occupied) n_occupied++;
        }
    
    return n_occupied;
}

// returns, whether the wa has changed
bool do_turn(WaitingArea& wa) {
    vector<pair<size_t, size_t>> to_occupied;
    vector<pair<size_t, size_t>> to_empty;
    bool will_change = false;

    for (size_t i = 0; i < wa.size(); i++) {
        for (size_t j = 0; j < wa[0].size(); j++) {
            if (wa[i][j] == Empty && n_of_occ_surrounding_seats(wa, i, j) == 0) {
                to_occupied.push_back({i, j});
                will_change = true;
            }
            else if (wa[i][j] == Occupied && n_of_occ_surrounding_seats(wa, i, j) >= 4) {
                to_empty.push_back({i, j});
                will_change = true;
            }
        }
    }
    if (!will_change) return false;

    for (auto pos : to_occupied)
        wa[pos.first][pos.second] = Occupied;
    for (auto pos : to_empty)
        wa[pos.first][pos.second] = Empty;

    return true;
}

int number_of_occupied_seats(WaitingArea& wa) {
    int n_occupied = 0;
    for (auto row : wa) {
        for (auto seat_state : row) {
            if (seat_state == Occupied) n_occupied++;
        }
    }
    return n_occupied;
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    WaitingArea wa;
    while (getline(input, line)) {
        wa.push_back({});
        size_t last_row = wa.size() - 1;
        for (char c : line) {
            wa[last_row].push_back(parse_seat(c));
        }
    }

    // do some calculating
    while(do_turn(wa)) {}
    int n_occupied = number_of_occupied_seats(wa);

    // write output
    cout << "number of occupied seats: " << n_occupied << endl;
}