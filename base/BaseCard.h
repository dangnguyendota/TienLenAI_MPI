//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_BASECARD_H
#define MPIPROJECT_BASECARD_H


#include <string>
#include <algorithm>

class BaseCard {
public:
    /* type */
    static const int SPADE = 0; // bích
    static const int CLUB = 1; // tép
    static const int DIAMOND = 2; // rô
    static const int HEART = 3; // cơ
    /* value */
    static const int THREE = 0;
    static const int FOUR = 1;
    static const int FIVE = 2;
    static const int SIX = 3;
    static const int SEVEN = 4;
    static const int EIGHT = 5;
    static const int NINE = 6;
    static const int TEN = 7;
    static const int JACK = 8;
    static const int QUEEN = 9;
    static const int KING = 10;
    static const int ACE = 11;
    static const int TWO = 12;
private:
    int value;
    int type;
public:
    BaseCard(int value, int type);

    BaseCard(std::string code);

    int getValue();

    int getType();

    bool equals(BaseCard *card);

    std::string toString();

    int compareTo(BaseCard *baseCard);

    static std::vector<BaseCard *> deckOfCards();

    static std::vector<BaseCard *> randomCards(std::vector<BaseCard *> container, int length);

    static void sort(std::vector<BaseCard *> *sequence);

    static std::vector<BaseCard *> removeFrom(const std::vector<BaseCard *>& container, const std::vector<BaseCard *>& removed);
};


#endif //MPIPROJECT_BASECARD_H
