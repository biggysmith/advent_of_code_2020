#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
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

    // part 1
    {
        std::vector<int> errors;
        for (auto& t : input.nearby_tickets) {
            auto invalids = validate_ticket(input.rules, t);
            if (!invalids.empty()) {
                for (auto i : invalids) {
                    errors.push_back(i);
                }
            }
        }

        int c = 0;
        for (auto i : errors) {
            std::cout << (c++ != 0 ? " + " : "") << i;
        }
        std::cout << " = " << std::accumulate(errors.begin(), errors.end(), 0) << std::endl;
    }

    {
        std::vector<ticket_t> valid_tickets;
        for (auto& t : input.nearby_tickets) {
            auto invalids = validate_ticket(input.rules, t);
            if (invalids.empty()) {
                valid_tickets.push_back(t);
            }
        }

        int columns = (int)valid_tickets.front().size();
        int rows = (int)valid_tickets.size();

        std::vector<std::set<int>> valid_sets(columns);

        for(int col=0; col<columns; ++col){
            for(int i=0; i<input.rules.size(); ++i){
                bool valid = true;
                for(int row=0; row<rows; ++row){
                    auto& r = input.rules[i];
                    int val = valid_tickets[row][col];
                    if(!((val >= r.r0 && val <= r.r1) || (val >= r.r2 && val <= r.r3))){
                        valid = false;
                        break;
                    }
                }
                if(valid){      
                    valid_sets[col].insert(i);
                }
            }
        }

        std::vector<bool> found_rule(columns,0);

        auto solved = [&]{
            return std::all_of(valid_sets.begin(),valid_sets.end(),[](auto& s){ return s.size()<=1; });
        };

        auto remove_rule = [&](int rn){
            for(int r=0; r<found_rule.size(); ++r){
                if(!found_rule[r]){
                    valid_sets[r].erase(rn);
                }
            }
        };

        auto refresh = [&](){
            for(int c=0; c<columns; ++c){
                if(!found_rule[c] && valid_sets[c].size()==1){
                    found_rule[c] = true;
                    remove_rule(*valid_sets[c].begin());
                    return;
                }
            }
        };

        while(!solved()){
            refresh();
        }

        std::cout << std::endl << "my ticket:";
        for(auto i : input.my_ticket){
            std::cout << i << ",";
        }
        std::cout << std::endl << std::endl;

        std::vector<size_t> prod;
        for(int c=0; c<columns; ++c){
            int field_id = *valid_sets[c].begin();
            std::cout << c << " - " << input.rules[field_id].name << " : " << input.my_ticket[c] << std::endl;
            if(field_id < 6){
                prod.push_back(input.my_ticket[c]);
            }
        }

        std::cout << std::endl;
        int c = 0;
        for (auto i : prod) {
            std::cout << (c++ != 0 ? " * " : "") << i;
        }
        std::cout << " = " << std::accumulate(prod.begin(), prod.end(), 1ULL, std::multiplies<size_t>()) << std::endl;
    }


}
