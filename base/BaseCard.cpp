//
// Created by mpiuser on 15/10/2019.
//

#include "BaseCard.h"

int BaseCard::getValue() {
    return this->value;
}

int BaseCard::getType() {
    return this->type;
}

BaseCard::BaseCard(int value, int type) {
    this->value = value;
    this->type = type;
}

bool BaseCard::equals(BaseCard *card) {
    return this->value == card->value && this->type == card->value;
}

std::string BaseCard::toString() {
    std::string val = "";
    std::string type = "";
    switch (this->value) {
        case ACE:
            val = "A";
            break;
        case TWO:
            val = "2";
            break;
        case THREE:
            val = "3";
            break;
        case FOUR:
            val = "4";
            break;
        case FIVE:
            val = "5";
            break;
        case SIX:
            val = "6";
            break;
        case SEVEN:
            val = "7";
            break;
        case EIGHT:
            val = "8";
            break;
        case NINE:
            val = "9";
            break;
        case TEN:
            val = "10";
            break;
        case JACK:
            val = "J";
            break;
        case QUEEN:
            val = "Q";
            break;
        case KING:
            val = "K";
            break;
    }
    switch (this->type) {
        case SPADE:
            type = "♠";
            break;
        case CLUB:
            type = "♣";
            break;
        case DIAMOND:
            type = "♦";
            break;
        case HEART:
            type = "♥";
            break;
    }
    return val + type;
}
