#include <algorithm>
#include <functional>
#include <stack>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>

std::vector<int> parse_input(const std::string& file){
    std::vector<int> input;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){
        input.push_back(std::stoi(line));
    }

    return input;
}


void main() 
{
    auto keys = parse_input("../src/day25/day25_input.txt");

    bool found = false;
    int64_t loop = 0;
    int64_t value0 = 1;
    int64_t subject_number = 7;

    while(!found){
        loop++;
        
        value0 *= subject_number;
        value0 %= 20201227;

        if(value0 == keys[1]){
            found = true;
        }
    }

    int64_t value1 = 1;

    for(int i=0; i<loop; ++i){
        value1 *= keys[0];
        value1 %= 20201227;
    }

    std::cout << "part1: " << value1 << std::endl;
    std::cout << "part2: " << "thanks crabby!" << std::endl;
}



