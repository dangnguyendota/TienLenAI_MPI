//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_DUB_H
#define MPIPROJECT_DUB_H


#include <algorithm>
#include "../base/BaseObject.h"

class Dub : public BaseObject {
private:
    int maxType;
    int minType;
    int value;
public:
    BaseCard *card1;
    BaseCard *card2;

    Dub(BaseCard *card1, BaseCard *card2);

    int getValue();

    int getMaxType();

    int compareTo(Dub *dub);

    std::vector<BaseCard *> getCards() override {
        std::vector<BaseCard *> result;
        result.push_back(card1);
        result.push_back(card2);
        return result;
    }

    bool beats(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_dub) {
            Dub *dub = (Dub *) object;
            if (value > dub->value) return true;
            if (value < dub->value) return false;
            if (value >= BaseCard::SIX) return maxType > dub->maxType;
            return true;
        }
        return false;
    }

    BaseObject *getCopy() override {
        return new Dub(card1, card2);
    }

    std::string toString() override {
        return "[" + card1->toString() + " " + card2->toString() + "]";
    }

    bool equals(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_dub) {
            Dub *dub = (Dub *) object;
            return dub->card1->equals(card1) && dub->card2->equals(card2);
        }
        return false;
    }

    int classCode() override{
        return BaseObject::code_dub;
    }

    static void sort(std::vector<BaseObject *> *dubs) {
        std::sort(dubs->begin(),
                  dubs->end(),
                  [](BaseObject *lhs, BaseObject *rhs) {

                      return ((Dub *) lhs)->compareTo((Dub *) rhs) < 0;
                  });
    }

    static bool valid(BaseCard *card1, BaseCard *card2) {
        return card1->getValue() == card2->getValue();
    }

};


#endif //MPIPROJECT_DUB_H
