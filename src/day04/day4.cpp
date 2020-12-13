#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <optional>
#include <sstream>
#include <fstream>

struct passport{
    std::string byr; // (Birth Year)
    std::string iyr; // (Issue Year)
    std::string eyr; // (Expiration Year)
    std::string hgt; // (Height)
    std::string hcl; // (Hair Color)
    std::string ecl; // (Eye Color)
    std::string pid; // (Passport ID)
    std::string cid; // (Country ID)
};

bool is_set(const std::string& field){
    return field != "";
}

bool has_required_fields(const passport& pass){
    return is_set(pass.byr) &&
           is_set(pass.iyr) &&
           is_set(pass.eyr) &&
           is_set(pass.hgt) &&
           is_set(pass.hcl) &&
           is_set(pass.ecl) &&
           is_set(pass.pid);
           //is_set(pass.cid);
}

bool has_valid_fields(const passport& pass){
    bool valid = true;

    if(is_set(pass.byr)){
        int year = std::stoi(pass.byr);
        valid &= year >= 1920 && year <= 2002;
    }

    if(is_set(pass.iyr)){
        int issue = std::stoi(pass.iyr);
        valid &= issue >= 2010 && issue <= 2020;
    }

    if(is_set(pass.eyr)){
        int expiration_year = std::stoi(pass.eyr);
        valid &= expiration_year >= 2020 && expiration_year <= 2030;
    }

    if(is_set(pass.hgt)){
        std::size_t found0 = pass.hgt.find("cm");
        if(found0!=std::string::npos){
            int height = std::stoi(pass.hgt.substr(0,found0));
            valid &= height >= 150 && height <= 193;
        }
        std::size_t found1 = pass.hgt.find("in");
        if(found1!=std::string::npos){
            int height = std::stoi(pass.hgt.substr(0,found1));
            valid &= height >= 59 && height <= 76;
        }
        if(found0 == std::string::npos && found1 == std::string::npos){
            valid &= false;
        }
    }

    if(is_set(pass.hcl)){
        valid &= pass.hcl[0] == '#' && pass.hcl.size()==7 && std::all_of(pass.hcl.begin()+1, pass.hcl.end(), [](auto c){
            return isxdigit(c);  
        });
    }

    if(is_set(pass.ecl)){
        valid &= pass.ecl == "amb" || pass.ecl == "blu" || pass.ecl == "brn" || pass.ecl == "gry" || pass.ecl == "grn" || pass.ecl == "hzl" || pass.ecl == "oth";
    }

    if(is_set(pass.pid)){
        valid &= pass.pid.size() == 9;
    }

    return valid;
}


void print_passport(const passport& pass){
    std::cout << "byr: " << pass.byr << "\n";
    std::cout << "iyr: " << pass.iyr << "\n";
    std::cout << "eyr: " << pass.eyr << "\n";
    std::cout << "hgt: " << pass.hgt << "\n";
    std::cout << "hcl: " << pass.hcl << "\n";
    std::cout << "ecl: " << pass.ecl << "\n";
    std::cout << "pid: " << pass.pid << "\n";
    std::cout << "cid: " << pass.cid << "\n\n";
}

std::vector<passport> parse_txt(const std::string& file){
    std::vector<passport> ret;

    std::ifstream test_passports(file);
    if(!test_passports){
        std::cout << "cannot open file" << std::endl;
        return ret;
    }

    ret.push_back(passport());
    std::string line;
    while (std::getline(test_passports, line)) {
        std::istringstream ss_line(line);
        if(line == ""){
            ret.push_back(passport());
        }
        while(ss_line){
            std::string field;
            ss_line >> field;
            std::string tag = field.substr(0,3);
            if(tag == "byr"){
                ret.back().byr = field.substr(4,field.size());
            }else if(tag == "iyr"){
                ret.back().iyr = field.substr(4,field.size());
            }else if(tag == "eyr"){
                ret.back().eyr = field.substr(4,field.size());
            }else if(tag == "hgt"){
                ret.back().hgt = field.substr(4,field.size());
            }else if(tag == "hcl"){
                ret.back().hcl = field.substr(4,field.size());
            }else if(tag == "ecl"){
                ret.back().ecl = field.substr(4,field.size());
            }else if(tag == "pid"){
                ret.back().pid = field.substr(4,field.size());
            }else if(tag == "cid"){
                ret.back().cid = field.substr(4,field.size());
            }
        }
    }

    return ret;
}

void main()
{
    auto passports = parse_txt("../src/day04/day4_input.txt");

    int valid = 0;
    for(auto& pass : passports){
        //print_passport(pass);
        if(has_required_fields(pass) && has_valid_fields(pass)){
            valid++;
        }
    }

    std::cout << valid << std::endl;
}