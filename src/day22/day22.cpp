#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>
#include <fstream>
#include <sstream>

struct decks_t{
    std::vector<int> player1;
    std::vector<int> player2;
};

decks_t parse_input(const std::string& file){
    decks_t input;

    int player_pos = -1;
    std::vector<int>* players[] = {
        &input.player1,
        &input.player2,
    };

    std::ifstream file_stream(file);
    std::string line;
    while(std::getline(file_stream, line)){

        if(line == ""){
            continue;
        }else if(line.find("Player") != std::string::npos){
            player_pos++;
            continue;
        }
        
        players[player_pos]->push_back(std::stoi(line));
    }

    return input;
}


template<typename T>
std::size_t vector_hash(const std::vector<T>& vec) {
    std::hash<T> hasher;
    std::size_t ret = 0;
    for(auto& i : vec) {
        ret ^= hasher(i);
    }
    return ret;
}

template<typename C, typename T>
auto contains(const C& c, const T& t){
    return std::find(std::begin(c), std::end(c), t) != std::end(c);
}

bool play_game(decks_t& decks,bool recurse)
{
    std::vector<size_t> player1_decks;
    std::vector<size_t> player2_decks;

    while(!decks.player1.empty() && !decks.player2.empty()){
        auto deck1_hash = vector_hash(decks.player1);
        auto deck2_hash = vector_hash(decks.player2);
        if(contains(player1_decks,deck1_hash) || contains(player2_decks,deck2_hash)){
            return true;
        }
        player1_decks.push_back(deck1_hash);
        player2_decks.push_back(deck2_hash);


        int player1_card = decks.player1.front();
        int player2_card = decks.player2.front();

        bool player1_wins;
        if(recurse && player1_card < decks.player1.size() && player2_card < decks.player2.size()){
            decks_t new_deck {
                std::vector<int>(decks.player1.begin()+1, decks.player1.begin()+1+player1_card),
                std::vector<int>(decks.player2.begin()+1, decks.player2.begin()+1+player2_card)
            };
            player1_wins = play_game(new_deck,recurse);
        }else{
            player1_wins = player1_card > player2_card;
        }   

        std::rotate(decks.player1.begin(), decks.player1.begin()+1, decks.player1.end());
        std::rotate(decks.player2.begin(), decks.player2.begin()+1, decks.player2.end());

        if(player1_wins){
            decks.player1.push_back(player2_card);
            decks.player2.pop_back();
        }else{
            decks.player2.push_back(player1_card);
            decks.player1.pop_back();
        }
    }

    return !decks.player1.empty();
};

void main()
{
    auto decks = parse_input("../src/day22/day22_input.txt");

    auto calculate_score = [](decks_t decks, bool recurse){
        play_game(decks,recurse);

        std::vector<int>* winning_deck = decks.player2.empty() ?  &decks.player1 : &decks.player2;

        int i = 1;
        int score = 0;
        for(auto it=winning_deck->rbegin(); it!=winning_deck->rend(); ++it, ++i){
            score += *it * i;
        }

        return score;
    };

    std::cout << "part1: " << calculate_score(decks, false) << std::endl;
    std::cout << "part2: " << calculate_score(decks, true) << std::endl;
}

