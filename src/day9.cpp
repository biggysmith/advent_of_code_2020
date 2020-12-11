#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

std::vector<size_t> parse_list(const std::string& file){
    std::vector<size_t> prog;

    std::ifstream file_stream(file);
    if(!file_stream){
        std::cout << "cannot open file" << std::endl;
        return prog;
    }

    std::string line;
    while (std::getline(file_stream, line)) {
        prog.push_back(std::stoull(line));
    }

    return prog;
}

void main()
{
    auto numbers = parse_list("../src/day9_input.txt");

    int preamble = 25;

    for(int i=preamble; i<numbers.size(); ++i)
    {
        int n = 2;
        std::vector<size_t> sub(numbers.begin()+i-preamble,numbers.begin()+i);
        std::vector<size_t> indexes(sub.size(), 0);
        std::fill(indexes.begin(), indexes.begin()+n, 1);

        bool found = false;

        do {
            int j = 0;
            std::vector<size_t> set(n);
            for (int k = 0; k < sub.size() && j<n; ++k) {
                if (indexes[k]) {
                    set[j++] = sub[k];
                }
            }

            if(set[0] != set[1]){
                if(set[0] + set[1] == numbers[i]){
                    found = true;
                    break;
                }
            }
        } while (std::prev_permutation(indexes.begin(), indexes.end()));

        if(!found){
            std::cout << "found the bam: " << numbers[i] << std::endl;
        }
    }
}