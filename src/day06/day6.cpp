#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

std::vector<std::map<char,int>> parse_txt(const std::string& file){
    std::vector<std::map<char,int>> ret;

    std::ifstream test_answers(file);
    if(!test_answers){
        std::cout << "cannot open file" << std::endl;
        return ret;
    }

    ret.push_back(std::map<char,int>());
    std::string line;
    while (std::getline(test_answers, line)) {
        std::istringstream ss_line(line);
        if(line == ""){
            ret.push_back(std::map<char,int>());
            continue;
        }
        while(ss_line){
            char answer;
            ss_line >> answer;
            ret.back()[answer]++;
        }
    }

    return ret;
}

std::vector<std::pair<int,std::map<char,int>>> parse_txt2(const std::string& file){
    std::vector<std::pair<int,std::map<char,int>>> ret;

    std::ifstream test_answers(file);
    if(!test_answers){
        std::cout << "cannot open file" << std::endl;
        return ret;
    }

    ret.push_back(std::pair<int,std::map<char,int>>());
    std::string line;
    while (std::getline(test_answers, line)) {
        std::istringstream ss_line(line);
        if(line == ""){
            ret.push_back(std::pair<int,std::map<char,int>>());
            ret.back().first = 0;
            continue;
        }
        char answer;
        while(ss_line >> answer){
            ret.back().second[answer]++;
        }
        ret.back().first++;
    }

    return ret;
}

void main()
{
    auto groups = parse_txt2("../src/day06/day6_input.txt");

    int sum = 0;
    for(auto group : groups){
        int sub_sum = 0;
        for(auto p : group.second){
            if(group.first == p.second){
                sub_sum++;
            }
        }
        sum += sub_sum;
    }
    std::cout << sum << "\n";
}