//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_TRIPSEQUENCE_H
#define MPIPROJECT_TRIPSEQUENCE_H


#include "../base/BaseObject.h"
#include "Dub.h"
#include "Card.h"

class TripSequence : public BaseObject {
private:
    Dub *dub1;
    Dub *dub2;
    Dub *dub3;
    int maxType;
    int minValue;
public:
    TripSequence(Dub *dub1, Dub *dub2, Dub *dub3);

    int compareTo(TripSequence *sequence);

    std::vector<BaseCard *> getCards() override {
        std::vector<BaseCard *> result;
        result.push_back(dub1->card1);
        result.push_back(dub1->card2);
        result.push_back(dub2->card1);
        result.push_back(dub2->card2);
        result.push_back(dub3->card1);
        result.push_back(dub3->card2);
        return result;
    }

    bool beats(BaseObject *object) override {
        if (dynamic_cast<TripSequence *>(object) != nullptr) {
            auto *sequence = (TripSequence *) object;
            if (this->minValue > sequence->minValue) return true;
            if (this->minValue < sequence->minValue) return false;
            return this->maxType > sequence->maxType;
        }
        if (dynamic_cast<Card *>(object) != nullptr) {
            return ((Card *) object)->card->getValue() == BaseCard::TWO;
        }
        return false;
    }

    BaseObject *getCopy() override {
        return new TripSequence((Dub *) dub1->getCopy(), (Dub *) dub2->getCopy(), (Dub *) dub3->getCopy());
    }

    std::string toString() override {
        return "{" + dub1->toString() + " " + dub2->toString() + " " + dub3->toString() + "}";
    }

    static bool valid(Dub *dub1, Dub *dub2, Dub *dub3) {
        if (dub3->getValue() == BaseCard::TWO) return false;
        return (dub1->getValue() + 1 == dub2->getValue()) && (dub2->getValue() + 1 == dub3->getValue());
    }

    static void sort(std::vector<BaseObject *> *sequence) {
        std::sort(sequence->begin(),
                  sequence->end(),
                  [](BaseObject *lhs, BaseObject *rhs) {
                      return ((TripSequence *) lhs)->compareTo((TripSequence *) rhs) < 0;
                  });
    }
};


#endif //MPIPROJECT_TRIPSEQUENCE_H
