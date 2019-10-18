//
// Created by mpiuser on 15/10/2019.return std::vector<BaseObject *>();
//

#ifndef MPIPROJECT_BASEOBJECT_H
#define MPIPROJECT_BASEOBJECT_H


#include <string>
#include <vector>
#include "BaseCard.h"

class BaseObject {
public:

    virtual std::vector<BaseCard *> getCards();

    virtual bool beats(BaseObject *object);

    virtual BaseObject *getCopy();

    virtual bool contains(BaseCard *card) final;

    virtual bool contains(int value) final;

    virtual bool equals(BaseObject *object);

    virtual std::string toString();
};


#endif //MPIPROJECT_BASEOBJECT_H
