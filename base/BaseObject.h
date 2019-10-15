//
// Created by mpiuser on 15/10/2019.
//

#ifndef MPIPROJECT_BASEOBJECT_H
#define MPIPROJECT_BASEOBJECT_H


#include <string>
#include <vector>
#include "BaseCard.h"

class BaseObject {
public:

    virtual std::vector<BaseCard*> getCards();

    virtual bool beats(BaseObject *object);

    virtual BaseObject* getCopy();

    virtual bool contains(BaseCard *card);

    virtual bool contains(int value);

    virtual bool equals(BaseObject *object);

    virtual std::string toString();

};


#endif //MPIPROJECT_BASEOBJECT_H
