#include <iostream>
#include <algorithm>
#include "objects/Card.h"

int main()
{
    std::vector <Card*> vec;
    vec.push_back(new Card(new BaseCard(BaseCard::QUEEN, BaseCard::DIAMOND)));
    vec.push_back(new Card(new BaseCard(BaseCard::QUEEN, BaseCard::SPADE)));
    vec.push_back(new Card(new BaseCard(BaseCard::JACK, BaseCard::SPADE)));
    vec.push_back(new Card(new BaseCard(BaseCard::TEN, BaseCard::SPADE)));
    Card::sort(&vec);
    for(Card* card : vec){
        std::cout << card->toString() + ", ";
    }
    return 0;
}
