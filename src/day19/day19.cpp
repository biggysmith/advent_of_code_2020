#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <regex>

struct rule_t{
    char s;
    std::vector<int> sub_rules0;
    std::vector<int> sub_rules1;
};

std::pair<std::unordered_map<int,rule_t>,std::vector<std::string>> parse_input(const std::string& file){
   std::pair<std::unordered_map<int,rule_t>,std::vector<std::string>> input;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){
        if(line == ""){
            break;
        }

        std::regex re("[^\\s:]+");
        std::sregex_token_iterator first{line.begin(), line.end(), re}, last;
        std::vector<std::string> tokens{first, last};

        rule_t rule;
        if(tokens[1].find('"') != std::string::npos){
            rule.s = tokens[1][1];
        }else {
            auto* vec = &rule.sub_rules0;
            for(int i=1; i<tokens.size(); ++i){
                if(tokens[i] == "|"){
                    vec = &rule.sub_rules1;
                    continue;
                }
                vec->push_back(std::stoi(tokens[i]));
            }         
        }
        input.first[std::stoi(tokens[0])] = rule;
    }

    while(std::getline(file_stream, line)){
        input.second.push_back(line);
    }

    return input;
}

bool check(const std::unordered_map<int,rule_t>& rules, const rule_t& rule, const std::string& str, std::vector<int>& pos)
{
    if (rule.sub_rules0.empty()) {
        pos.erase(std::remove_if(pos.begin(),pos.end(),[&](auto& p){ return str[p++] != rule.s; }),pos.end());
        return !pos.empty();
    }

    std::vector<int> local_pos;
    bool match = false;
    auto sub_pos = pos;
    for (auto n : rule.sub_rules0) {
        if(!(match = check(rules, rules.at(n), str, sub_pos))){
            break;
        }
    }

    if(match){
        std::copy(sub_pos.begin(), sub_pos.end(), std::back_inserter(local_pos));
    }

    if (rule.sub_rules1.size()) 
    {
        sub_pos = pos;
        for (auto n : rule.sub_rules1){
            if(!(match = check(rules, rules.at(n), str, sub_pos))){
                break;
            }
        }

        if(match){
            std::copy(sub_pos.begin(), sub_pos.end(), std::back_inserter(local_pos));
        }
    }

    if(local_pos.empty()){
        return false;
    }else{
        pos = local_pos;
        return true;
    }
}

bool check(const std::unordered_map<int,rule_t>& rules, const std::string& str){
    std::vector<int> pos(1,0);
    return check(rules, rules.at(0), str, pos) && std::any_of(pos.begin(),pos.end(),[&](auto n){ return n >= str.size(); });
}


void main()
{   
    auto input = parse_input("../src/day19/day19_input.txt");

    {
        int zeros = 0;
        for (auto& s : input.second) {
            zeros += check(input.first, s);
        }
        std::cout << "part1: " << zeros << std::endl;
    }

    {
        input.first[8] = { 0, { 42 }, { 42, 8 } };
        input.first[11] = { 0, { 42, 31 }, { 42, 11, 31 } };

        int zeros = 0;
        for (auto& s : input.second) {
            zeros += check(input.first, s);
        }
        std::cout << "part2: " << zeros << std::endl;
    }
}


