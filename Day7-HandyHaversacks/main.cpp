#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using std::ifstream;
using std::vector;
using std::set;
using std::map;
using std::pair;
using std::string;
using std::getline;
using std::cout;
using std::endl;


// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != ',';
    }));
}

pair<string, string> get_word(string s, char delim = ' ') {
    ltrim(s);
    size_t pos = s.find(delim);
    string s1 = s.substr(0, pos);
    string s2 = s.substr(pos);
    return {s1, s2};
}

pair<string, string> parse_color(string s) {
    auto pair = get_word(s);
    string s1 = pair.first;
    pair = get_word(pair.second);
    return {s1 + ' ' + pair.first, pair.second};
}

pair<string, string> parse_bag(string s) {
    auto pair = parse_color(s);
    string rest = pair.second.substr(13); // remove "bags contain "

    return {pair.first, rest};
}

pair<int, string> parse_number(string s) {
    auto pair = get_word(s);
    int number = stoi(pair.first);
    return {number, pair.second};
}

pair<pair<string, int>, string> parse_number_and_bag(string s) {
    auto pair = parse_number(s);
    auto pair2 = parse_color(pair.second);
    string rest;
    if (pair.first == 1)
        rest = pair2.second.substr(4);
    else
        rest = pair2.second.substr(5);
    return {{pair2.first, pair.first}, rest};
}

// parses a rule
// returns the color of the bag and the colors and quantities of the bags it contains
// Example:
// "light red bags contain 1 bright white bag, 2 muted yellow bags."
// ↓            ↓            ↓            ↓
// <"lightred", [<"bright white", 1>, <"mutedyellow, 2">]>
pair<string, map<string, int>> parse_rule(string line) {
    map<string, int> bags;
    auto pair = parse_bag(line);
    auto pair3 = get_word(pair.second);
    if (get_word(pair.second).first == "no") {
        // "no other bags"
        return {pair.first, bags};
    }

    string rest = pair.second;
    while (rest != ".") {
        auto pair2 = parse_number_and_bag(rest);
        bags[pair2.first.first] = pair2.first.second;
        rest = pair2.second;
    }

    return {pair.first, bags};
}

// void test_1() {
//     string rule_string = "light red bags contain 1 bright white bag, 2 muted yellow bags.";
//     auto rule = parse_rule(rule_string);

//     assert(rule.first == "light red");
//     assert(rule.second.size() == 2);
//     assert(rule.second[0].first == "bright white");
//     assert(rule.second[0].second == 1);
//     assert(rule.second[1].first == "muted yellow");
//     assert(rule.second[1].second == 2);
// }

// void test_2() {
//     string rule_string = "bright white bags contain 1 shiny gold bag.";
//     auto rule = parse_rule(rule_string);

//     assert(rule.first == "bright white");
//     assert(rule.second.size() == 1);
//     assert(rule.second[0].first == "shiny gold");
//     assert(rule.second[0].second == 1);
// }

// void test_3() {
//     string rule_string = "faded blue bags contain no other bags.";
//     auto rule = parse_rule(rule_string);

//     assert(rule.first == "faded blue");
//     assert(rule.second.size() == 0);
// }

// void test_parse_rule() {
//     test_1();
//     test_2();
//     test_3();
// }

template<typename K, typename V>
bool map_contains(map<K, V> map, K key) {
    return map.find(key) != map.end();
}

template<typename T>
bool contains(set<T> set, T val) {
    return set.find(val) != set.end();
}

map<string, set<string>> reverse_rules(map<string, map<string, int>>& rules) {
    map<string, set<string>> reversed_rules;
    for (auto rule : rules) {
        for (auto bag : rule.second) {
            reversed_rules[bag.first].insert(rule.first);
        }
    }

    return reversed_rules;
}

set<string> can_contain(map<string, set<string>>& reversed_rules, string bag) {
    set<string> can_contain_set;
    
    for (string b : reversed_rules[bag]) {
        can_contain_set.insert(b);

        set<string> can_contain_set_inner = can_contain(reversed_rules, b);
        for (string inner_b : can_contain_set_inner) can_contain_set.insert(inner_b);
    }

    return can_contain_set;
}

int main() {
    // parse input
    map<string, map<string, int>> rules;
    ifstream input("input/input.txt");
    string line;
    while (getline(input, line)) {
        auto rule = parse_rule(line);
        rules[rule.first] = rule.second;
    }

    // do some calculating
    map<string, set<string>> reversed_rules = reverse_rules(rules);
    set<string> contains_shiny_gold = can_contain(reversed_rules, "shiny gold");

    cout << "solution: " << contains_shiny_gold.size() << endl;

    // write output
}