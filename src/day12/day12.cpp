#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

struct instruction_t{
    char cmd;
    int val;
};

std::vector<instruction_t> parse_instructions(const std::string& file){
    std::vector<instruction_t> route_lines;

    std::ifstream file_stream(file);
    if(!file_stream){
        std::cout << "cannot open file" << std::endl;
        return route_lines;
    }

    std::string line;
    while (std::getline(file_stream, line)) {
        route_lines.push_back({ line[0], std::stoi(line.substr(1,line.size())) });
    }

    return route_lines;
}


int process0(const std::vector<instruction_t>& instructions){
    int x = 0;
    int y = 0;
    int dx = 1;
    int dy = 0;

    for(auto& i : instructions){
        if(i.cmd == 'N'){
            y += i.val;
        }else if(i.cmd == 'S'){
            y -= i.val;
        }else if(i.cmd == 'E'){
            x += i.val;
        }else if(i.cmd == 'W'){
            x -= i.val;
        }else if(i.cmd == 'L'){
            if(i.val == 90){
                std::tie(dx,dy) = std::pair(-dy,dx);
            }else if(i.val == 180){
                std::tie(dx,dy) = std::pair(-dx,-dy);
            }else if(i.val == 270){
                std::tie(dx,dy) = std::pair(dy,-dx);
            }
        }else if(i.cmd == 'R'){
            if(i.val == 90){
                std::tie(dx,dy) = std::pair(dy,-dx);
            }else if(i.val == 180){
                std::tie(dx,dy) = std::pair(-dx,-dy);
            }else if(i.val == 270){
                std::tie(dx,dy) = std::pair(-dy,dx);
            }
        }else if(i.cmd == 'F'){
            x += dx*i.val;
            y += dy*i.val;
        }
    }

    return abs(x) + abs(y);
}

int process1(const std::vector<instruction_t>& instructions){
    int x = 0;
    int y = 0;
    int wx = 10;
    int wy = 1;

    for(auto& i : instructions){
        if(i.cmd == 'N'){
            wy += i.val;
        }else if(i.cmd == 'S'){
            wy -= i.val;
        }else if(i.cmd == 'E'){
            wx += i.val;
        }else if(i.cmd == 'W'){
            wx -= i.val;
        }else if(i.cmd == 'L'){
            if(i.val == 90){
                std::tie(wx,wy) = std::pair(-wy,wx);
            }else if(i.val == 180){
                std::tie(wx,wy) = std::pair(-wx,-wy);
            }else if(i.val == 270){
                std::tie(wx,wy) = std::pair(wy,-wx);
            }
        }else if(i.cmd == 'R'){
            if(i.val == 90){
                std::tie(wx,wy) = std::pair(wy,-wx);
            }else if(i.val == 180){
                std::tie(wx,wy) = std::pair(-wx,-wy);
            }else if(i.val == 270){
                std::tie(wx,wy) = std::pair(-wy,wx);
            }
        }else if(i.cmd == 'F'){
            x += wx*i.val;
            y += wy*i.val;
        }
    }

    return abs(x) + abs(y);
}

void print_instructions(const std::vector<instruction_t>& instructions){
    for(auto& i : instructions){
        std::cout << i.cmd << i.val << std::endl;
    }
    std::cout << std::endl;
}

void main()
{
    auto instructions = parse_instructions("../src/day12/day12_input.txt");

    std::cout << process0(instructions) << std::endl;

    std::cout << process1(instructions) << std::endl;
}