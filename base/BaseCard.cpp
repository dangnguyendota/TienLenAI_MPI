//
// Created by mpiuser on 15/10/2019.
//

#include <stdexcept>
#include <vector>
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

int BaseCard::compareTo(BaseCard *baseCard) {
    if (this->getValue() == baseCard->getValue()) {
        if (this->getType() == baseCard->getType()) return 0;
        if (this->getType() > baseCard->getType()) return 1;
        return -1;
    }
    return this->getValue() > baseCard->getValue() ? 1 : -1;

}

BaseCard::BaseCard(std::string code) {
    if (code.length() != 4 && code.length() != 5) throw std::invalid_argument("cards code is not valid");
    std::string type_str = code.substr(code.length() - 3, code.length());
    if (type_str == "♥") this->type = HEART;
    else if (type_str == "♦") this->type = DIAMOND;
    else if (type_str == "♣") this->type = CLUB;
    else if (type_str == "♠") this->type = SPADE;
    else throw std::invalid_argument("type is not valid");

    if (code.length() == 5) {
        this->value = TEN;
        return;
    }

    switch (code[0]) {
        case 'A':
            this->value = ACE;
            break;
        case '2':
            this->value = TWO;
            break;
        case '3':
            this->value = THREE;
            break;
        case '4':
            this->value = FOUR;
            break;
        case '5':
            this->value = FIVE;
            break;
        case '6':
            this->value = SIX;
            break;
        case '7':
            this->value = SEVEN;
            break;
        case '8':
            this->value = EIGHT;
            break;
        case '9':
            this->value = NINE;
            break;
        case 'J':
            this->value = JACK;
            break;
        case 'Q':
            this->value = QUEEN;
            break;
        case 'K':
            this->value = KING;
            break;
    }
}

std::vector<BaseCard *> BaseCard::deckOfCards() {
    std::vector<BaseCard *> deck;
    for (int type = SPADE; type <= HEART; type++) {
        for (int value = THREE; value <= TWO; value++) {
            deck.push_back(new BaseCard(value, type));
        }
    }
    return deck;
}

std::vector<BaseCard *> BaseCard::randomCards(std::vector<BaseCard *> container, int length) {
    return std::vector<BaseCard *>();
}

void BaseCard::sort(std::vector<BaseCard *> *sequence) {
    std::sort(sequence->begin(),
              sequence->end(),
              [](BaseCard *lhs, BaseCard *rhs) {
                  return lhs->compareTo(rhs) < 0;
              });
}


