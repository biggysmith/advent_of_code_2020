#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>

struct ticket{
    std::string seat;
    unsigned int row;
    unsigned int col;
    unsigned int id;
};

ticket get_ticket(const std::string& seat){
    unsigned int row = 127;
    unsigned int n = 6;
    for(auto c : seat.substr(0,7)){
        if(c == 'F'){
            row &= ~(1U << n); // clear bit
        }
        n--;
    }

    unsigned int col = 7;
    n = 2;
    for(auto c : seat.substr(7,11)){
        if(c == 'L'){
            col &= ~(1U << n); // clear bit
        }
        n--;
    }

    return {seat, row, col, row*8 + col};
}

std::string bin_to_seat(unsigned int bin){
    std::string ret(10, ' ');
    for(int i=0; i<7; ++i){
        if((bin >> i) & 1U){ // check bit
            ret[i] = 'F';
        }else{
            ret[i] = 'B';       
        }
    }
    for(int i=7; i<10; ++i){
        if((bin >> i) & 1U){ // check bit
            ret[i] = 'L';
        }else{
            ret[i] = 'R';       
        }
    }
    return ret;
}

void print_ticket(const ticket& t){
    std::cout << t.seat << ": row:" << t.row << " col:" << t.col << " id:" << t.id << "\n";
}

