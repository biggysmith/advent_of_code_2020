#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

struct instruction_t{
    std::string cmd;
    int val;
};

using program_t = std::vector<instruction_t>;

instruction_t parse_instruction(const std::string& op){
    return { op.substr(0, 3), std::stoi(op.substr(3, op.size())) };
}

program_t parse_prog(const std::string& file){
    program_t prog;

    std::ifstream file_stream(file);
    if(!file_stream){
        std::cout << "cannot open file" << std::endl;
        return program_t();
    }

    std::string line;
    while (std::getline(file_stream, line)) {
        prog.push_back(parse_instruction(line));
    }

    return prog;
}

void run_prog1(const program_t& prog){
    std::vector<int> instruction_count(prog.size(),0);

    int acc = 0;
    for(int i=0; i<prog.size(); ){
        instruction_count[i]++;

        for(auto c : instruction_count){
            if(c > 1){
                std::cout << acc << std::endl;
                return;
            }
        }

        if(prog[i].cmd == "nop"){
            i++;
        }else if(prog[i].cmd == "acc"){
            acc += prog[i].val;  
            i++;
        }else if(prog[i].cmd == "jmp"){
            i += prog[i].val;
        }
    }
}

void run_prog2(const program_t& prog){
    int max_iters = 500;
    int acc = 0;
    for(int i=0,c=0; i<prog.size(); ++c){
        if(prog[i].cmd == "nop"){
            i++;
        }else if(prog[i].cmd == "acc"){
            acc += prog[i].val;  
            i++;
        }else if(prog[i].cmd == "jmp"){
            i += prog[i].val;
        }

        if(c > max_iters){
            return;
        }
    }

    std::cout << "woah, it finished: " << acc << std::endl;
}

void main()
{
    auto prog = parse_prog("../src/day08/day8_input.txt");

    run_prog1(prog);

    for(int i=0; i<prog.size(); ++i){
        if(prog[i].cmd == "nop"){
            auto alt_prog = prog;
            alt_prog[i].cmd = "jmp";
            run_prog2(alt_prog);
        }

        if(prog[i].cmd == "jmp"){
            auto alt_prog = prog;
            alt_prog[i].cmd = "nop";
            run_prog2(alt_prog);
        }
    }
}