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

enum Direction { North, East, South, West };

Direction parse_direction(char c) {
    switch(c) {
        case 'N': return North;
        case 'E': return East;
        case 'S': return South;
        default: return West;
    }
}

pair<int, int> get_direction_pair(const Direction& dir) {
    switch(dir) {
        case North: return {-1, 0};
        case East: return {0, 1};
        case South: return {1, 0};
        default: return {0, -1};
    }
}

pair<int, int> get_direction_pair(const char& c) {
    return get_direction_pair(parse_direction(c));
}

struct ShipState {
    Direction dir;
    Position pos;

    friend ostream& operator<<(ostream& output, const ShipState& ship_state) {
        output << "(" << ship_state.pos.first << "," << ship_state.pos.second << ") -> " << ship_state.dir;
        return output;
    }

    void move(Instruction instruction) {
        switch(instruction.first) {
            case 'L':
                dir = (Direction)((dir - (instruction.second % 360) / 90 + 4) % 4);
                break;
            case 'R':
                dir = (Direction)((dir + (instruction.second % 360) / 90 + 4) % 4);
                break;
            case 'F':
                pos += get_direction_pair(dir) * instruction.second;
                break;
            default:
                pos += get_direction_pair(instruction.first) * instruction.second;
                break;
        }
    }
};

const Position INITIAL_POSITION{0, 0};
const Direction INITIAL_DIRECTION = East;

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
    ShipState ship{INITIAL_DIRECTION, INITIAL_POSITION};
    for (auto instruction : instructions)
        ship.move(instruction);

    int manhattan_distance = get_manhattan_distance(INITIAL_POSITION, ship.pos);

    // write output
    cout << "manhattan distance: " << manhattan_distance << endl;
}