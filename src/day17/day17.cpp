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

        int xdim = (int)input[0].size();
        int ydim = (int)input.size();
        int width = 7 + xdim + 7;
        int height = 7 + ydim + 7;
        int depth = 7 + 1 + 7;
        int duration = 7 + 1 + 7;

        int w_offset = depth*height*width;
        int z_offset = height*width;

        std::vector<char> src_volume(width*height*depth*duration, 0);

        auto lookup = [&](std::vector<char>& volume, int x, int y, int z, int w) -> auto& {
            return volume[w*w_offset + z*z_offset + y*width + x];
        };

        int w_begin = duration/2;
        int z_begin = depth/2;
        int y_begin = height/2 - ydim/2;
        int x_begin = width/2 - xdim/2;

        for (int y=0; y<input.size(); ++y) {
            for (int x=0; x<input.front().size(); ++x) {
                lookup(src_volume, x_begin + x, y_begin + y, z_begin, w_begin) = input[y][x] == '#' ? 1 : 0;
            }
        }

        std::vector<char> dst_volume = src_volume;

        int w_start = dimensionality!=3 ? w_begin - 1 : w_begin;
        int z_start = z_begin - 1;
        int y_start = y_begin - 1;
        int x_start = x_begin - 1;

        int w_end =  dimensionality!=3 ? w_begin + 2 : w_begin + 1;
        int z_end = z_begin + 2;
        int y_end = y_begin + ydim + 1;
        int x_end = x_begin + xdim + 1;

        auto cycle = [&]()
        {
            std::swap(dst_volume, src_volume);

            int iz = z_end-z_start;
            int iw = w_end-w_start;
            int iwz = iw*iz;

            #pragma omp parallel for
            for (int i=0; i<iwz; ++i) { // maximize parallelism
                int w = w_start + i / iz;
                int z = z_start + i % iz;
                auto* zsrc_ptr = src_volume.data() + w*w_offset + z*z_offset;
                auto* zdst_ptr = dst_volume.data() + w*w_offset + z*z_offset;
                for (int y=y_start; y<y_end; ++y) {
                    auto* ysrc_ptr = zsrc_ptr + y*width + x_start;
                    auto* ydst_ptr = zdst_ptr + y*width + x_start;
                    for (int x=x_start; x<x_end; ++x, ++ysrc_ptr, ++ydst_ptr) {

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

            if(dimensionality!=3)   w_start--;
            z_start--;
            y_start--;
            x_start--;

            if(dimensionality!=3)   w_end++;
            z_end++;
            y_end++;
            x_end++;
        };

        auto count = [&] {
            int active = 0;
            for (int w=w_start; w<w_end; ++w) {
                auto* wdst_ptr = dst_volume.data() + w*w_offset;
                for (int z=z_start; z<z_end; ++z) {
                    auto* zdst_ptr = wdst_ptr + z*z_offset;
                    for (int y=y_start; y<y_end; ++y) {
                        auto* ydst_ptr = zdst_ptr + y*width + x_start;
                        for (int x=x_start; x<x_end; ++x, ++ydst_ptr) {
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
