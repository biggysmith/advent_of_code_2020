#include <vector>
#include <iostream>
#include <unordered_map>

struct record{
    int last;
    int second_last;
};

void main()
{
    std::vector<int> numbers{ 8,11,0,19,1,2 };

    auto nth_spoken_word = [&](int n)
    {
        std::unordered_map<int,record> number_map;
        for(int i=0; i<numbers.size(); ++i){
            number_map[numbers[i]] = {i+1,-1};
        }

        int spoken_number = numbers.back();
        for(int i=(int)numbers.size(); i<n; ++i){
            spoken_number = number_map[spoken_number].second_last == -1 ? 0 : number_map[spoken_number].last - number_map[spoken_number].second_last;
            number_map[spoken_number] = { i+1, number_map.find(spoken_number) != number_map.end() ? number_map[spoken_number].last : -1 };
        }

        return spoken_number;
    };

    std::cout << "2020th spoken number: " << nth_spoken_word(2020) << std::endl;
    std::cout << "30000000th spoken number: " << nth_spoken_word(30000000) << std::endl;
}