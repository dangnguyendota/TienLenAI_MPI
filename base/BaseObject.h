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
    static const int code_baseobject = 1;
    static const int code_card = 2;
    static const int code_dub = 3;
    static const int code_trip = 4;
    static const int code_quad = 5;
    static const int code_seq = 6;
    static const int code_pass = 7;
    static const int code_dubseq = 8;
    static const int code_tripseq = 9;
    static const int code_quadseq = 10;
public:
    virtual std::vector<BaseCard *> getCards();

    virtual bool beats(BaseObject *object);

    virtual BaseObject *getCopy();

    virtual bool contains(BaseCard *card) final;

    virtual bool contains(int value) final;

    virtual bool equals(BaseObject *object);

    virtual std::string toString();

    virtual int classCode();

};

#endif //MPIPROJECT_BASEOBJECT_H
