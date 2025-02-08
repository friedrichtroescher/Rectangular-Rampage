//
// Created by Friedrich Tröscher on 08.02.25.
//

#ifndef CMAKESFMLPROJECT_INPUT_H
#define CMAKESFMLPROJECT_INPUT_H


#include "Direction.h"

class Input {
public:
    static Direction getWASDDirection();

    static bool isShooting();
};


#endif //CMAKESFMLPROJECT_INPUT_H
