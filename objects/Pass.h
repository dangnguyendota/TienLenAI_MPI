//
// Created by mpiuser on 16/10/2019.
//

#ifndef MPIPROJECT_PASS_H
#define MPIPROJECT_PASS_H


#include "../base/BaseObject.h"

class Pass : public BaseObject {
public:
    Pass();

    std::vector<BaseCard *> getCards() override {
        return std::vector<BaseCard *>();
    }

    bool beats(BaseObject *object) override {
        return false;
    }

    BaseObject *getCopy() override {
        return this;
    }

    std::string toString() override {
        return "Pass";
    }

    bool equals(BaseObject *object) override {
        return dynamic_cast<Pass *> (object) != nullptr;
    }
};


#endif //MPIPROJECT_PASS_H
