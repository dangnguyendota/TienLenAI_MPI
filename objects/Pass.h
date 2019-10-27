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

    int classCode() override{
        return BaseObject::code_pass;
    }

    bool equals(BaseObject *object) override {
        return object->classCode() == BaseObject::code_pass;
    }
};


#endif //MPIPROJECT_PASS_H
