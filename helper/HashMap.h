//
// Created by mpiuser on 22/10/2019.
//

#ifndef MPIPROJECT_HASHMAP_H
#define MPIPROJECT_HASHMAP_H


#include "../base/BaseObject.h"
#include "Util.h"

class HashMap {
private:
    std::vector<BaseObject *> keys;
    std::vector<std::vector<BaseObject *>> values;
public:
    void push_back(BaseObject *key, const std::vector<BaseObject *>& value);

    std::vector<BaseObject *>& operator[](BaseObject *object) {
        for(int i = 0; i < keys.size(); i++) {
            if(keys[i]->equals(object)) return values[i];
        }
        throw std::invalid_argument("hash map does not contain key " + object->toString() + this->toString());
    }

    std::string toString(){
        std::string str = "\n{\n";
        for(int i = 0; i < keys.size(); i++) {
            str += "    [\n";
            str += "        k: ";
            str += keys[i]->toString();
            str += ",\n";
            str += "        v: ";
            str += Util::vectorToString(values[i]);
            str += "\n  ];\n";
        }
        str += "}\n";
        return str;
    }
};


#endif //MPIPROJECT_HASHMAP_H
