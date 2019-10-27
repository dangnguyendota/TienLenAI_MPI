#include <iostream>
#include <algorithm>
#include <ctime>
#include "objects/Card.h"
#include "helper/Util.h"
#include "test/Test.h"

int main()
{
//    std::vector <Card*> vec;
//    vec.push_back(new Card(new BaseCard(BaseCard::QUEEN, BaseCard::DIAMOND)));
//    vec.push_back(new Card(new BaseCard(BaseCard::QUEEN, BaseCard::SPADE)));
//    vec.push_back(new Card(new BaseCard(BaseCard::JACK, BaseCard::SPADE)));
//    vec.push_back(new Card(new BaseCard(BaseCard::TEN, BaseCard::SPADE)));
//    Card::sort(&vec);
//    for(Card* card : vec){
//        std::cout << card->toString() + ", ";
//        std::cout << vec.size();
//    }
//    BaseCard *baseCard = new BaseCard("10♥");
//    std::string str = "J♥";
//    std::cout << baseCard->toString();
//    long start = Util::currentTimeMillis();
//    while (Util::currentTimeMillis() - start < 5000) {
//    }
//    std::cout << (Util::currentTimeMillis() - start) << std::endl;
    Test::playSolo();
    return 0;
}
