#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <chrono>

struct timer{
    using timer_t = std::chrono::steady_clock;

    timer() 
        : s_(timer_t::now()) {}

    ~timer(){
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(timer_t::now() - s_).count() << "ms" << std::endl;
    }

    timer_t::time_point s_;
};

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

        auto cycle = [&]()
        {
            std::swap(dst_volume, src_volume);

            #pragma omp parallel for
            for (int w=1; w<duration-1; ++w) {
                auto* wsrc_ptr = src_volume.data() + w*w_offset;
                auto* wdst_ptr = dst_volume.data() + w*w_offset;
                for (int z=1; z<depth-1; ++z) {
                    auto* zsrc_ptr = wsrc_ptr + z*z_offset;
                    auto* zdst_ptr = wdst_ptr + z*z_offset;
                    for (int y=1; y<height-1; ++y) {
                        auto* ysrc_ptr = zsrc_ptr + y*width + 1;
                        auto* ydst_ptr = zdst_ptr + y*width + 1;
                        for (int x=1; x<width-1; ++x, ++ysrc_ptr, ++ydst_ptr) {

                            int neighbours_active = 0;
                            for(int w2=w-1; w2<=w+1; ++w2){
                                auto* wneigh_ptr = src_volume.data() + w2*w_offset;
                                for(int z2=z-1; z2<=z+1; ++z2){
                                    auto* zneigh_ptr = wneigh_ptr + z2*z_offset;
                                    for(int y2=y-1; y2<=y+1; ++y2){
                                        auto* yneigh_ptr = zneigh_ptr + y2*width + x - 1;
                                        for(int x2=x-1; x2<=x+1; ++x2, ++yneigh_ptr){
                                            neighbours_active += *yneigh_ptr;
                                        }
                                    }
                                }
                            }
                            neighbours_active -= *ysrc_ptr; // remove x,y,z from neighbors rather than checking in loop, faster

                            if (*ysrc_ptr) {
                                *ydst_ptr = (neighbours_active == 2 || neighbours_active == 3);
                            }else {
                                *ydst_ptr = (neighbours_active == 3);
                            }

                        }
                    }
                }
            }
        };

        auto count = [&] {
            int active = 0;
            for (int w=1; w<duration-1; ++w) {
                auto* wdst_ptr = dst_volume.data() + w*w_offset;
                for (int z=1; z<depth-1; ++z) {
                    auto* zdst_ptr = wdst_ptr + z*z_offset;
                    for (int y=1; y<height-1; ++y) {
                        auto* ydst_ptr = zdst_ptr + y*width + 1;
                        for (int x=1; x<width-1; ++x, ++ydst_ptr) {
                            active += *ydst_ptr;
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

    {
        timer t;
        std::cout << "part2: " << cubes_active(4) << std::endl;
    }

}
