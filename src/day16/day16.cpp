#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

struct rule_t{
    std::string name;
    int r0, r1, r2, r3;
};

using ticket_t = std::vector<int>;

struct data_t{
    std::vector<rule_t> rules;
    ticket_t my_ticket;
    std::vector<ticket_t> nearby_tickets;
};

data_t parse_input(const std::string& file){
    data_t data;

    int mode = 0;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){
        if(line == ""){
            mode++;
        }else if(mode==0){
            std::string name = line.substr(0,line.find(':'));
            line = line.substr(line.find(':')+2);

            std::string sub;
            std::stringstream ss(line);
            std::getline(ss, sub, ' ');
            int r0 = std::stoi(sub.substr(0,sub.find('-')));
            int r1 = std::stoi(sub.substr(sub.find('-')+1));

            std::getline(ss, sub, ' ');
            std::getline(ss, sub, ' ');
            int r2 = std::stoi(sub.substr(0,sub.find('-')));
            int r3 = std::stoi(sub.substr(sub.find('-')+1));

            data.rules.push_back({ name, r0, r1, r2, r3 });
        }else if(mode == 1){
            if(line != "your ticket:"){
                std::string sub;
                std::stringstream ss(line);
                while(std::getline(ss, sub, ',')){
                    data.my_ticket.push_back(std::stoi(sub));
                }
            }
        }else if(mode == 2){
            if(line != "nearby tickets:"){
                data.nearby_tickets.push_back(ticket_t());

                std::string sub;
                std::stringstream ss(line);
                while(std::getline(ss, sub, ',')){
                    data.nearby_tickets.back().push_back(std::stoi(sub));
                }
            }
        }
    }

    return data;
}

std::vector<int> validate_ticket(const std::vector<rule_t>& rules,const ticket_t& ticket){
    std::vector<int> invalids;
    for(auto i : ticket){
        bool valid_for_any_field = false;
        for(auto& r : rules){
            valid_for_any_field |= ((i >= r.r0 && i<=r.r1) || (i >= r.r2 && i <= r.r3));
        }
        if(!valid_for_any_field){
            invalids.push_back(i);
        }
    }
    return invalids;
}

void main()
{
    auto input = parse_input("../src/day16/day16_input.txt");

    std::vector<int> errors;
    for(auto& t : input.nearby_tickets){
        auto invalids = validate_ticket(input.rules, t);
        if(!invalids.empty()){
            std::cout << "invalid" << std::endl;
            for(auto i : invalids){
                errors.push_back(i);
            }   
        }else{
            std::cout << "valid" << std::endl;
        }
    }

    for(auto i : errors){
        std::cout << i << " + ";
    } 
    std::cout << std::endl;
    std::cout << std::accumulate(errors.begin(), errors.end(), 0) << std::endl;

    /*for(auto& r : input.rules){
        std::cout << r.name << ": " << r.r0 << "-" << r.r1 << " or " << r.r2 << "-" << r.r3 << std::endl; 
    }
    std::cout << std::endl;

    std::cout << "your ticket:" << std::endl;
    for(auto i : input.my_ticket){
        std::cout << i << ",";
    }
    std::cout << std::endl << std::endl;

    std::cout << "nearby ticket:" << std::endl;
    for(auto& t : input.nearby_tickets){
        for(auto i : t){
            std::cout << i << ",";
        }
        std::cout << std::endl;
    }*/
}