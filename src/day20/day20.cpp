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


struct tile_t{
    size_t id;
    std::vector<char> data;
};

std::map<size_t,tile_t> parse_input(const std::string& file){
    std::map<size_t,tile_t> input;

    int id;
    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){

        if(line.find("Tile ") != std::string::npos){
            id = std::stoi(line.substr(line.find(" ")+1,line.find(":")-line.find(" ")-1));
            input[id].id = id;
        }else if(line != ""){
            std::copy(line.begin(), line.end(), std::back_inserter(input[id].data));
        }
    }
    return input;
}


std::vector<char> rotate(const std::vector<char>& src, int width) {
    std::vector<char> dst(src.size());

    for(int y=0; y<width; ++y){
        for(int x=0; x<width; ++x){
            dst[y*width+x] = src[(width-x-1)*width+y]; 
        }
    }

    return dst;
};

std::vector<char> flip(const std::vector<char>& src, int width){
    std::vector<char> dst(src.size());

    for(int y=0; y<width; ++y){
        for(int x=0; x<width; ++x){
            dst[y*width+x] = src[(width-y-1)*width+x];
        }
    }

    return dst;
};

std::string get_edge(const std::vector<char>& tile_data,int e){ 
    std::string ret(10,0);
    if(e==0){
        for(int i=0; i<10; ++i){
            ret[i] = tile_data[i];
        }
    }else if(e==1){
        for(int i=0; i<10; ++i){
            ret[i] = tile_data[i*10+9];
        }
    }else if(e==2){
        for(int i=0; i<10; ++i){
            ret[i] = tile_data[10*9+i];
        }
    }else if(e==3){
        for(int i=0; i<10; ++i){
            ret[i] = tile_data[i*10];
        }
    }

    return ret;
}


using grid_t = std::vector<tile_t>;

void find_grid(const std::map<size_t,tile_t>& tiles,grid_t& grid,int grid_width){
    if(grid.size() == tiles.size()){
        return;
    }
     
    for(auto& [id,tile] : tiles)
    {
        bool tile_in_grid = std::find_if(grid.begin(), grid.end(), [&](auto& a){ return a.id == tile.id; }) != grid.end();

        if(!tile_in_grid){ 
            auto curr_tile = tile;

            for(int f=0; f<2; ++f) // flips
            {
                for (int r=0; r<4; ++r) // rotations
                {
                    size_t grid_idx = grid.size();
                    size_t gx = grid_idx % grid_width;
                    size_t gy = grid_idx / grid_width;

                    bool edge_match = true;
                    if(gy > 0)  edge_match &= get_edge(curr_tile.data, 0) == get_edge(grid[(gy-1)*grid_width+gx].data, 2); // match above
                    if(gx > 0)  edge_match &= get_edge(curr_tile.data, 3) == get_edge(grid[gy*grid_width+(gx-1)].data, 1); // match left

                    if(edge_match){
                        grid.push_back(curr_tile);
                        find_grid(tiles, grid, grid_width);
                        if(grid.size() == tiles.size()){
                            return;
                        }
                        grid.pop_back();
                    };

                    curr_tile.data = rotate(curr_tile.data,10);
                }

                curr_tile.data = flip(curr_tile.data,10);
            }

        }
    }

}

std::vector<char> fill_image(const grid_t& grid,int grid_width){
    int tile_width = 10;
    int new_tile_width = tile_width - 2;
    std::vector<char> image(grid.size()*new_tile_width*new_tile_width);

    int x_start = 1; int x_end = 9; int y_start = 1; int y_end = 9;

    int stride = new_tile_width*grid_width;
    for(int gy=0; gy<grid_width; ++gy){
        for(int gx=0; gx<grid_width; ++gx){
            
            auto y_src = grid[gy*grid_width+gx].data.begin() + y_start*tile_width + x_start;
            auto y_dst = image.begin() + (gy*new_tile_width)*stride+(gx*new_tile_width);

            for(int y=y_start; y<y_end; ++y, y_src+=tile_width, y_dst+=stride){
                auto src = y_src;
                auto dst = y_dst;

                for(int x=x_start; x<x_end; ++x, ++src, ++dst){
                    *dst = *src;
                }   
            }

        }
    }

    return image;
}


std::string nessie_str = "                  # #    ##    ##    ### #  #  #  #  #  #   ";

int find_any_nessies(const std::vector<char>& image,int grid_width){
    int width = (int)nessie_str.size()/3;
    int stride = 8*grid_width;

    int num_nessies = 0;
    for(int y=0; y<stride-3; ++y){
        for(int x=0; x<stride-width; ++x){
            std::string sub_image_str;
            sub_image_str.append(image.data()+y*stride+x, width);
            sub_image_str.append(image.data()+(y+1)*stride+x, width);
            sub_image_str.append(image.data()+(y+2)*stride+x, width);

            num_nessies += std::equal(nessie_str.begin(),nessie_str.end(),sub_image_str.begin(),[](char a,char b){
                if(a == ' '){
                    return true; // only care about #'s
                }
                return (a == '#' && b == '#');
            });
        }
    }

    return num_nessies;
}

void main()
{
    auto tiles = parse_input("../src/day20/day20_input.txt");
    int width = (int)sqrt(tiles.size());

    // part 1
    grid_t grid;
    find_grid(tiles, grid, width);

    auto grid_val = [&](int x,int y){
        return grid[y*width+x].id;
    };

    std::cout << "part1: " << grid_val(0,0) * grid_val(width-1,0) * grid_val(width-1,width-1) * grid_val(0,width-1) << std::endl;

    // part 2
    auto image = fill_image(grid, width);

    for(int f=0; f<2; ++f) // flips
    {
        for(int r=0; r<4; ++r) // rotates
        {
            int num_nessies = find_any_nessies(image,width);
            if(num_nessies){
                size_t water_roughness = std::count(image.begin(),image.end(),'#') - num_nessies * std::count(nessie_str.begin(),nessie_str.end(),'#');
                std::cout << "part2: " << water_roughness << std::endl;
                return;
            }
        
            image = rotate(image, width*8);
        }

        image = flip(image, width*8);
    }
}

