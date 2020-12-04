#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>

using std::ifstream;
using std::vector;
using std::map;
using std::pair;
using std::string;
using std::getline;
using std::cout;
using std::endl;

const vector<string> required_fields{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};
const vector<string> optional_fields{"cid"};
const vector<string> eye_colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

// split a string into strings, using ' ' as delimiter
template <class Container>
void split(const std::string& str, Container& cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(cont));
}

struct Passport {
    map<string, string> fields;
};

pair<string, string> split_field(string field) {
    size_t pos = field.find(':');
    size_t length = field.size();
    return pair{field.substr(0, pos), field.substr(pos + 1, length - pos)};
}

bool contains(map<string, string>& fields, string& key) {
    return fields.find(key) != fields.end();
}

bool is_between(int lb, int ub, int value) {
    return lb <= value && value <= ub;
}

int safe_stoi(string s) {
    try {
        return stoi(s);
    } catch (const std::exception& e) {
        return false;
    }
}

bool is_valid_field(pair<string, string> field) {
    if (field.first == "byr") {
        int year = safe_stoi(field.second);
        return is_between(1920, 2002, year);
    }
    else if (field.first == "iyr") {
        int year = safe_stoi(field.second);
        return is_between(2010, 2020, year);
    }
    else if (field.first == "eyr") {
        int year = safe_stoi(field.second);
        return is_between(2020, 2030, year);
    }
    else if (field.first == "hgt") {
        size_t length = field.second.size();
        string unit = field.second.substr(length - 2, 2);
        if (unit == "cm") {
            int cm;
            sscanf(field.second.c_str(), "%icm", &cm);
            return is_between(150, 193, cm);
        }
        else if (unit == "in") {
            int in;
            sscanf(field.second.c_str(), "%iin", &in);
            return is_between(59, 76, in);
        }
        else {
            return false;
        }
        
    }
    else if (field.first == "hcl") {
        char buffer[10];
        sscanf(field.second.c_str(), "#%s", buffer);
        string x = buffer;
        if (x.size() != 6) return false;
        for (char c : x) {
            int lb_letter = 'a';
            int ub_letter = 'f';
            int lb_number = '0';
            int ub_number = '9';
            int val = c;
            return is_between(lb_letter, ub_letter, val) || is_between(lb_number, ub_number, val);
        }
    }
    else if (field.first == "ecl") {
        for (string color : eye_colors) {
            if (field.second == color) return true;
        }
        return false;
    }
    else if (field.first == "pid") {
        for (char c : field.second) {
            int lb_number = '0';
            int ub_number = '9';
            int val = c;
            if (!is_between(lb_number, ub_number, val)) return false;
        }
        return field.second.size() == 9;
    }
    else if (field.first == "cid") {
        return true;
    }
    return false;
}

bool is_valid_passport(Passport p) {
    for (string field_name : required_fields)
        if (!contains(p.fields, field_name)) return false;

    for (pair<string, string> field : p.fields)
        if (!is_valid_field(field)) return false;

    return true;
}

int main() {
    // parse input
    ifstream input("input/input.txt");
    // ifstream input("input/test-input.txt");
    string line;
    int valid_passports = 0;
    Passport p;

    while (getline(input, line)) {
        if (line == "") {
            if (is_valid_passport(p)) valid_passports++;
            p.fields.clear(); // start new passport
        }
        else {
            // split line and add fields into p
            vector<string> fields;
            split(line, fields);
            for (size_t i = 0; i < fields.size(); i++) {
                pair<string, string> field = split_field(fields[i]);
                p.fields[field.first] = field.second;
            }
        } 
    }
    if (is_valid_passport(p)) valid_passports++;

    cout << "number of valid passports: " << valid_passports << endl;
}