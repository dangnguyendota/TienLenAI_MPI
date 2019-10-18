//
// Created by mpiuser on 17/10/2019.
//

#ifndef MPIPROJECT_FINDER_H
#define MPIPROJECT_FINDER_H

#include "../base/BaseObject.h"
#include "../objects/Dub.h"
#include "../objects/Trips.h"
#include "../helper/Util.h"
#include "../objects/Quads.h"
#include "../objects/Sequence.h"
#include "../objects/DubSequence.h"
#include "../objects/QuadSequence.h"

using namespace std;

class Finder {
public:
    static vector<BaseObject *> scan(const vector<BaseCard *> &cards, const string &clazz) {
        if (clazz == "Dub") {
            return dubScan(cards);
        } else if (clazz == "Trips") {
            return tripsScan(cards);
        } else if (clazz == "Quads") {
            return quadsScan(cards);
        } else if (clazz == "DubSequence") {
            return dubSequenceScan(cards);
        } else if (clazz == "TripSequence") {
            return tripSequenceScan(cards);
        } else if (clazz == "QuadSequence") {
            return quadSequenceScan(cards);
        } else if (clazz == "Sequence") {
            return sequenceScan(cards);
        }
        return vector<BaseObject *>();
    }

private:
    static vector<BaseObject *> dubScan(vector<BaseCard *> cards) {
        vector<BaseObject *> dubs;
        for (int i = 0; i < cards.size(); i++) {
            for (int j = i + 1; j < cards.size(); j++) {
                if (Dub::valid(cards[i], cards[j])) {
                    dubs.push_back(new Dub(cards[i], cards[j]));
                }
            }
        }
        Dub::sort(&dubs);
        return dubs;
    }

    static vector<BaseObject *> tripsScan(const vector<BaseCard *> &cards) {
        vector<BaseObject *> trips;
        int *count = new int[13];
        for (BaseCard *card : cards) {
            count[card->getValue()] += 1;
        }

        for (int value = BaseCard::THREE; value <= BaseCard::TWO; value++) {
            if (count[value] < 3) continue;
            if (count[value] == 3) {
                vector<BaseCard *> list = Finder::getAllCardsWithValue(cards, value);
                trips.push_back(new Trips(list[0], list[1], list[2]));
            } else if (count[value] == 4) {
                BaseCard *card_1 = Util::findCard(value, BaseCard::SPADE, cards);
                BaseCard *card_2 = Util::findCard(value, BaseCard::CLUB, cards);
                BaseCard *card_3 = Util::findCard(value, BaseCard::DIAMOND, cards);
                BaseCard *card_4 = Util::findCard(value, BaseCard::HEART, cards);
                trips.push_back(new Trips(card_1, card_2, card_3));
                trips.push_back(new Trips(card_1, card_2, card_4));
                trips.push_back(new Trips(card_1, card_3, card_4));
                trips.push_back(new Trips(card_2, card_3, card_4));
            }
        }
        Trips::sort(&trips);
        return trips;
    }

    static vector<BaseObject *> quadsScan(const vector<BaseCard *> &cards) {
        vector<BaseObject *> quads;
        int *count = new int[13];
        for (BaseCard *card : cards) {
            count[card->getValue()] += 1;
        }
        for (int value = BaseCard::THREE; value <= BaseCard::TWO; value++) {
            if (count[value] != 4) continue;
            quads.push_back(new Quads(
                    Util::findCard(value, BaseCard::SPADE, cards),
                    Util::findCard(value, BaseCard::CLUB, cards),
                    Util::findCard(value, BaseCard::DIAMOND, cards),
                    Util::findCard(value, BaseCard::HEART, cards)
            ));
        }

        Quads::sort(&quads);
        return quads;
    }

    /* tìm bộ dây */
    static vector<BaseObject *> sequenceScan(const vector<BaseCard *> &cards) {
        vector<BaseObject *> sequences;
        vector<vector<BaseCard *>> count;
        for (int i = 0; i < 13; i++) {
            vector<BaseCard *> t;
            count.push_back(t);
        }
        for (BaseCard *card : cards) {
            count[card->getValue()].push_back(card);
        }
        int index = 0;
        int start = 0;
        int stop = 0;
        while (index < count.size()) {
            if (count[index].empty() || index == count.size() - 1) {
                stop = index + 1;
                if (stop - start >= 3) {
                    vector<vector<int>> iFound;
                    for (int i = start; i < stop; i++) {
                        vector<int> temp_i;
                        temp_i.push_back(i);
                        Finder::find(i, stop, temp_i, iFound);
                    }
                    vector<vector<BaseCard *>> foundCards;
                    for (const vector<int> &anIFound : iFound) {
                        vector<BaseCard *> temp;
                        Finder::findSequence(temp, 0, anIFound, count, foundCards);
                    }

                    for (const vector<BaseCard *> &c : foundCards) {
                        if (c.size() < 3) continue;
                        if (!Sequence::valid(c)) continue;
                        sequences.push_back(new Sequence(c));
                    }
                }
                start = index + 1;
            }
            index++;
        }
        Sequence::sort(&sequences);
        return sequences;
    }

