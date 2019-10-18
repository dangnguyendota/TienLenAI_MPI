//
// Created by mpiuser on 16/10/2019.
//

#ifndef MPIPROJECT_QUADSEQUENCE_H
#define MPIPROJECT_QUADSEQUENCE_H


#include "../base/BaseObject.h"
#include "Dub.h"
#include "Quads.h"
#include "TripSequence.h"

class QuadSequence : public BaseObject {
private:
    Dub *dub1;
    Dub *dub2;
    Dub *dub3;
    Dub *dub4;
    int minValue;
    int maxType;
public:
    QuadSequence(Dub *dub1, Dub *dub2, Dub *dub3, Dub *dub4);

    int compareTo(QuadSequence *sequence);

    std::vector<BaseCard *> getCards() override {
        std::vector<BaseCard *> result;
        result.push_back(dub1->card1);
        result.push_back(dub1->card2);
        result.push_back(dub2->card1);
        result.push_back(dub2->card2);
        result.push_back(dub3->card1);
        result.push_back(dub3->card2);
        result.push_back(dub4->card1);
        result.push_back(dub4->card2);
        return result;
    }

    bool beats(BaseObject *object) override {
        if (dynamic_cast<QuadSequence *>(object) != nullptr) {
            auto *sequence = (QuadSequence *) object;
            if (this->minValue > sequence->minValue) return true;
            if (this->minValue < sequence->minValue) return false;
            return this->maxType > sequence->maxType;
        }
        if (dynamic_cast<Quads *>(object) != nullptr) return true;
        if (dynamic_cast<TripSequence *>(object) != nullptr) return true;
        if (dynamic_cast<Dub *>(object) != nullptr) return ((Dub *) object)->getValue() == BaseCard::TWO;
        if (dynamic_cast<Card *>(object) != nullptr) return ((Card *) object)->card->getValue() == BaseCard::TWO;
        return false;
    }

    BaseObject *getCopy() override {
        return new QuadSequence((Dub *) dub1->getCopy(), (Dub *) dub2->getCopy(), (Dub *) dub3->getCopy(),
                                (Dub *) dub4->getCopy());
    }

    bool equals(BaseObject *object) override {
        if (dynamic_cast<QuadSequence *>(object) != nullptr) {
            auto *sequence = (QuadSequence *) object;
            return this->dub1->equals(sequence->dub1) &&
                   this->dub2->equals(sequence->dub2) &&
                   this->dub3->equals(sequence->dub3) &&
                   this->dub4->equals(sequence->dub4);
        }
        return false;
    }

    std::string toString() override {
        return "{" + dub1->toString() + " " + dub2->toString() + " " + dub3->toString() + " " + dub4->toString() + "}";
    }

    static bool valid(Dub *dub1, Dub *dub2, Dub *dub3, Dub *dub4) {
        if (dub4->getValue() == BaseCard::TWO) return false;
        return dub1->getValue() + 1 == dub2->getValue() &&
               dub2->getValue() + 1 == dub3->getValue() &&
               dub3->getValue() + 1 == dub4->getValue();
    }

    static void sort(std::vector<BaseObject *> *sequence) {
        std::sort(sequence->begin(),
                  sequence->end(),
                  [](BaseObject *lhs, BaseObject *rhs) {
                      return ((QuadSequence *) lhs)->compareTo((QuadSequence *) rhs) < 0;
                  });
    }
};


#endif //MPIPROJECT_QUADSEQUENCE_H
