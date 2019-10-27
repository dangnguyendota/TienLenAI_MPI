//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_DUBSEQUENCE_H
#define MPIPROJECT_DUBSEQUENCE_H


#include "../base/BaseObject.h"
#include "Dub.h"

class DubSequence : public BaseObject {
private:
    Dub *dub1;
    Dub *dub2;
    int minValue;
    int maxType;
public:
    DubSequence(Dub *dub1, Dub *dub2);

    int compareTo(DubSequence *sequence);

    std::vector<BaseCard *> getCards() override {
        std::vector<BaseCard *> result;
        result.push_back(dub1->card1);
        result.push_back(dub1->card2);
        result.push_back(dub2->card1);
        result.push_back(dub2->card2);
        return result;
    }

    bool beats(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_dubseq) {
            auto *sequence = (DubSequence *) object;
            if (this->minValue > sequence->minValue) return true;
            if (this->minValue < sequence->minValue) return false;
            return this->maxType > sequence->maxType;
        }
        return false;
    }


    BaseObject *getCopy() override {
        return new DubSequence((Dub *) dub1->getCopy(), (Dub *) dub2->getCopy());
    }

    bool equals(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_dubseq) {
            auto *sequence = (DubSequence *) object;
            return this->dub1->equals(sequence->dub1) && this->dub2->equals(sequence->dub2);
        }
        return false;
    }

    std::string toString() override {
        return "{" + dub1->toString() + " " + dub2->toString() + "}";
    }

    int classCode() override{
        return BaseObject::code_dubseq;
    }

    static bool valid(Dub *dub1, Dub *dub2) {
        if (dub2->getValue() == BaseCard::TWO) return false;
        return dub1->getValue() + 1 == dub2->getValue();
    }

    static void sort(std::vector<BaseObject *> *sequence) {
        std::sort(sequence->begin(),
                  sequence->end(),
                  [](BaseObject *lhs, BaseObject *rhs) {
                      return ((DubSequence *) lhs)->compareTo((DubSequence *) rhs) < 0;
                  });
    }
};


#endif //MPIPROJECT_DUBSEQUENCE_H
