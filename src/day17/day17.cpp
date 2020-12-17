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
    auto cubes_active = [](int dimensionality)
    {
        auto input = parse_input("../src/day17/day17_input.txt");

        int dims = 27;
        int width = dims;
        int height = dims;
        int depth = dims;
        int duration = dimensionality==3 ? 3 : dims;

        int w_offset = depth*height*width;
        int z_offset = height*width;

        std::vector<char> src_volume(width*height*depth*duration, 0);

        auto lookup = [&](std::vector<char>& volume, int x, int y, int z, int w) -> auto& {
            return volume[w*w_offset + z*z_offset + y*width + x];
        };

        for (int y=0; y<input.size(); ++y) {
            for (int x=0; x<input.front().size(); ++x) {
                lookup(src_volume, width/2 + x, height/2 + y, depth/2, duration/2) = input[y][x] == '#' ? 1 : 0;
            }
        }

        std::vector<char> dst_volume = src_volume;

        auto cycle = [&]
        {
            std::swap(dst_volume, src_volume);

            for (int w=1; w<duration-1; ++w) {
                for (int z=1; z<depth-1; ++z) {
                    for (int y=1; y<height-1; ++y) {
                        for (int x=1; x<width-1; ++x) {

                            int neighbours_active = 0;
                            for(int w2=w-1; w2<=w+1; ++w2){
                                for(int z2=z-1; z2<=z+1; ++z2){
                                    for(int y2=y-1; y2<=y+1; ++y2){
                                        for(int x2=x-1; x2<=x+1; ++x2){
                                            if (std::tie(x2, y2, z2, w2) != std::tie(x, y, z, w)) {
                                                neighbours_active += lookup(src_volume, x2, y2, z2, w2);
                                            }
                                        }
                                    }
                                }
                            }

                            if (lookup(src_volume, x, y, z, w)) {
                                lookup(dst_volume, x, y, z, w) = (neighbours_active == 2 || neighbours_active == 3);
                            }else {
                                lookup(dst_volume, x, y, z, w) = (neighbours_active == 3);
                            }

                        }
                    }
                }
            }
        };

        auto count = [&] {
            int active = 0;
            for (int w=1; w<duration-1; ++w) {
                for (int z=1; z<depth-1; ++z) {
                    for (int y=1; y<height-1; ++y) {
                        for (int x=1; x<width-1; ++x) {
                            active += lookup(dst_volume, x, y, z, w);
                        }
                    }
                }
            }
            return active;
        };

        for (int i=0; i<6; ++i) {
            cycle();
        }

        return count();
    };

    std::cout << "part1: " << cubes_active(3) << std::endl;
    std::cout << "part2: " << cubes_active(4) << std::endl;
}
