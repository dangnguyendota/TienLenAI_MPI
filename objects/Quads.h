//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_QUADS_H
#define MPIPROJECT_QUADS_H


#include <algorithm>
#include "../base/BaseObject.h"
#include "TripSequence.h"

class Quads : public BaseObject {
private:
    BaseCard *card1;
    BaseCard *card2;
    BaseCard *card3;
    BaseCard *card4;
    int value;
public:
    Quads(BaseCard *card1, BaseCard *card2, BaseCard *card3, BaseCard *card4);

    int compareTo(Quads *quads);

    std::vector<BaseCard *> getCards() override {
        std::vector<BaseCard *> result;
        result.push_back(card1);
        result.push_back(card2);
        result.push_back(card3);
        result.push_back(card4);
        return result;
    }

    bool beats(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_quad) return this->value > ((Quads *) object)->value;
        if (object->classCode() == BaseObject::code_tripseq) return true;
        if (object->classCode() == BaseObject::code_dub) return ((Dub *) object)->getValue() == BaseCard::TWO;
        if (object->classCode() == BaseObject::code_card) return ((Card *) object)->card->getValue() == BaseCard::TWO;
        return false;
    }

    BaseObject *getCopy() override {
        return new Quads(card1, card2, card3, card4);
    }

    bool equals(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_quad) {
            return this->value == ((Quads *) object)->value;
        }
        return false;
    }

    std::string toString() override {
        return "[" + card1->toString() + " " + card2->toString() + " " + card3->toString() + " " + card4->toString() +
               "]";
    }

    int classCode() override{
        return BaseObject::code_quad;
    }

    static bool valid(BaseCard *card1, BaseCard *card2, BaseCard *card3, BaseCard *card4) {
        return card1->getValue() == card2->getValue() && card2->getValue() == card3->getValue() &&
               card3->getValue() == card4->getValue();
    }

    static void sort(std::vector<BaseObject *> *quads) {
        std::sort(quads->begin(),
                  quads->end(),
                  [](BaseObject *lhs, BaseObject *rhs) {
                      return ((Quads *) lhs)->compareTo((Quads *) rhs) < 0;
                  });
    }
};


#endif //MPIPROJECT_QUADS_H
