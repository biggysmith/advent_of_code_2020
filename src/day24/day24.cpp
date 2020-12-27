#include <algorithm>
#include <functional>
#include <stack>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

std::vector<std::vector<std::string>> parse_input(const std::string& file){
    std::vector<std::vector<std::string>> input;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){
        std::regex re("w|e|nw|ne|sw|se");
        std::sregex_token_iterator first{line.begin(), line.end(), re}, last;
        std::vector<std::string> tokens{first, last};
        input.push_back({first, last});
    }

    return input;
}


int main() 
{
    auto directions = parse_input("../src/day24/day24_input.txt");

    int width = 140;
    int height = 140;

    std::vector<int> floor(width*height, 1);
    std::vector<int> dst_floor(width*height);

    auto tile = [&](std::vector<int>& tiles, int x,int y) -> auto& {
        return tiles[y*width+x];
    };

    for(auto& direction : directions){
        int x = width/2;
        int y = height/2;

        for(auto& step : direction){
        
            if(step == "w"){
                x -= 1;
            }else if(step == "e"){
                x += 1;
            }else if(step == "nw"){
                x -= 1;
                y -= 1;
            }else if(step == "ne"){
                y -= 1;
            }else if(step == "sw"){
                y += 1;
            }else if(step == "se"){
                x += 1;
                y += 1;
            }

        }

        tile(floor,x,y) = tile(floor,x,y)==1 ? 0 : 1;
    }

    std::cout << "part1: " << std::count(floor.begin(), floor.end(), 0) << std::endl;


    auto process_day = [&]
    {
        std::copy(floor.begin(), floor.end(), dst_floor.begin());

        //#pragma omp parallel for
        for(int y=1; y<height-1; ++y){
            for(int x=1; x<width-1; ++x){
        
                int num_black_tiles = 
                    (tile(floor,x-1,y) == 0) +
                    (tile(floor,x+1,y) == 0) +
                    (tile(floor,x-1,y-1) == 0) +
                    (tile(floor,x,y-1) == 0) +
                    (tile(floor,x,y+1) == 0) +
                    (tile(floor,x+1,y+1) == 0);

                if(tile(floor,x,y) == 0 && (num_black_tiles==0 || num_black_tiles>2)){
                    tile(dst_floor,x,y) = 1;
                }
                
                if(tile(floor,x,y) == 1 && num_black_tiles==2){
                    tile(dst_floor,x,y) = 0;
                }

            }
        }

        std::swap(dst_floor, floor);
    };

    for(int d=0; d<100; ++d){
        process_day();
    }

    std::cout << "part2: " << std::count(floor.begin(), floor.end(), 0) << std::endl;
}



