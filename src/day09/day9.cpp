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
    auto numbers = parse_list("../src/day09/day9_input.txt");

    int number_pos;
    size_t dodgy_number;
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
            number_pos = i;
            dodgy_number = numbers[i];
            std::cout << "found the dodgy number: " << dodgy_number << std::endl;
        }
    }


    for(int i=2; i<number_pos; ++i){
        int num_seqs = number_pos-(i-i);
        for(int j=0; j<num_seqs; ++j){
            size_t sum = std::accumulate(numbers.begin()+j,numbers.begin()+j+i,0ULL);
            if(sum == dodgy_number){
                size_t mn = std::numeric_limits<size_t>::max();
                size_t mx = std::numeric_limits<size_t>::min();
                for(auto it=numbers.begin()+j; it!=numbers.begin()+j+i; ++it){
                    mn = std::min(mn, *it);
                    mx = std::max(mx, *it);
                    std::cout << *it << " ";
                }
                std::cout << "= " << sum << std::endl;
                std::cout << "min + max: " << mn  << " + " << mx << " = " << mn+mx << std::endl;
            }
        }
    }

}