#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

std::vector<size_t> parse_list(const std::string& file){
    std::vector<size_t> numbers;

    std::ifstream file_stream(file);
    if(!file_stream){
        std::cout << "cannot open file" << std::endl;
        return numbers;
    }

    std::string line;
    while (std::getline(file_stream, line)) {
        numbers.push_back(std::stoull(line));
    }

    return numbers;
}

void main()
{
    // part 1
    {
        auto numbers = parse_list("../src/day10/day10_input.txt");

        numbers.push_back(0); // charger outlet
        std::sort(numbers.begin(), numbers.end());
        numbers.push_back(numbers.back()+3); // built-in adapter

        std::vector<int> diff(4, 0);
        for (int n=1; n<numbers.size(); ++n) {
            diff[numbers[n]-numbers[n-1]]++;
        }

        std::cout << "1 jolt * 3 jolt: " << diff[1] << " * " << diff[3] << " = " << diff[1] * diff[3] << std::endl;
    }

    // part 2
    {
        auto numbers = parse_list("../src/day10/day10_input.txt");

        numbers.push_back(0); // charger outlet
        std::sort(numbers.begin(), numbers.end());
        numbers.push_back(numbers.back()+3); // built-in adapter

        std::vector<size_t> links(numbers.size(),0);
        links[0] = 1;

        // calculate number from links from one level to possible upper numbers, store, then repeat for next level
        // last level will have accumulated valid paths
        for(int i=0; i<links.size(); ++i){
            for(int j=i; j<links.size(); ++j){
                if(i!=j && numbers[j]-numbers[i] < 4){ // number with valid reach of upper numbers
                    links[j] += links[i];
                }
            }
        }

        int i = 0;
        std::cout << std::endl;
        for(auto l : links){
            std::cout << i++ << " : " << l << std::endl;
        }
    }

}