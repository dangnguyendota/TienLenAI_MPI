//
// Created by mpiuser on 17/10/2019.
//

#ifndef MPIPROJECT_UTIL_H
#define MPIPROJECT_UTIL_H


#include <chrono>
#include <stdexcept>
#include <iostream>
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

    static int indexOf(BaseCard *element, const std::vector<BaseCard *> &vector) {
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

    static bool deleteElement(BaseCard *element, std::vector<BaseCard *> &vector) {
        int index = Util::indexOf(element, vector);
        if (index == -1) {
            return false;
        }
        vector.erase(vector.begin() + index);
        return true;
    }

    static BaseObject *deleteElement(int index, std::vector<BaseObject *> &vector) {
//        if (0 > index || index >= vector.size())
//            throw std::invalid_argument("Index out of ranger " + std::to_string(index));
        BaseObject *o = vector[index];
        vector.erase(vector.begin() + index);
        return o;
    }

    static BaseCard *deleteElement(int index, std::vector<BaseCard *> &vector) {
//        if (index < 0 || index >= vector.size())
//            throw std::invalid_argument("Index out of ranger " + std::to_string(index));
        BaseCard *o = vector[index];
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


    static long currentTimeMillis() {
        return std::clock() / 1000;
    }

    static void replaceAll(std::string& str, const std::string& from, const std::string& to) {
        if(from.empty())
            return;
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
        }
    }

    static std::vector<std::string> split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos-prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        }
        while (pos < str.length() && prev < str.length());
        return tokens;
    }

    static std::string vectorToString(const std::vector<BaseCard *>& vector) {
        std::string str = "[";
        for(BaseCard *card : vector) {
            str += card->toString();
            str += ", ";
        }
        str += "]";
        return str;
    }

    static std::string vectorToString(const std::vector<BaseObject *>& vector) {
        std::string str = "[";
        for(BaseObject *card : vector) {
            str += card->toString();
            str += ", ";
        }
        str += "]";
        return str;
    }

    static void println(const std::string& text) {
        std::cout << text << "\n";
    }

    static void println(const int& text) {
        std::cout << std::to_string(text) << "\n";
    }

    static void print(const std::string& text) {
        std::cout << text << " ";
    }

    static int nextInt() {
        std::string tmp;
        std::getline(std::cin, tmp);
        return std::atoi(tmp.c_str());
    }
};


#endif //MPIPROJECT_UTIL_H
