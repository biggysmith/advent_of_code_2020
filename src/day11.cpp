#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>

std::vector<std::string> parse_grid(const std::string& file){
    std::vector<std::string> grid_lines;

    std::ifstream file_stream(file);
    if(!file_stream){
        std::cout << "cannot open file" << std::endl;
        return grid_lines;
    }

    std::string line;
    while (std::getline(file_stream, line)) {
        grid_lines.push_back(line);
    }

    return grid_lines;
}

bool valid_coord(int x,int y,size_t width,size_t height){
    return x>=0 && y>=0 && x<width && y<height;
}

bool empty_seat(char seat){
    return seat == 'L';
}

bool occupied_seat(char seat){
    return seat == '#';
}

bool occupied_seat(int x,int y,int dx,int dy,const std::vector<std::string>& grid,bool line_of_sight){
    x += dx;
    y += dy;
    if(line_of_sight){
        while(valid_coord(x,y,grid[0].size(),grid.size())){
            if(occupied_seat(grid[y][x])){
                return true;
            }
            if(empty_seat(grid[y][x])){
                return false;
            }
            x += dx;
            y += dy;
        };

        return false;
    }else{
        return valid_coord(x,y,grid[0].size(),grid.size()) && occupied_seat(grid[y][x]);
    }
}

bool no_adjacent_occupied(int x,int y,const std::vector<std::string>& grid,bool line_of_sight){
    return !occupied_seat(x,y,-1,-1,grid,line_of_sight) &&
           !occupied_seat(x,y, 0,-1,grid,line_of_sight) &&
           !occupied_seat(x,y,+1,-1,grid,line_of_sight) &&
           !occupied_seat(x,y,-1, 0,grid,line_of_sight) &&
           !occupied_seat(x,y,+1, 0,grid,line_of_sight) &&
           !occupied_seat(x,y,-1,+1,grid,line_of_sight) &&
           !occupied_seat(x,y, 0,+1,grid,line_of_sight) &&
           !occupied_seat(x,y,+1,+1,grid,line_of_sight);
}


bool gte_adjacent_occupied(int x,int y,const std::vector<std::string>& grid,bool line_of_sight,int n){
    int occupied = occupied_seat(x,y,-1,-1,grid,line_of_sight) +
                   occupied_seat(x,y, 0,-1,grid,line_of_sight) +
                   occupied_seat(x,y,+1,-1,grid,line_of_sight) +
                   occupied_seat(x,y,-1, 0,grid,line_of_sight) +
                   occupied_seat(x,y,+1, 0,grid,line_of_sight) +
                   occupied_seat(x,y,-1,+1,grid,line_of_sight) +
                   occupied_seat(x,y, 0,+1,grid,line_of_sight) +
                   occupied_seat(x,y,+1,+1,grid,line_of_sight);

    return occupied >= n;
}

void update_seat(int x,int y,std::vector<std::string>& dst_grid,const std::vector<std::string>& src_grid,bool line_of_sight,int n){
    const char src_seat = src_grid[y][x];
    if(empty_seat(src_seat)){
        if(no_adjacent_occupied(x,y,src_grid,line_of_sight)){
            dst_grid[y][x] = '#';
        }
    }else if(occupied_seat(src_seat)){
        if(gte_adjacent_occupied(x,y,src_grid,line_of_sight,n)){
            dst_grid[y][x] = 'L';
        }
    }
}

bool compare_grid(const std::vector<std::string>& grida,const std::vector<std::string>& gridb){
    for(int y=0; y<grida.size(); ++y){
        for(int x=0; x<grida[0].size(); ++x){
            if(grida[y][x] != gridb[y][x]){
                return false;
            }
        }
    }
    return true;
}

void print_grid(const std::vector<std::string>& grid){
    for(auto& line : grid){
        std::cout << line << std::endl;
     }
     std::cout << std::endl;
}

bool update_grid(std::vector<std::string>& src_grid,bool line_of_sight,int n){
    std::vector<std::string> dst_grid = src_grid;
    for(int y=0; y<src_grid.size(); ++y){
        for(int x=0; x<src_grid[0].size(); ++x){
            update_seat(x,y,dst_grid,src_grid,line_of_sight,n);
        }
    }
    std::swap(dst_grid,src_grid);
    return compare_grid(dst_grid,src_grid);
}

int num_occupied_seats(const std::vector<std::string>& grid){
    int sum = 0;
    for(int y=0; y<grid.size(); ++y){
        for(int x=0; x<grid[0].size(); ++x){
            sum += grid[y][x] == '#';
        }
    }
    return sum;
}

void main()
{
     // part 1
     {
         auto grid = parse_grid("../src/day11_input.txt");
         while (!update_grid(grid,false,4)) {}
         std::cout << num_occupied_seats(grid) << std::endl;
     }

     // part 2
     {
         auto grid = parse_grid("../src/day11_input.txt");
         while (!update_grid(grid,true,5)) {}
         std::cout << num_occupied_seats(grid) << std::endl;
     }

}