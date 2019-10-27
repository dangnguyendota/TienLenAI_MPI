//
// Created by mpiuser on 16/10/2019.
//

#ifndef MPIPROJECT_SEQUENCE_H
#define MPIPROJECT_SEQUENCE_H


#include <vector>
#include <algorithm>
#include "../base/BaseCard.h"
#include "../base/BaseObject.h"

class Sequence : public BaseObject {
private:
    std::vector<BaseCard *> cards;
    int minValue;
    int type;
    int maxValue;
    bool homogeneity;
public:
    Sequence(std::vector<BaseCard *> cards);

    bool isHomogeneity();

    int compareTo(Sequence *sequence);

    int getMinValue();

    std::vector<BaseCard *> getCards() override {
        return cards;
    }

    bool beats(BaseObject *object) override {
        if (dynamic_cast<Sequence *>(object) != nullptr) {
            auto *sequence = (Sequence *) object;
            if (cards.size() != sequence->cards.size()) return false;
            if (!homogeneity && sequence->homogeneity) return false;
            if (this->minValue > sequence->minValue) return true;
            if (this->minValue < sequence->minValue) return false;
            if (this->maxValue >= BaseCard::SIX) return this->type > sequence->type;
            return true;
        }
        return false;
    }

    BaseObject *getCopy() override {
        return new Sequence(this->cards);
    }

    bool equals(BaseObject *object) override {
        if (dynamic_cast<Sequence *>(object) != nullptr) {
            auto *sequence = (Sequence *) object;
            if (sequence->cards.size() != this->cards.size()) return false;
            for (int i = 0; i < this->cards.size(); i++) {
                if (!this->cards[i]->equals(sequence->cards[i])) return false;
            }
            return true;
        }
        return false;
    }

    std::string toString() override {
        std::string str = "{";
        for (BaseCard *card : this->cards) {
            str += card->toString();
            str += " ";
        }
        str += "}";
        return str;
    }

    int classCode() override{
        return BaseObject::code_seq;
    }

    static bool valid(std::vector<BaseCard *> cards) {
        if (cards.size() <= 2) return false;
        if (cards[cards.size() - 1]->getValue() == BaseCard::TWO) return false;
        for (int i = 0; i < cards.size() - 1; i++) {
            if (cards[i]->getValue() + 1 != cards[i + 1]->getValue()) return false;
        }
        return true;
    }

    static void sort(std::vector<BaseObject *> *sequence) {
        std::sort(sequence->begin(),
                  sequence->end(),
                  [](BaseObject *lhs, BaseObject *rhs) {
                      return ((Sequence *) lhs)->compareTo((Sequence *) rhs) < 0;
                  });
    }

};


#endif //MPIPROJECT_SEQUENCE_H
