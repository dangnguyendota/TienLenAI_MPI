//
// Created by mpiuser on 18/10/2019.
//

#ifndef MPIPROJECT_FILTER_H
#define MPIPROJECT_FILTER_H

#include "../base/BaseObject.h"
#include "../objects/Sequence.h"

using namespace std;

class Filter {
public:
    static vector<BaseObject *> removeUnnecessarySequences(const vector<BaseObject *> &sequences) {
        bool *checked = new bool[sequences.size()];
        for(int i = 0; i < sequences.size(); i++) {
            checked[i] = false;
        }

        vector<BaseObject *> out;

        for (int i = 0; i < sequences.size(); i++) {
            if (checked[i]) continue;
            checked[i] = true;
            vector<Sequence *> same;
            auto *smin = (Sequence *) sequences[i];
            same.push_back(smin);
            for (int j = 0; j < sequences.size(); j++) {
                if (checked[j]) continue;
                auto *s = (Sequence *) sequences[j];
                if (s->getCards().size() != smin->getCards().size()) continue;
                if (s->getMinValue() != smin->getMinValue()) continue;
                checked[j] = true;
                same.push_back(s);
            }

            std::sort(same.begin(),
                      same.end(),
                      [](Sequence *o1, Sequence *o2) {
                          for (int i1 = (int) o1->getCards().size() - 1; i1 >= 0; i1--) {
                              if (i1 == o1->getCards().size() - 1) {
                                  if (o1->getCards()[i1]->getType() > o2->getCards()[i1]->getType()) return false;
                                  if (o1->getCards()[i1]->getType() < o2->getCards()[i1]->getType()) return true;
                              } else {
                                  if (o1->getCards()[i1]->getType() < o2->getCards()[i1]->getType()) return false;
                                  if (o1->getCards()[i1]->getType() > o2->getCards()[i1]->getType()) return true;
                              }
                          }
                          return false;
                      });

            same = findSequences(same);
            for (Sequence *sequence : same) {
                out.push_back(sequence);
            }
        }

        return out;
    }

    static vector<Sequence *> findSequences(const vector<Sequence *> &sorted) {
        vector<Sequence *> found;
        for (int i = (int) sorted.size() - 1; i >= 0; i--) {
            bool available = true;
            for (Sequence *f : found) {
                if (connect(sorted[i]->getCards(), f->getCards())) {
                    available = false;
                    break;
                }
            }
            if (available) found.push_back(sorted[i]);
        }
        return found;
    }

    static bool connect(const vector<BaseCard *> &card1, const vector<BaseCard *> &card2) {
        for (BaseCard *c1 : card1) {
            for (BaseCard *c2 : card2) {
                if (c1->equals(c2)) return true;
            }
        }
        return false;
    }
};

#endif //MPIPROJECT_FILTER_H
