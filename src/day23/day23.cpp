#include <algorithm>
#include <bitset>
#include <execution>
#include <functional>
#include <initializer_list>
#include <forward_list>
#include <stack>
#include <array>
#include <iostream>

struct node_t { 
    int val;
    node_t* next; 
};

void play(int num_cups, int rounds, bool print_part1) 
{
    std::vector<int> cups { 5, 8, 9, 1, 7, 4, 2, 6, 3 };

    std::vector<node_t> list(num_cups+cups.size());
    node_t* node = list.data() + cups[0];

    for (int i = 1; i < cups.size(); ++i){
        node->next = list.data() + cups[i];
        node->next->val = cups[i];
        node = node->next;
    }

    for (int i = (int)cups.size(); i < num_cups; ++i){
        node->next = list.data() + i + 1;
        node->next->val = i + 1;
        node = node->next;
    }

    node->next = list.data() + cups[0];
    node->next->val = cups[0];

    node = list.data() + cups[0];
    for (int i = 0; i < rounds; ++i) {
        node_t* next1 = node->next; 
        node_t* next2 = next1->next;
        node_t* next3 = next2->next;

        int d = node->val - 1;
        if(d == 0) {
            d = num_cups;
        }
        while (d == next1->val || d == next2->val || d == next3->val){
            d--;
            if(d==0) {
                d = num_cups;
            }
        }

        node_t* dest = list.data() + d;

        node->next = next3->next;
        node = node->next;

        next3->next = dest->next;
        dest->next = next1;     
    }

    if(print_part1)
    {
        std::cout << "part1: ";
        auto it = list[1].next;
        while(it != list.data()+1){
            std::cout << it->val;
            it = it->next;
        }
        std::cout << std::endl;
    }
    else
    {
        auto cw1 = list[1].next;
        std::cout << "part2: " << cw1->val * (int64_t)cw1->next->val << std::endl;
    }

}


int main() 
{
    play(9, 100, true);
    play(1000000, 10000000, false);
}



