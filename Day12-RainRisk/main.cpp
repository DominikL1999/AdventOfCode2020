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
using std::endl;

using Instruction = pair<char, int>;
using Position = pair<int, int>;

Position operator+(const Position& p1, const Position& p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

Position operator*(const Position& pos, int value) {
    return {pos.first * value, pos.second * value};
}

Position& operator+=(Position& p1, const Position& p2) {
    p1.first += p2.first;
    p1.second += p2.second;
    return p1;
}

ostream& operator<<(ostream& output, const Position& pos) {
    output << "(" << pos.first << "," << pos.second << ")";
    return output;
}

pair<int, int> get_direction_pair(const char& c) {
    switch(c) {
        case 'N': return {-1, 0};
        case 'E': return {0, 1};
        case 'S': return {1, 0};
        default: return {0, -1};
    }
}

struct ShipState {
    Position pos;
    Position distance_to_waypoint;

private:
    void rotate_waypoint_left(int degrees) {
        switch(degrees) {
            case 90:
                distance_to_waypoint = {-distance_to_waypoint.second, distance_to_waypoint.first};
                break;
            case 180:
                distance_to_waypoint = distance_to_waypoint * -1;
                break;
            case 270:
                distance_to_waypoint = {distance_to_waypoint.second, -distance_to_waypoint.first};
                break;
        }
    }

    void rotate_waypoint_right(int degrees) {
        rotate_waypoint_left(360 - degrees);
    }

public:

    friend ostream& operator<<(ostream& output, const ShipState& ship_state) {
        output << ship_state.pos << " --> " << ship_state.distance_to_waypoint;
        return output;
    }

    void move(Instruction instruction) {
        switch(instruction.first) {
            case 'L': {
                rotate_waypoint_left(instruction.second);
                break;
            }
            case 'R': {
                rotate_waypoint_right(instruction.second);
                break;
            }
            case 'F': {
                Position movement = distance_to_waypoint * instruction.second;
                pos += movement;
                break;
            }
            default: {
                distance_to_waypoint += get_direction_pair(instruction.first) * instruction.second;
                break;
            }
        }
    }
};

const Position INITIAL_POSITION{0, 0};
const Position INTIAL_DISTANCE_TO_WAYPOINT{-1, 10}; // param 1: y, param 2: x

int get_manhattan_distance(const Position p1, const Position p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main() {
    // parse input

    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    vector<Instruction> instructions;
    while (getline(input, line)) {
        instructions.push_back({line[0], stoi(line.substr(1))});
    }

    // do some calculating
    ShipState ship{INITIAL_POSITION, INTIAL_DISTANCE_TO_WAYPOINT};
    for (auto instruction : instructions) {
        ship.move(instruction);
    }

    int manhattan_distance = get_manhattan_distance(INITIAL_POSITION, ship.pos);

    // write output
    cout << "manhattan distance: " << manhattan_distance << endl;
}