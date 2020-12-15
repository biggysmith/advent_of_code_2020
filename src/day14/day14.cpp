#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>

struct load{
    size_t addr;
    size_t val;
};

struct program{
    std::string mask;
    std::vector<load> loads;
};

std::vector<program> parse_input(const std::string& file){
    std::vector<program> input;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){
        if(line.substr(0,4) == "mask"){
            program prog;
            prog.mask = line.substr(7);
            input.push_back(prog);
        }else if(line.substr(0,3) == "mem"){
            auto& prog = input.back();
            size_t addr = std::stoull(line.substr(4,line.find(']')));
            size_t val = std::stoull(line.substr(line.find('=')+1));
            prog.loads.push_back({addr,val});
        }
    }

    return input;
}


void main()
{
    auto input = parse_input("../src/day14/day14_input.txt");

    // part 1
    {
        std::map<size_t, size_t> memory;
        std::string mask;

        auto write = [&](const load& l) {
            size_t val = l.val;
            for (int i=0; i<36; ++i) {
                if (mask[35-i] == '0') {
                    val &= ~(1ULL << i);
                }else if (mask[35-i] == '1') {
                    val |= 1ULL << i;
                }
            }
            memory[l.addr] = val;
        };

        for (auto& i : input) {
            mask = i.mask;
            for (auto& l : i.loads) {
                write(l);
            }
        }

        size_t sum = 0;
        for (auto& m : memory) {
            sum += m.second;
        }

        std::cout << "part1: " << sum << std::endl;
    }


    // part 2
    {
        std::map<size_t, size_t> memory;
        std::string mask;

        auto write = [&](const load& l) {
            std::vector<int> floating;
            size_t addr = l.addr;
            for (int i=0; i<36; ++i) {
                if (mask[35-i] == 'X') {
                    floating.push_back(i);
                }else if (mask[35-i] == '1') {
                    addr |= 1ULL << i;
                }
            }

            int num_addrs = 1 << floating.size();
            for(int i=0; i<num_addrs; ++i){
                size_t addr2 = addr;
                for(int j=0; j<floating.size(); ++j){
                    if((i >> j) & 1ULL){
                        addr2 |= 1ULL << floating[j];
                    }else{
                        addr2 &= ~(1ULL << floating[j]);
                    }
                }
                memory[addr2] = l.val;
            }
        };

        for (auto& i : input) {
            mask = i.mask;
            for (auto& l : i.loads) {
                write(l);
            }
        }

        size_t sum = 0;
        for (auto& m : memory) {
            sum += m.second;
        }

        std::cout << "part2: " << sum << std::endl;
    }

}