    /* tìm hai đôi thông */
    static vector<BaseObject *> dubSequenceScan(const vector<BaseCard *> &cards) {
        vector<BaseObject *> dubSequences;
        vector<BaseObject *> dubs = Finder::dubScan(cards);
        for (int i = 0; i < dubs.size(); i++) {
            for (int j = i + 1; j < dubs.size(); j++) {
                if (DubSequence::valid((Dub *) dubs[i], (Dub *) dubs[j])) {
                    dubSequences.push_back(new DubSequence((Dub *) dubs[i], (Dub *) dubs[j]));
                }
            }
        }
        DubSequence::sort(&dubSequences);
        return dubSequences;
    }

    /* tìm ba đôi thông */
    static vector<BaseObject *> tripSequenceScan(const vector<BaseCard *> &cards) {
        vector<BaseObject *> tripSequences;
        vector<BaseObject *> dubs = Finder::dubScan(cards);
        if (dubs.size() < 3) {
            return vector<BaseObject *>();
        }

        for (int i = 0; i < dubs.size(); i++) {
            for (int j = i + 1; j < dubs.size(); j++) {
                for (int t = j + 1; t < dubs.size(); t++) {
                    if (TripSequence::valid((Dub *) dubs[i], (Dub *) dubs[j], (Dub *) dubs[t])) {
                        tripSequences.push_back(new TripSequence((Dub *) dubs[i], (Dub *) dubs[j], (Dub *) dubs[t]));
                    }
                }
            }
        }
        TripSequence::sort(&tripSequences);
        return tripSequences;
    }

    /* tìm 4 dôi thông */
    static vector<BaseObject *> quadSequenceScan(const vector<BaseCard *> &cards) {
        vector<BaseObject *> quadSequences;
        vector<BaseObject *> dubs = Finder::dubScan(cards);
        if (dubs.size() < 3) return vector<BaseObject *>();
        for (int i = 0; i < dubs.size(); i++) {
            for (int j = i + 1; j < dubs.size(); j++) {
                for (int t = j + 1; t < dubs.size(); t++) {
                    for (int k = t + 1; k < dubs.size(); k++) {
                        if (QuadSequence::valid((Dub *) dubs[i], (Dub *) dubs[j], (Dub *) dubs[t], (Dub *) dubs[k])) {
                            quadSequences.push_back(new QuadSequence((Dub *) dubs[i], (Dub *) dubs[j], (Dub *) dubs[t],
                                                                     (Dub *) dubs[k]));
                        }
                    }
                }
            }
        }
        QuadSequence::sort(&quadSequences);
        return quadSequences;
    }


    /* HELPER */

    static vector<BaseCard *> getAllCardsWithValue(const vector<BaseCard *> &cards, int value) {
        vector<BaseCard *> list;
        for (BaseCard *card : cards) {
            if (card->getValue() == value) list.push_back(card);
        }
        return list;
    }

    static void
    findSequence(vector<BaseCard *> &cards, int currentIndex, vector<int> arr, const vector<vector<BaseCard *>> &lists,
                 vector<vector<BaseCard *>> &out) {
        if (currentIndex == arr.size()) {
            out.push_back(cards);
            return;
        }

        for (BaseCard *card : lists[arr[currentIndex]]) {
            vector<BaseCard *> tmp;
            tmp.reserve(cards.size());
            for (auto item : cards) {
                tmp.push_back(item);
            }
            tmp.push_back(card);
            findSequence(tmp, currentIndex + 1, arr, lists, out);
        }
    }

    static void
    find(int current, int stop, const std::vector<int> &currentIndexes, std::vector<std::vector<int>> &out) {
        if (currentIndexes.size() >= 3) out.push_back(currentIndexes);
        for (int i = current + 1; i < stop; i++) {
            std::vector<int> tmp;
            tmp.reserve(currentIndexes.size());
            for (auto item : currentIndexes) {
                tmp.push_back(item);
            }
            tmp.push_back(i);
            find(i, stop, tmp, out);
        }
    }
};

#endif //MPIPROJECT_FINDER_H
