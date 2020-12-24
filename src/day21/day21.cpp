#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <fstream>
#include <sstream>
#include <cassert>
#include <random>
#include <chrono>
#include <regex>

struct food_t{
    std::vector<std::string> ingredients;
    std::vector<std::string> allergens;
};

std::vector<food_t> parse_input(const std::string& file){
    std::vector<food_t> input;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){

        std::regex re("[^\\s:(),]+");
        std::sregex_token_iterator first{line.begin(), line.end(), re}, last;
        std::vector<std::string> tokens{first, last};

        bool parsing_ingredients = true;
        input.push_back(food_t());
        for(auto& token : tokens){
            if(token == "contains"){
                parsing_ingredients = false;
                continue;
            }
            if(parsing_ingredients){
                input.back().ingredients.push_back(token);
            }else{
                input.back().allergens.push_back(token);
            }
        }

        std::sort(input.back().ingredients.begin(),input.back().ingredients.end());
    }

    return input;
}



void main()
{
    auto foods = parse_input("../src/day21/day21_input.txt");

    std::vector<std::string> all_ingredients;
    for(auto& food : foods){
        for(auto& ingredient : food.ingredients){
            all_ingredients.push_back(ingredient);
        }
    }

    std::set<std::string> all_allergens;
    for(auto& food : foods){
        for(auto& allergen : food.allergens){
            all_allergens.insert(allergen);
        }
    }

    std::map<std::string, std::vector<food_t>> allergen_to_foods;
    for(auto& food : foods){
        for(auto& allegern : food.allergens){
            bool food_has_allegern = std::find(food.allergens.begin(),food.allergens.end(),allegern) != food.allergens.end();
            if(food_has_allegern){
                allergen_to_foods[allegern].push_back(food);
            }
        }
    }

    std::map<std::string, std::set<std::string>> allergen_to_ingredients;
    for(auto& food : foods){
        for(auto& allegern : food.allergens){

            auto ingredients = food.ingredients;

            for(auto& food_that_has_allegern : allergen_to_foods[allegern]){
                std::vector<std::string> intersection;
                std::set_intersection(ingredients.begin(), ingredients.end(), food_that_has_allegern.ingredients.begin(), food_that_has_allegern.ingredients.end(), std::back_inserter(intersection));
                std::swap(ingredients, intersection);
            }

            for(auto& ingredient : ingredients){
                allergen_to_ingredients[allegern].insert(ingredient);
            }

        }
    }

    std::vector<bool> processed_allergen(allergen_to_ingredients.size(),0);
    auto remove_ingredient = [&](const std::string& ingredient){
        auto it = allergen_to_ingredients.begin();
        for(int r=0; r<processed_allergen.size(); ++r, ++it){
            if(!processed_allergen[r]){
                it->second.erase(ingredient);
            }
        }
    };

    auto update = [&]{
        auto it = allergen_to_ingredients.begin();
        for(int c=0; c<processed_allergen.size(); ++c, ++it){
            if(!processed_allergen[c] && it->second.size()==1){
                processed_allergen[c] = true;
                remove_ingredient(*it->second.begin());
                return;
            }
        }
    };

    auto all_allergens_identified = [&]{
        return std::all_of(allergen_to_ingredients.begin(),allergen_to_ingredients.end(),[](auto& s){ 
            return s.second.size() == 1; 
        });
    };

    while(!all_allergens_identified()){
        update();
    }

    int possible_allegerns = 0;
    for(auto& ingredient : all_ingredients){
        for(auto& [ignore,ingredients] : allergen_to_ingredients){
            if(*ingredients.begin() == ingredient){
                possible_allegerns++;
                break;
            }
        }
    }

    std::cout << "part1: " << all_ingredients.size() - possible_allegerns << std::endl;


    int i = 0;
    std::string part2;
    for(auto& [allegern,ingredient] : allergen_to_ingredients){
        part2 += (i++  ? "," : "") + *ingredient.begin();
    }

    std::cout << "part2: " << part2 << std::endl;

}