void main()
{
    std::cout << get_ticket("FBFBBFFRLR").id << std::endl; 
    std::cout << get_ticket("BFFFBBFRRR").id << std::endl; 
    std::cout << get_ticket("FFFBBBFRRR").id << std::endl; 
    std::cout << get_ticket("BBFFBBFRLL").id << std::endl << std::endl;  

    std::vector<std::string> seats {
        "FBBFBFFRRL",
        "BBFFBFBRRR",
        "BFBBFFFLRR",
        "FFBFFFBLLR",
        "BFBBBBBRLR",
        "FBFFFBFLRL",
        "BFBBBBFLRR",
        "FFBBBFBRRL",
        "FBFBBFBLRL",
        "BBFFFFBRRR",
        "FBBBBBBRRR",
        "FFBBFFBLLL",
        "BBFFFFFRRR",
        "BFFBFBFRLL",
        "BFBFFFBRLR",
        "FBBBFFFLRL",
        "BFBFBBFLRL",
        "BFFFBBBRRR",
        "FBFFBBFRRL",
        "BBFBFFFLLR",
        "FBBFBBBRLL",
        "BBFFBFBRLR",
        "BFFFFFBRLL",
        "BBFFFBBRRR",
        "FBFFBBFRLL",
        "FBBBBBFRRL",
        "BBFBFFFLRL",
        "BFBFBBBRLR",
        "FBBFBBBRRR",
        "BFBBBFFLLL",
        "BFFFFFFLLL",
        "BFBFFFBLRL",
        "FBBFBBBLLR",
        "BFFFBFBRLL",
        "FFBFFBFLRL",
        "FBFBFFBRLR",
        "BBFFFBBLLR",
        "BFFBFFFRRR",
        "FBFFBBBLLL",
        "BFBFFFFRLL",
        "FBFBBFFRRL",
        "BFBFBBBLLL",
        "BFBFBFFRLR",
        "FBBFBFFLRL",
        "BFFFFBBLLR",
        "FBBBFBBRRR",
        "FBBBFFFLRR",
        "FFBBBBFLRR",
        "BFFFFFFRRL",
        "BBFFFFFLRL",
        "BFFBFBFRLR",
        "FFBBBBBLLR",
        "FBFFBFBRLL",
        "BFBBFFBLRR",
        "BFFFFBFLLR",
        "FBBBBFFRLL",
        "FBBBFFBLLR",
        "BFFBBBFLLL",
        "FFBFBBBLLL",
        "BBFBFFFLRR",
        "FBFBFFFLRL",
        "BFFBBFFRRL",
        "FBFBFBBLRR",
        "FFBBFBBRLL",
        "FFBBFBFRLL",
        "BFFFBFBRRL",
        "BFBBBBFRLL",
        "BFFFBFBLLL",
        "BFFFBBBLLL",
        "FBBBBFBRRL",
        "BFBBFFBRLL",
        "BFBBFFFRLR",
        "FFBBBBFLLL",
        "FFBBFFBRLL",
        "FFBFBFFLRR",
        "FBBBFBBRRL",
        "FFBFBBBLRR",
        "BFBFFFFRRR",
        "BFFBBFBRRR",
        "BFFFFBBRLL",
        "BFFFBBFRRR",
        "BFFFBFBRLR",
        "FFBBBFFRRR",
        "BFFBFBFRRL",
        "FFBBBBBRLR",
        "FBBFBFBRRL",
        "FFBBBBBLRL",
        "FFBBFBBRRR",
        "BFFBBBFLLR",
        "FFBFBFFRRR",
        "BFBBFFBRRL",
        "BFBBFBBLLR",
        "FBBBFFBRLR",
        "BFFBBFFLLR",
        "FBBFFBFRRR",
        "FFBFFFBLRR",
        "FFFBBBBRRL",
        "FBBFBFBLLR",
        "FBBBBFFRRR",
        "FFFBBBBLRL",
        "FBBBFFBRRL",
        "BFBBFBFLRL",
        "FBBFBBFRRL",
        "FBBFBBFRLR",
        "BBFFBBFRLL",
        "BBFFFFBLLR",
        "FFBFFBFLLL",
        "FFBBFFBRRL",
        "FBBFFFBLLL",
        "FFFBBBBLLR",
        "FBBBFFBLLL",
        "FFBFBBFLLR",
        "FBBFBBFLRL",
        "BBFFBBFRLR",
        "FBFBBBBRLR",
        "BFBFBFFRRL",
        "BFBBFBBLLL",
        "FBFBBBBRRL",
        "FFBFBFBRLL",
        "BFFBBBFRRL",
        "BFFBFFBRLR",
        "FBFBBFBLRR",
        "FFBBFFFLRL",
        "BBFFFBBRLR",
        "FFBBBFFLLR",
        "FBFFFBBRRR",
        "BFFBBFBRRL",
        "BFBBFFFRLL",
        "FBFBBFBRLR",
        "FBBBBFFLLL",
        "FFBBFBFLLR",
        "BFFBBBFRLR",
        "BFFFBBBRLL",
        "BFBFBFBLRL",
        "BFFFFFFRRR",
        "FBFBFBBRRL",
        "BFBFFBFRRL",
        "FBFFFFFLRR",
        "FFBBBBFRRL",
        "FFBBBBBRRR",
        "BFBFFBBRRL",
        "BBFFFBFLRL",
        "FBBBBFBRLR",
        "BFBFFBFRRR",
        "FFBBBFBRLL",
        "FFBFFBBLLL",
        "BFBBBFBLRL",
        "BFFBBBBLLR",
        "FFBFBBFRLL",
        "BFFFBBBLRR",
        "BBFBFFFRRL",
        "BBFFBFFRLL",
        "BFBBFBFRRR",
        "FFBFBFBLRL",
        "BFBBFFBLLR",
        "FBBFBFBRLR",
        "FFBBBFBRLR",
        "FBFBBBFLRL",
        "FBFBBFFLRR",
        "FBBBFBBRLR",
        "FBFBBBFRRL",
        "BFFBBFBLRR",
        "FFFBBFBLLL",
        "BFBFFBFLRL",
        "FBBBBFFLLR",
        "FBFFFFFRRR",
        "FBFBFBFLLL",
        "BFBBFFFRRR",
        "BFBBBFBLRR",
        "BFBBFBFRLR",
        "FFBFFBFRLL",
        "BFBFBBFRRR",
        "BFBFFBFRLL",
        "BBFFBBBLLR",
        "FBFFBFBRLR",
        "FBBBFBFLRL",
        "BBFFBBFLLR",
        "BFBBBFFLRR",
        "FBBBFFFLLL",
        "FFBBFBFRRL",
        "FBFFBBFLLR",
        "FFBFFBBLRL",
        "FFBFBFBLLR",
        "FFFBBFFLLL",
        "BFBBFBBRRL",
        "BFBFBFBRLL",
        "BFFBFFFRLR",
        "BFFFBBFLLR",
        "FBFFFFFLLR",
        "FBFFFFBLLR",
        "FFFBBBFLRL",
        "FFBBFBBLRL",
        "FFBFBBBRRL",
        "FBBFBFBRRR",
        "BFFFFFBLLL",
        "BFBFBBBLRL",
        "BFFFFFBRRR",
        "FFBFBFFRLL",
        "BFFBFFBLLR",
        "BFFBFFFLLL",
        "BFBBBFFRLR",
        "BFBBBBBLLR",
        "FBFBFBBRLR",
        "BFFFBBBRLR",
        "FFFBBBFRLL",
        "BFBBBBBLLL",
        "FBBFFBBLLR",
        "BFBFFBBLLL",
        "FBFBBBBRRR",
        "FFBBFFFLLR",
        "BFFBFFBLRR",
        "BFFFFBFLRR",
        "FFBFFFBLLL",
        "FFBFBBFRRL",
        "FBBFFFFLRR",
        "FBFBFBBRLL",
        "BFFBFBFLRR",
        "BFFBBFBRLR",
        "BFFBFBBLRR",
        "BFFFBBBLLR",
        "FBFBFFBRRL",
        "BFBBBFFRRR",
        "BFBFFBBRLR",
        "FBFFBBFLRR",
        "FFFBBFFRRR",
        "BBFFBFFLRL",
        "FBFBBFBRRR",
        "FBFFFFBRLR",
        "FFBFFFFRLL",
        "FBBBFFBLRL",
        "FBBBBBBLLR",
        "BFFFBFBRRR",
        "FBBBBBFLLR",
        "BFFBFBBLLL",
        "FBBBFBFRRR",
        "FBBBFBFLLR",
        "FFBFBFFLRL",
        "BFFFBFBLRR",
        "FFFBFBBRRR",
        "BFBFBBFRLL",
        "FFBFBBBRLR",
        "BFBFBFFLRL",
        "FFBBFFBRRR",
        "BFBBFBBRLL",
        "FBFBBBFLLL",
        "BFBFFBFRLR",
        "FBBFBFFRLR",
        "BFFFFFFRLL",
        "BFFFFFBLRL",
        "FBBFBBFRRR",
        "FBBFBBFRLL",
        "FBFBFFFRLR",
        "FFBFFBFLLR",
        "FBBBFFFLLR",
        "BFBBBBBLRR",
        "FBFBBFFLLL",
        "FFFBBBBLRR",
        "FBBBBBBLRL",
        "FFBFFBBLRR",
        "FBBFFFFRRR",
        "BFBFBBFRLR",
        "FFBFBBFLRL",
        "BFBBFFFLLL",
        "BFBBBBFRRL",
        "FBBBFBFRRL",
        "FBFFBBBRLL",
        "FFBBFFFRLL",
        "FBFBBBBLRR",
        "FFBBBBFRLR",
        "FBFBBFFLRL",
        "FFBBFFBRLR",
        "FBBBFBFLRR",
        "FBFFFBFRLR",
        "FFBBBFFLLL",
        "FBFFBBFLRL",
        "FFBFFBFLRR",
        "FBFFBFFLLR",
        "FFFBBFFLRR",
        "FBBFFBBRRL",
        "BFBBBFBRRR",
        "BBFFBBBRRR",
        "BFFFBBFLRL",
        "FBFBFFBLRL",
        "FBBFFBFLLL",
        "BFFBBBFRRR",
        "BFFFBFFRRL",
        "FBFFFBFRRR",
        "FFBBFFBLRL",
        "BBFFFFBRLR",
        "FBFBBFBLLR",
        "FFBFFBFRLR",
        "BFBBFBFRLL",
        "FFBBFBFRRR",
        "BBFFBFBLLL",
        "FBBFBBBLLL",
        "FBBFFBFLRL",
        "FBFFFBFRRL",
        "FBBBFBBLRR",
        "FBBFFFFRRL",
        "FBBBBBFLRR",
        "FFBBFFFLLL",
        "BFBBBFBRLL",
        "FBFFFFBRLL",
        "BFBFBBFLLR",
        "FFBBBFFLRL",
        "FBBFBBBRLR",
        "BFBFBFFLLR",
        "BFFBBFBRLL",
        "FFFBBFFRRL",
        "FFBFFFFLRR",
        "BFFFFBFRLR",
        "FBFFFBBLLL",
        "FFBFBFFRRL",
        "FBFFFBBLRR",
        "FBFFBFFRLR",
        "FBBFBBBRRL",
        "FBFFBFBRRL",
        "FBFFFBFLLL",
        "BFFBFFBRLL",
        "BFFBBFBLLL",
        "BFFFFBBRRR",
        "FBFFFFBLLL",
        "FBBFBFFLRR",
        "FFFBBBFRRR",
        "BBFFFFFLLL",
        "BFFBFBBLRL",
        "BBFFFBBLRR",
        "FBFFBFBLLL",
        "BFBFFFBLLL",
        "BBFFBBFRRR",
        "FFBBFBBRRL",
        "FBBBBBBRRL",
        "FBFFFBFLLR",
        "BBFBFFFLLL",
        "BFFBBBBRRR",
        "FBBFFBBRRR",
        "FBBBBFFRLR",
        "FBBFBBFLRR",
        "FBBFFFFRLR",
        "BFBBBBFRLR",
        "FBFBFFBRLL",
        "BFFBFFFLLR",
        "FBFFBFBLLR",
        "FFFBBBFRLR",
        "FBBBFFBRRR",
        "BFFBBBBLRL",
        "BFFFFBBLLL",
        "BFFBBFFLRR",
        "BFFBFFFLRL",
        "FBBFBBBLRR",
        "FFFBBFBLRR",
        "FFBBBFBLRR",
        "FBFFFBBLRL",
        "FBFFBFFRRL",
        "FFBFBFFLLL",
        "FFBBBBBLRR",
        "FFBBFBFLLL",
        "FBFBFBFRLL",
        "BFFBBBFLRR",
        "FFBFBFBRRR",
        "FBBFFFBLRL",
        "FBBBFFBLRR",
        "BFBBBBFLRL",
        "BFBBFBFRRL",
        "FFBBBFFRLL",
        "BBFFFFFRLL",
        "BBFFFBBRRL",
        "FBBBFBBLLR",
        "FBBBBBBLRR",
        "FFBBFBFRLR",
        "FFBFFBFRRL",
        "FBBBBBFLRL",
        "BFBFBFBRRR",
        "BBFFBBFLLL",
        "BFFFBBFRLL",
        "FBFBBBBLRL",
        "BFFFBFFLRL",
        "FBBBFFFRRR",
        "BFFFFBFLLL",
        "BFFBBBFRLL",
        "FBFFFBBRLL",
        "FBFBFFBLLL",
        "FBBBBFBLRL",
        "FBBFBFFRRR",
        "FFFBBBBLLL",
        "FFBFBFBRLR",
        "BFBFBFBRRL",
        "BFBFBBBLRR",
        "FBFFFFFRLL",
        "BFBBBBBRRL",
        "FBBFFFFLLR",
        "FBBBBFBLLR",
        "FBBFFFFLRL",
        "FBBFBFBLLL",
        "BFFFFBBLRR",
        "FBBBBFFLRR",
        "BBFFFBFRRR",
        "FBFBBBFRLL",
        "BFFFFFBRRL",
        "BFFFFFFLRR",
        "FFBFFFBRLL",
        "FBFFBFFLLL",
        "BFBBFFBRRR",
        "BFBBFBFLRR",
        "BFBBFFBLLL",
        "FBBFFBFRLL",
        "BFBFBBFLRR",
        "FFBFFFFRLR",
        "FBFBBFBRLL",
        "FBFFBBBLRR",
        "FBBFBFBLRL",
        "FBFFBFBLRL",
        "FFBFFFFRRR",
        "BFFBBBBLLL",
        "BFFBFFFRRL",
        "BFBFBBBRRL",
        "BBFFFBFLLL",
        "FBBBFFBRLL",
        "BFFFFFFRLR",
        "FFFBBFBLRL",
        "BFBFBFBLLR",
        "FBFBFFFRRR",
        "FBFBFFBRRR",
        "BBFFFFBLRR",
        "BFBBBBFLLR",
        "FBFBFBFLRR",
        "FBBBBBFRLR",
        "BFFFBBFLRR",
        "BBFFBFBLRL",
        "BBFFFFFLRR",
        "FBFBFBFLLR",
        "FFFBBBBRRR",
        "BFFBBFFLLL",
        "FBBFBBBLRL",
        "BFFFBFFLRR",
        "BFBBBFBRLR",
        "FFBBFBBLLL",
        "BBFFBBBLLL",
        "BFFFBFBLLR",
        "FFBBBFBRRR",
        "BBFFFFFRLR",
        "FFBBBFFRRL",
        "FFBBFFBLLR",
        "FBBFBFFLLL",
        "FBBFFBBLLL",
        "BFFBFBBRLR",
        "FFBBFFFLRR",
        "BFFBFBBLLR",
        "FFBFFBBRRL",
        "FFBFBBBLLR",
        "BFFFBBFLLL",
        "FBBFFBFRLR",
        "BFFFBFFRRR",
        "FFFBBFFLLR",
        "FBFBBBFRRR",
        "BFFFFFBLRR",
        "FFBBFFFRRL",
        "FFBFBBBLRL",
        "FBBFFBFLRR",
        "BFFFFBBRLR",
        "FFBBBFBLLR",
        "FFFBBFBRLR",
        "BBFBFFFRLL",
        "FBFFBFFRLL",
        "FBBBBFBRLL",
        "BBFFFBBLRL",
        "BFFBFFFRLL",
        "FBFFFFFRRL",
        "BBFFBBBRLR",
        "BBFFFFFRRL",
        "BBFFBBBRLL",
        "BFFBFFBRRR",
        "BFBBFFFLLR",
        "BFFFBBFRLR",
        "FBBBFBFLLL",
        "BFBBFBBRLR",
        "FBBBFBBLLL",
        "BFBFBBBRLL",
        "BBFFFBFLLR",
        "BFBBFFFLRL",
        "FFBFBBFRRR",
        "FFBBBBBRRL",
        "BBFFBBFLRR",
        "FBFBBBFLRR",
        "FFBFFBBRRR",
        "FBBFFFBRLR",
        "BFBBBFFRRL",
        "FBFBFBFRLR",
        "FBBBBFBRRR",
        "FBBFFBBLRL",
        "BBFFFFBLRL",
        "FFFBBBBRLR",
        "FBFBBFFRLR",
        "BFBFFBBLLR",
        "BFFFFBBRRL",
        "BFBFFFBRLL",
        "FBFFBFBRRR",
        "FFBBFBBLLR",
        "BFFBBFFRRR",
        "FBFFFBBLLR",
        "FBFBBFBRRL",
        "FFBFFFFLLL",
        "BFFBBBBRLR",
        "BFFBBFBLRL",
        "BFFBFBBRRL",
        "FFBFFBBLLR",
        "FBBFFFBRRL",
        "BFBFFBBRLL",
        "FBFFFFBRRR",
        "BFFFFFFLLR",
        "FBFFBBFLLL",
        "FFFBBFBRLL",
        "BFBFFBFLLL",
        "BFBBFBBLRL",
        "BFFFBFFLLR",
        "FBFFFBBRRL",
        "BBFFFFBRLL",
        "FFBBBBBRLL",
        "FBFBFBFRRR",
        "BBFFBBFLRL",
        "FBBBBFBLLL",
        "BFBFBFFRRR",
        "FFBFBFFRLR",
        "BBFFBFBLRR",
        "BFBFFFFLRL",
        "BFFFBBFRRL",
        "FFBFBBBRRR",
        "FBFFFBFRLL",
        "BFFFFBFRRR",
        "BFBFBFFRLL",
        "FBBBFBFRLR",
        "BFFFFFBLLR",
        "BFBBBFBRRL",
        "BFFBBFFRLR",
        "FBBBFBBLRL",
        "BFFFBFFRLR",
        "BBFFFBFRLR",
        "BFFFBFFRLL",
        "FBBBBFFRRL",
        "BBFFBBFRRL",
        "BBFFBFFRRR",
        "BBFFBFFRRL",
        "FBBBBFBLRR",
        "BBFFFBBRLL",
        "FBBFBFBLRR",
        "BFFBBFFLRL",
        "BFBBBFBLLL",
        "BBFFBFBRLL",
        "FFBFFFBRLR",
        "BBFFBBBLRL",
        "FFBBFBBLRR",
        "FFBBBFBLLL",
        "BFFBFFFLRR",
        "FFBFBFFLLR",
        "FFBFFBBRLL",
        "BFBBBBBLRL",
        "BBFFFBFLRR",
        "BFBFBFFLRR",
        "BFFBFBFLLL",
        "FFBFFFFRRL",
        "FFBBBBFRLL",
        "FBFBFBBLRL",
        "BBFFFBFRRL",
        "FFBFFBFRRR",
        "FBBFFBBRLR",
        "FBBFBFBRLL",
        "BFBFBFBRLR",
        "BFFBFFBLRL",
        "BFBBFFBRLR",
        "FBFBFFFLLR",
        "BFFFFFFLRL",
        "FBBFBBFLLL",
        "FFBBBFBLRL",
        "BFBFBBFLLL",
        "BBFFFBFRLL",
        "FBFBFFBLRR",
        "FBBBFFFRLR",
        "BFBBBFFLRL",
        "FFBBFFBLRR",
        "BBFFBFFLLR",
        "FBFFBFFRRR",
        "FBFFBBBRLR",
        "BFBFBFBLRR",
        "BFFBBBBRLL",
        "FBFFFFBLRL",
        "FBBFBFFLLR",
        "FBFBFFFLRR",
        "FBBBBBBRLL",
        "FBFFBBBRRR",
        "FBBFFBBLRR",
        "BFFFBFBLRL",
        "FBBFFFFRLL",
        "BFBFFBBRRR",
        "BBFFBBBLRR",
        "BFBFFFBLLR",
        "FBFBFBBRRR",
        "FFFBBBFLLR",
        "BFBFFFFLLL",
        "FBFFBBBLRL",
        "FBFBFBBLLL",
        "FFBFFFFLRL",
        "FBFBBBBLLR",
        "FBFBFBFLRL",
        "FBBBFBFRLL",
        "FBFBFFFRRL",
        "BBFFBBBRRL",
        "BBFFFFBLLL",
        "FBFFBBBRRL",
        "BFBFFFBRRL",
        "BBFFFFBRRL",
        "BFBFFBBLRR",
        "BFFBFFBRRL",
        "FFBFBFBRRL",
        "FFFBBFBRRR",
        "BBFFFBBLLL",
        "FBFBBFFRLL",
        "BFFFBFFLLL",
        "BFFBFBFLRL",
        "FBBBBBFRLL",
        "FBFBBBFLLR",
        "FFBBFFFRRR",
        "FBBBBBBLLL",
        "BFBFBBFRRL",
        "FBFBFBFRRL",
        "BFBFFFFRLR",
        "FFFBBFFRLR",
        "FFBBBFFRLR",
        "FFFBBFBRRL",
        "FBFFFFFRLR",
        "FBFFBBFRLR",
        "FFBFFFBLRL",
        "BFBFFFFLRR",
        "FFBFFFFLLR",
        "FFBBFFFRLR",
        "BFBFFFBLRR",
        "FBBBBBFRRR",
        "BFFBBBBRRL",
        "FFFBBFFLRL",
        "FBFFBFBLRR",
        "FBBFFBFRRL",
        "FBBFBFFRLL",
        "FFBFBBBRLL",
        "BFFFBBBLRL",
        "BFFBFBBRRR",
        "FBBBBBBRLR",
        "BFBFBBBRRR",
        "BBFFBFFRLR",
        "FBBBFFFRRL",
        "FFBBBBFRRR",
        "BFBBBFBLLR",
        "FFFBBBFRRL",
        "FFFBBBBRLL",
        "FBBBFBBRLL",
        "BFFFFFBRLR",
        "BFBFBBBLLR",
        "BFBFFBBLRL",
        "FBBFFFBRRR",
        "BFBBFBBLRR",
        "FBBFFBFLLR",
        "FBFBBBBRLL",
        "BFFBBFFRLL",
        "FFBBFBBRLR",
        "BFBFFBFLLR",
        "BFBBBFFLLR",
        "FBBFBBFLLR",
        "BFBBFBFLLR",
        "BFFBFBFRRR",
        "BFBFBFBLLL",
        "FBFFFFFLLL",
        "FFBFFFBRRL",
        "FBFFBBFRRR",
        "BBFFBFBRRL",
        "FBFFBFFLRR",
        "FBFBBFFRRR",
        "BFFFBBBRRL",
        "BFBFBFFLLL",
        "BFBFFFFLLR",
        "FBBBBBFLLL",
        "FFBFFBBRLR",
        "FFBBBBBLLL",
        "BFFBBBFLRL",
        "FFBBFBFLRL",
        "FFFBBBFLLL",
        "BFFFFBFLRL",
        "FBBFFFBLLR",
        "FBFBBBFRLR",
        "BBFFBFBLLR",
        "BFBBBBFRRR",
        "FBFBFFFRLL",
        "FBFBBFBLLL",
        "FBFBFFFLLL",
        "FFBFBBFLLL",
        "BFBFFFFRRL",
        "FFFBBFBLLR",
        "BFFBBFBLLR",
        "FFBFBFBLLL",
        "FBFBBFFLLR",
        "FFBFBFBLRR",
        "BFFBFBFLLR",
        "BFBBBBBRRR",
        "FBBFFFBLRR",
        "FBBFFFFLLL",
        "FFBBFBFLRR",
        "BBFFFFFLLR",
        "BFBBFBFLLL",
        "BFFFFBBLRL",
        "FBFFFFBLRR",
        "FFBBBFFLRR",
        "FFFBBFFRLL",
        "BFFBBBBLRR",
        "FBFFBBBLLR",
        "FFBFFFBRRR",
        "FBFFFFFLRL",
        "BFFFFBFRRL",
        "BFFFFBFRLL",
        "BFBFFBFLRR",
        "BFBBBFFRLL",
        "BFBBFBBRRR",
        "BBFBFFFRLR",
        "BBFFBFFLRR",
        "FFBFBBFRLR",
        "BFBBBBFLLL",
        "FBFFFBBRLR",
        "BFBBBBBRLL",
        "BBFFBFFLLL",
        "FBFFBFFLRL",
        "FBFBFBBLLR",
        "BFFBFFBLLL",
        "FFBBBBFLRL",
        "FBFBFFBLLR",
        "FFFBBBFLRR",
        "FBBBFFFRLL",
        "BFFBFBBRLL",
        "FFBFBBFLRR",
        "BFBBFFFRRL",
        "FFBBBBFLLR",
        "FBBFFFBRLL",
        "FBFBBBBLLL",
        "FBFFFBFLRR",
        "FBBBBFFLRL",
        "BFBFFFBRRR",
        "FBBFFBBRLL",
        "FBFFFFBRRL",
    };

    unsigned int mx = 0;
    for(auto& seat : seats){
        mx = std::max(mx, get_ticket(seat).id);
    }

    std::cout << "max: " << mx << "\n\n";

    for(unsigned int i=0; i<mx; ++i){
        std::string seat = bin_to_seat(i);
        if(std::find(seats.begin(), seats.end(), seat) != seats.end()){ // seat is in list, ignore
            continue;
        }

        ticket potential_ticket = get_ticket(seat);
        if(potential_ticket.row == 0 || potential_ticket.row == 127){ // front or back row seat, ignore
            continue;
        }

        bool neg = false;
        bool pos = false;
        for(auto& list_seat : seats){ // check adjacent tickets
            ticket list_ticket = get_ticket(list_seat);
            int id_diff = list_ticket.id - potential_ticket.id;
            if(id_diff == -1){
                neg = true;
            }
            if(id_diff == 1){
                pos = true;
            }
            if(neg && pos){
                print_ticket(potential_ticket);
                break;
            }
        }
    }
}