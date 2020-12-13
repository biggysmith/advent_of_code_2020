#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>


std::pair<int,std::vector<int>> parse_bus_times(const std::string& file){
    std::pair<int,std::vector<int>> bus_times;

    std::ifstream file_stream(file);
    if(!file_stream){
        std::cout << "cannot open file" << std::endl;
        return bus_times;
    }

    std::string line;
    std::getline(file_stream, line);
    bus_times.first = std::stoi(line);

    std::getline(file_stream, line);
    std::stringstream ss(line);
    std::string bus_number_str;
    while(std::getline(ss, bus_number_str, ',')){
        if(bus_number_str == "x"){
            bus_times.second.push_back(0);
        }else{
            bus_times.second.push_back(std::stoi(bus_number_str));
        }
    }

    return bus_times;
}


int my_mod(int n,int m){
    return (n+m)-(n % m);
}

template<typename T>
T mod_inverse(T a, T n) {
    T t = 0;     
    T newt = 1;
    T r = n;     
    T newr = a;

    while (newr != 0){ 
        T quotient = r / newr;
        std::tie(r, newr) = std::pair(newr, r - quotient * newr);
        std::tie(t, newt) = std::pair(newt, t - quotient * newt);
    }

    return t + n;
}
 
template<typename T>
T chinese_remainder(const std::vector<T>& num, const std::vector<T>& rem) {
	T prod = 1;
    for(auto i : num){
        prod *= i;
    }

	T sum = 0;
	for (T i=0; i<(T)num.size(); ++i) {
		T p = prod / num[i];
		sum += rem[i] * mod_inverse(p, num[i]) * p;
	}
 
	return sum % prod;
}

void main()
{
    auto times = parse_bus_times("../src/day13/day13_input.txt");

    // part 1
    {
        int mn = INT_MAX;
        int id = 0;
        for (auto i : times.second) {
            if(i>0){
                int m = my_mod(times.first, i);
                if (m < mn) {
                    mn = m;
                    id = i;
                }
            }
        }

        std::cout << "time: " << times.first << std::endl;
        std::cout << "next bus: " << id << " arriving at " << mn << std::endl;
        std::cout << "waiting time: " << mn - times.first << std::endl;
        std::cout << "answer: " << (mn - times.first)*id << std::endl;
        std::cout << std::endl;
    }

    // part 2
    {
        // chinese remainder (or smallest positive integer that satisfies system of congruences) 
        // solve system of linear congruences e.g. (7,13,59,31,19)
        // x = 7  (mod 7 )
        // x = 12 (mod 13)
        // x = 55 (mod 59)
        // x = 25 (mod 31)
        // x = 12 (mod 19)
        // answer is x which satisfies this system of equations

        std::vector<long long> num;
        std::vector<long long> rem;

        int c = 0;
        for (auto i : times.second) {
            if(i > 0){
                num.push_back(i);
                rem.push_back(i-c%i);
            }
            c++;
        }

        std::cout << "answer: " << chinese_remainder(num,rem) << std::endl;

    }

}