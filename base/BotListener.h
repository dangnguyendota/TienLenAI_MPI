//
// Created by mpiuser on 16/10/2019.
//

#ifndef MPIPROJECT_BOTLISTENER_H
#define MPIPROJECT_BOTLISTENER_H

#include "BaseObject.h"

class BotListener {
public:
    virtual void onResult(BaseObject *o);
};

#endif //MPIPROJECT_BOTLISTENER_H
