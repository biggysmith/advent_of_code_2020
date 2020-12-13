#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

struct contains_t{
    int number;
    std::string bag_name;
};

struct bag_t{
    std::string bag_name;
    std::vector<contains_t> contains;
};

std::vector<std::string> split(const std::string& str, char delim)
{
   std::vector<std::string> elems;
   std::string elem;
   std::istringstream iss(str);
   while (std::getline(iss, elem, delim)){
      elems.push_back(elem);
   }
   return elems;
}

contains_t parse_contains(const std::string& s){
    auto contain_split = split(s, ' ');
    return { std::stoi(contain_split[1]), contain_split[2]+" "+contain_split[3] };
}

bag_t parse_bag(const std::string& s){
    bag_t bag;

    size_t contain_pos = s.find(" bags");
    bag.bag_name = s.substr(0, contain_pos);

    auto contains_str = s.substr(s.find("contain")+7, s.size());
    auto contains_split = split(contains_str, ',');
    if(contains_split.size() == 1){
        if(contains_split[0].find("no other bags") != std::string::npos){
            bag.contains.push_back({0, ""});
        }else{
            bag.contains.push_back(parse_contains(contains_split[0]));
        }
    }else{
        for(auto r : contains_split){
            bag.contains.push_back(parse_contains(r));
        }
    }

    return bag;
}

std::map<std::string,std::vector<contains_t>> parse_rules(const std::string& file){
    std::map<std::string,std::vector<contains_t>> ret;

    std::ifstream file_stream(file);
    if(!file_stream){
        std::cout << "cannot open file" << std::endl;
        return ret;
    }

    std::string line;
    while (std::getline(file_stream, line)) 
    {
        auto bag = parse_bag(line);
        ret[bag.bag_name] = bag.contains;
    }

    return ret;
}

int can_contain(const std::map<std::string,std::vector<contains_t>>& bag_map,const std::vector<contains_t>& sub_bags,const std::string& outer_bag){
    int found = 0;
    for(auto& bag : sub_bags){
        if(bag.bag_name == outer_bag){
            found++;
        }
        if(bag_map.find(bag.bag_name) != bag_map.end()) {
            found += can_contain(bag_map,bag_map.at(bag.bag_name),outer_bag);
        }
    }
    return found;
}


int bags_required(const std::map<std::string,std::vector<contains_t>>& bag_map,const contains_t& outer_bag){
    if(outer_bag.number == 0){
        return 0;
    }
    int required = 0;
    for(auto& bag : bag_map.at(outer_bag.bag_name)){
        required += bag.number + bags_required(bag_map,bag);
    }
    return outer_bag.number * required;
}

void main()
{
    auto bag_map = parse_rules("../src/day07/day7_input.txt");

    // part 1
    {
        int found = 0;
        for (auto& bag : bag_map) {
            found += can_contain(bag_map, bag.second, "shiny gold") > 0;
        }
        std::cout << found << std::endl;
    }

    // part 2
    {
        int found = 0;
        for(auto& bag : bag_map["shiny gold"]){
            found += bag.number + bags_required(bag_map, bag);
        }
        std::cout << found << std::endl;
    }
}