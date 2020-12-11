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

SeatState parse_seat(char c) {
    if (c == '.') return Floor;
    else if (c == 'L') return Empty;
    else return Occupied;
}

bool in_bounds(size_t lb, size_t ub, size_t val) {
    return lb <= val && val <= ub;
}

bool in_bounds(WaitingArea& wa, pair<size_t, size_t> pos) {
    return in_bounds(0, wa.size() - 1, pos.first)
        && in_bounds(0, wa[0].size() - 1, pos.second);
}

// returns whether there is a seat in sight.
// "false" means, that there is no seat in the waiting area in the line of sight
template<class F>
bool look_at(WaitingArea& wa, pair<size_t, size_t> pos, F func, SeatState& next_seat) {
    pos = func(pos);
    while (in_bounds(wa, pos)) {
        if (wa[pos.first][pos.second] == Floor) {
            pos = func(pos);
            continue;
        } else if (wa[pos.first][pos.second] == Empty) {
            next_seat = Empty;
            return true;
        } else {
            next_seat = Occupied;
            return true;
        }
    }
    return false;
}

const vector<pair<size_t, size_t>> directions{
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 1},
    {1, 0},
    {1, -1},
    {0, -1}
};

int n_of_occ_surrounding_seats(WaitingArea& wa, pair<size_t, size_t> pos) {
    int n_occupied = 0;

    SeatState next_seat;
    for (auto direction : directions) {
        if (look_at(
            wa, pos, [direction](auto pos){return pair<size_t, size_t>{pos.first + direction.first, pos.second + direction.second}; }, next_seat)
            && next_seat == Occupied)
            n_occupied++;
    }

    return n_occupied;
}

// returns, whether the waiting area has changed
bool do_turn(WaitingArea& wa) {
    vector<pair<size_t, size_t>> to_occupied;
    vector<pair<size_t, size_t>> to_empty;
    bool will_change = false;

    for (size_t i = 0; i < wa.size(); i++) {
        for (size_t j = 0; j < wa[0].size(); j++) {
            int n_occupied = n_of_occ_surrounding_seats(wa, {i, j});
            if (wa[i][j] == Empty && n_occupied == 0) {
                to_occupied.push_back({i, j});
                will_change = true;
            }
            else if (wa[i][j] == Occupied && n_occupied >= 5) {
                if (i == 1 && j == 0)
                    cout << "n_occupied: " << n_occupied << endl;
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