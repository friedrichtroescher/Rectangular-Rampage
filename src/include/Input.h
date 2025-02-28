//
// Created by Friedrich Tröscher on 08.02.25.
//

#ifndef CMAKESFMLPROJECT_INPUT_H
#define CMAKESFMLPROJECT_INPUT_H


#include "Direction.h"

//Input just provides some tooling for getting input from the player
class Input {
public:
    static Direction getWASDDirection();

    static bool isShooting();
};


#endif //CMAKESFMLPROJECT_INPUT_H
