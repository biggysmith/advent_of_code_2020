#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>


std::vector<std::string> parse_input(const std::string& file){
    std::vector<std::string> input;

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){
        input.push_back(line);
    }

    return input;
}

void main()
{
    auto input = parse_input("../src/day17/day17_input.txt");

    for(auto& s : input){
        std::cout << s << std::endl;
    }

    int width = 100;
    int height = 100;
    int depth = 100;

    std::vector<int> src_volume(width*height*depth,0);

    auto lookup = [&](std::vector<int>& volume,int x,int y,int z) -> int&{
        return volume[(z*height*width)+(y*width)+x];
    };

    for(int y=0; y<input.size(); ++y){
        for(int x=0; x<input.front().size(); ++x){
            lookup(src_volume,width/2+x,height/2+y,depth/2) = input[y][x] == '#' ? 1 : 0;
            //std::cout << lookup(src_volume,width/2+x,height/2+y,depth/2) << "";
        }
        //std::cout << std::endl;
    }

    std::vector<int> dst_volume(src_volume.size(),0);

    auto cycle = [&]
    {
        for(int z=1; z<depth-1; ++z){
            for(int y=1; y<height-1; ++y){
                for(int x=1; x<width-1; ++x){

                    int count = 0;
                    int neighbours_active = 0;
                    for(int z2=z-1; z2<=z+1; ++z2){
                        for(int y2=y-1; y2<=y+1; ++y2){
                            for(int x2=x-1; x2<=x+1; ++x2){
                                if(std::tie(x2,y2,z2) != std::tie(x,y,z)){
                                    neighbours_active += lookup(src_volume,x2,y2,z2);
                                }
                            }
                        }
                    }

                    if(lookup(src_volume,x,y,z) == 1){
                        lookup(dst_volume,x,y,z) = (neighbours_active==2 || neighbours_active==3) ? 1 : 0;
                    }else{
                        lookup(dst_volume,x,y,z) = (neighbours_active==3) ? 1 : 0;
                    }

                }
            }
        }

    };

    auto count = [&]{
        int active = 0;
        for(int z=1; z<depth-1; ++z){
            for(int y=1; y<height-1; ++y){
                for(int x=1; x<width-1; ++x){
                    active += lookup(dst_volume,x,y,z);
                }
            }
        }
        return active;
    };

    for(int i=0; i<6; ++i){
        cycle();
        std::cout << count() << std::endl;
        std::swap(dst_volume,src_volume);
    }

}
