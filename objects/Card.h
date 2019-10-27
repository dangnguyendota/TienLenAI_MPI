//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_CARD_H
#define MPIPROJECT_CARD_H


#include <string>
#include <algorithm>
#include "../base/BaseObject.h"

class Card : public BaseObject {
public:
    Card(BaseCard *card);

    int compareTo(Card *card);

    bool equals(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_card) {
            Card *c = (Card *) object;
            return c->card->equals(this->card);
        }
        return false;
    }

    std::vector<BaseCard *> getCards() override {
        std::vector<BaseCard *> cards;
        cards.push_back(this->card);
        return cards;
    }

    bool beats(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_card) {
            Card *c = (Card *) object;
            if (c->card->getValue() > card->getValue()) return false;
            if (c->card->getValue() < card->getValue()) return true;
            if (c->card->getValue() >= BaseCard::SIX) return card->getType() > c->card->getType();
            return true;
        }
        return false;
    }

    BaseObject *getCopy() override {
        return new Card(this->card);
    }

    std::string toString() override {
        return this->card->toString();
    }

    int classCode() override{
        return BaseObject::code_card;
    }

    static void sort(std::vector<Card *> *cards) {
        std::sort(cards->begin(),
                  cards->end(),
                  [](Card *lhs, Card *rhs) {
                      return lhs->card->compareTo(rhs->card) < 0;
                  });
    }

    BaseCard *card;
};


#endif //MPIPROJECT_CARD_H
