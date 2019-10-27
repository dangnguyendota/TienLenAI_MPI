//
// Created by mpiuser on 15/10/2019.
//

#include "BaseObject.h"
#include "BaseCard.h"

std::string BaseObject::toString() {
    return "BaseObject";
}


bool BaseObject::beats(BaseObject *object) {
    return false;
}

bool BaseObject::contains(int value) {
    std::vector<BaseCard *> cards = this->getCards();
    for (BaseCard *baseCard : cards) {
        if (baseCard->getValue() == value) return true;
    }
    return false;
}

bool BaseObject::contains(BaseCard *card) {
    std::vector<BaseCard *> cards = this->getCards();
    for (BaseCard *baseCard : cards) {
        if (baseCard->equals(card)) return true;
    }
    return false;
}

BaseObject *BaseObject::getCopy() {
    return nullptr;
}

std::vector<BaseCard *> BaseObject::getCards() {
    return std::vector<BaseCard *>();
}

bool BaseObject::equals(BaseObject *object) {
    return false;
}

int BaseObject::classCode() {
    return BaseObject::code_baseobject;
}
