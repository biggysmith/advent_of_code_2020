#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <regex>
#include <cctype>
	
std::vector<std::string> parse_input(const std::string& file){
    std::vector<std::string> input;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){
        input.push_back(line);
    }

    return input;
}

bool is_number(const std::string& s){
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

long long eval(const std::vector<std::string>& tokens,int& pos,bool advanced){
    long long sum = 0;

    auto get_token = [&]()
    {
        while (pos < tokens.size()) {
            auto token = tokens[pos++];

            if (is_number(token)) {
                return std::make_pair(0,std::stoll(token));
            } else if (token == "+") {
                return std::make_pair(1,0LL);
            } else if (token == "-") {
                return std::make_pair(2,0LL);
            } else if (token == "*") {
                return std::make_pair(3,0LL);
            } else if (token == "/") {
                return std::make_pair(4,0LL);
            }else if (token == "(") {
                long long val = eval(tokens,pos,advanced); pos++;
                return std::make_pair(0,val);
            }
        }

        return std::make_pair(-1,0LL);
    };

    while (pos < tokens.size() && tokens[pos] != ")")
    {
        auto token = get_token();
        if(token.first == 0){
            sum = token.second;
        }else if(token.first == 1){
            sum += get_token().second;
        }else if(token.first == 2){
            sum -= get_token().second;
        }else if(token.first == 3){
            sum *= advanced ? eval(tokens,pos,advanced) : get_token().second; // push on mult in advanced mode
        }else if(token.first == 4){
            sum /= get_token().second;
        }
    }

    return sum;
}

long long eval(const std::string& expr, bool advanced){
    std::regex expr_regex("[0-9]?([0-9]*[.])?[0-9]+|[\\-\\+\\\\\\(\\)\\/\\*]"); 

    std::vector<std::string> tokens;
    for (auto i = std::sregex_iterator(expr.begin(), expr.end(), expr_regex); i != std::sregex_iterator(); ++i) {
        tokens.push_back(i->str());
    }

    int pos = 0;
    return eval(tokens,pos,advanced);
}


void main()
{   
    auto input = parse_input("../src/day18/day18_input.txt");

    std::cout << "part1: " << std::accumulate(input.begin(), input.end(), 0LL, [&](auto& a,auto& expr){ return a + eval(expr, false); }) << std::endl;
    std::cout << "part2: " << std::accumulate(input.begin(), input.end(), 0LL, [&](auto& a,auto& expr){ return a + eval(expr, true); }) << std::endl;
}
