//
// Created by mpiuser on 15/10/2019.
//

#include "vector"
#include "string"
#include "Card.cpp"

using namespace std;

class BaseObject {
    virtual ~BaseObject() = default;

    virtual vector<const Card&> getCards() {
    };

    virtual bool beats(const BaseObject& o){

    };

    virtual BaseObject getCopy(){

    };

    virtual bool contains(const Card& card){

    };

    virtual bool contains(int value){

    };

    virtual string toString(){

    };

    virtual bool equals(const BaseObject& o);
};