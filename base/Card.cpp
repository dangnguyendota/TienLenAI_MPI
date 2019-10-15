//
// Created by mpiuser on 15/10/2019.
//

#include <vector>
#include <string>
#include "BaseObject.cpp"

using namespace std;

class Card : BaseObject{
public:
    /* type */
    const static int SPADE = 0; // bích
    const static int CLUB = 1; // tép
    const static int DIAMOND = 2; // rô
    const static int HEART = 3; // cơ
    /* value */
    const static int THREE = 0;
    const static int FOUR = 1;
    const static int FIVE = 2;
    const static int SIX = 3;
    const static int SEVEN = 4;
    const static int EIGHT = 5;
    const static int NINE = 6;
    const static int TEN = 7;
    const static int JACK = 8;
    const static int QUEEN = 9;
    const static int KING = 10;
    const static int ACE = 11;
    const static int TWO = 12;

private:
    int value;
    int type;

public:
    int getValue(){
        return value;
    }

    int getType() {
        return type;
    }
};