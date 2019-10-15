#include <iostream>
#include <algorithm>
#include "base/Card.h"

int main()
{
//    std::vector <Card*> vec;
//    vec.push_back(new Card(new BaseCard(BaseCard::QUEEN, BaseCard::SPADE)));
//    vec.push_back(new Card(new BaseCard(BaseCard::THREE, BaseCard::SPADE)));
//    vec.push_back(new Card(new BaseCard(BaseCard::JACK, BaseCard::SPADE)));
//    vec.push_back(new Card(new BaseCard(BaseCard::TEN, BaseCard::SPADE)));
//    Card::sort(&vec);
//    for(Card* card : vec){
//        std::cout << card->toString() + ", ";
//    }
    bool *push = new bool[4];
    push = new bool[2]{true, true};
    std::cout << push[0];
    return 0;
}
