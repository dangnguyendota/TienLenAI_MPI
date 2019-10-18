//
// Created by mpiuser on 17/10/2019.
//

#ifndef MPIPROJECT_UTIL_H
#define MPIPROJECT_UTIL_H


#include <chrono>
#include "../base/BaseObject.h"
#include "../objects/Card.h"

class Util {
public:
    static int indexOf(BaseObject *element, const std::vector<BaseObject *> &vector) {
        for (int i = 0; i < vector.size(); i++) {
            if (vector[i]->equals(element)) return i;
        }
        return -1;
    }

    static bool deleteElement(BaseObject *element, std::vector<BaseObject *> &vector) {
        int index = Util::indexOf(element, vector);
        if (index == -1) {
            return false;
        }
        vector.erase(vector.begin() + index);
        return true;
    }

    static BaseObject *deleteElement(int index, std::vector<BaseObject *> &vector) {
        if (0 < index || index > vector.size())
            throw std::invalid_argument("Index out of ranger " + std::to_string(index));
        BaseObject *o = vector[index];
        vector.erase(vector.begin() + index);
        return o;
    }

    static BaseCard *findCard(int value, int type, const std::vector<BaseCard *> &deck) {
        for (BaseCard *card : deck) {
            if (card->getValue() == value && card->getType() == type) return card;
        }
        return nullptr;
    }

    static void addAll(std::vector<BaseObject *> &dis, const std::vector<BaseObject *> &src) {
        for (BaseObject *o : src) dis.push_back(o);
    }

    static std::vector<BaseObject *> convertToBaseObject(const std::vector<BaseCard *> &cards) {
        std::vector<BaseObject *> vector;
        vector.reserve(cards.size());
        for (BaseCard *card : cards) {
            vector.push_back(new Card(card));
        }
        return vector;
    }


    static std::chrono::milliseconds currentTimeMillis() {
        std::chrono::milliseconds ms = duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
        );
        return ms;
    }
};


#endif //MPIPROJECT_UTIL_H
