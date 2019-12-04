//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_TRIPS_H
#define MPIPROJECT_TRIPS_H


#include <vector>
#include <algorithm>
#include "../base/BaseCard.h"
#include "../base/BaseObject.h"

class Trips : public BaseObject {
private:
    BaseCard *card1;
    BaseCard *card2;
    BaseCard *card3;
    int value;

public:
    Trips(BaseCard *card1, BaseCard *card2, BaseCard *card3);

    int compareTo(Trips *trips);

    int getValue();

    std::vector<BaseCard *> getCards() override {
        std::vector<BaseCard *> result;
        result.push_back(card1);
        result.push_back(card2);
        result.push_back(card3);
        return result;
    }

    bool beats(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_trip) {
            auto *trips = (Trips *) object;
            return this->value > trips->value;
        }
        return false;
    }

    BaseObject *getCopy() override {
        return new Trips(this->card1, this->card2, this->card3);
    }

    bool equals(BaseObject *object) override {
        if (object->classCode() == BaseObject::code_trip) {
            auto *trips = (Trips *) object;
            return this->card1->equals(trips->card1) && this->card2->equals(trips->card2) &&
                   this->card3->equals(trips->card3);
        }
        return false;
    }

    std::string toString() override {
        return "{" + card1->toString() + " " + card2->toString() + " " + card3->toString() + "}";
    }

    int classCode() override{
        return BaseObject::code_trip;
    }

    static void sort(std::vector<BaseObject *> *trips) {
        std::sort(trips->begin(),
                  trips->end(),
                  [](BaseObject *lhs, BaseObject *rhs) {
                      return ((Trips *) lhs)->compareTo((Trips *) rhs) < 0;
                  });
    }

    static bool valid(BaseCard *card1, BaseCard *card2, BaseCard *card3) {
        return card1->getValue() == card2->getValue() && card2->getValue() == card3->getValue();
    }
};


#endif //MPIPROJECT_TRIPS_H
