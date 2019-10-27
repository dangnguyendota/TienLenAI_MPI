//
// Created by mpiuser on 22/10/2019.
//

#include <stdexcept>
#include "HashMap.h"

void HashMap::push_back(BaseObject *key, const std::vector<BaseObject *>& value) {
    if(this->keys.size() != this->values.size()) throw std::invalid_argument("length of keys and values are different");
    this->keys.push_back(key);
    this->values.push_back(value);
}

